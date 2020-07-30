/*
 * Copyright (C) 2019  Christian Berger
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "cluon-complete.hpp"
#include "opendlv-standard-message-set.hpp"
#include "lynx19gw.hpp"

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/select.h>

#ifdef __linux__
    #include <linux/if.h>
    #include <linux/can.h>
#endif

#include <unistd.h>

#include <cerrno>
#include <cmath>
#include <cstdint>
#include <cstring>

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

int32_t main(int32_t argc, char **argv) {
    int32_t retCode{1};
    auto commandlineArguments = cluon::getCommandlineArguments(argc, argv);
    if ( (0 == commandlineArguments.count("cid")) ) {
        std::cerr << argv[0] << " translates messages from CAN to ODVD messages for CFSD 20 Lynx Car." << std::endl;
        std::cerr << "Usage:   " << argv[0] << " --cid=<OD4 session> [--id=ID] --can=<name of the CAN device> [--verbose]" << std::endl;
        std::cerr << "         --cid:    CID of the OD4Session to send and receive messages" << std::endl;
        std::cerr << "         --id:     ID to use as senderStamp for sending" << std::endl;
        std::cerr << "Example: " << argv[0] << " --cid=111 --can=can0 --verbose" << std::endl;
    }
    else {
        const std::string CANDEVICE{commandlineArguments["can"]};
        const uint32_t ID{(commandlineArguments["id"].size() != 0) ? static_cast<uint32_t>(std::stoi(commandlineArguments["id"])) : 0};
        const bool VERBOSE{commandlineArguments.count("verbose") != 0};

        cluon::OD4Session od4{static_cast<uint16_t>(std::stoi(commandlineArguments["cid"]))};

        // Delegate to convert incoming CAN frames into ODVD messages that are broadcast into the OD4Session.
        // std::mutex msgTest;
        // opendlv::proxy::Test msgTest;

        auto decode = [&od4, VERBOSE, ID](cluon::data::TimeStamp ts, uint16_t canFrameID, uint8_t *src, uint8_t len) {
            if ( (nullptr == src) || (0 == len) ) return;
            const int16_t senderStampAsmsOn = 5005;
            const int16_t senderStampSaAvailable = 5016;
            const int16_t senderStampResState = 5003;
            const int16_t senderStampResStopSignal = 5014;
            const int16_t senderStampResGoSignal = 5013;
            const int16_t senderStampResInitialized = 5018;
            const int16_t senderStampFinishSignal = 5015;
            const int16_t senderStampEbsState = 5002;
            const int16_t senderStampEbsArmed = 5008;
            const int16_t senderStampEbsActivated = 5009;
            const int16_t senderStampEbsSpeakerOn = 5010;
            const int16_t senderStampWaitToDrive = 5011;
            const int16_t senderStampBrakesReleased = 5007;
            const int16_t senderStampTsOn = 5006;
            const int16_t senderStampAsMission = 5004;
            const int16_t senderStampVehicleSpeed = 5017;


            if (LYNX19GW_TEST_CAN_MESSAGE_1_FRAME_ID == canFrameID) {
                lynx19gw_test_can_message_1_t tmp;
                if (0 == lynx19gw_test_can_message_1_unpack(&tmp, src, len)) {
                    {
                        opendlv::cfsdProxyCANReading::Test msg;
                        msg.testCanMessage1(static_cast<int8_t>(lynx19gw_test_can_message_1_test_message_decode(tmp.test_message)));
                        if (VERBOSE) {
                            std::stringstream sstr;
                            msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                       [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                       []() {});
                            std::cout << sstr.str() << std::endl;
                        }
                        od4.send(msg, ts, ID);
                    }
                }
            }
            else if (LYNX19GW_TEST_CAN_MESSAGE_2_FRAME_ID == canFrameID) {
                lynx19gw_test_can_message_2_t tmp;
                    if (0 == lynx19gw_test_can_message_2_unpack(&tmp, src, len)) {
                    {
                        opendlv::cfsdProxyCANReading::Test msg;
                        msg.testCanMessage2(static_cast<int8_t>(lynx19gw_test_can_message_2_test_message_decode(tmp.test_message)));
                        if (VERBOSE) {
                            std::stringstream sstr;
                            msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                       [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                       []() {});
                            std::cout << sstr.str() << std::endl;
                        }
                        od4.send(msg, ts, ID);
                    }
                }
            }
            else if (LYNX19GW_TEST_CAN_MESSAGE_3_FRAME_ID == canFrameID) {
                lynx19gw_test_can_message_3_t tmp;
                    if (0 == lynx19gw_test_can_message_3_unpack(&tmp, src, len)) {
                        opendlv::cfsdProxyCANReading::Test msg;
                        msg.testCanMessage3(static_cast<int8_t>(lynx19gw_test_can_message_3_test_message_decode(tmp.test_message)));
                        if (VERBOSE) {
                            std::stringstream sstr;
                            msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                       [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                       []() {});
                            std::cout << sstr.str() << std::endl;
                        }
                        od4.send(msg, ts, ID);

                }
            }            
            else if (LYNX19GW_APPS_1_FRAME_ID == canFrameID) {
                lynx19gw_apps_1_t tmp;
                    if (0 == lynx19gw_apps_1_unpack(&tmp, src, len)) {
                    {
                        opendlv::cfsdProxyCANReading::Sensors msg;
                        msg.apps1throttlePercentage(static_cast<float>(lynx19gw_apps_1_throttle_percentage_decode(tmp.throttle_percentage)));
                        if (VERBOSE) {
                            std::stringstream sstr;
                            msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                       [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                       []() {});
                            std::cout << sstr.str() << std::endl;
                        } 
                        od4.send(msg, ts, ID);
                    }
                }
            }
            else if (LYNX19GW_APPS_2_FRAME_ID == canFrameID) {
                lynx19gw_apps_2_t tmp;
                    if (0 == lynx19gw_apps_2_unpack(&tmp, src, len)) {
                    {
                        opendlv::cfsdProxyCANReading::Sensors msg;
                        msg.apps2throttlePercentage(static_cast<float>(lynx19gw_apps_2_throttle_percentage_decode(tmp.throttle_percentage)));
                        if (VERBOSE) {
                            std::stringstream sstr;
                            msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                       [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                       []() {});
                            std::cout << sstr.str() << std::endl;
                        } 
                        od4.send(msg, ts, ID);
                    }
                }
            }
            else if (LYNX19GW_HYDRAULIC_BRAKE_PRESSURE_1_FRAME_ID == canFrameID) {
                lynx19gw_hydraulic_brake_pressure_1_t tmp;
                    if (0 == lynx19gw_hydraulic_brake_pressure_1_unpack(&tmp, src, len)) {
                    {
                        opendlv::cfsdProxyCANReading::Sensors msg;
                        msg.hydraulicPressure1(static_cast<float>(lynx19gw_hydraulic_brake_pressure_1_hydraulic_pressure_decode(tmp.hydraulic_pressure)));
                        if (VERBOSE) {
                            std::stringstream sstr;
                            msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                       [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                       []() {});
                            std::cout << sstr.str() << std::endl;
                        } 
                        od4.send(msg, ts, ID);
                    }
                }
            }
            else if (LYNX19GW_HYDRAULIC_BRAKE_PRESSURE_2_FRAME_ID == canFrameID) {
                lynx19gw_hydraulic_brake_pressure_2_t tmp;
                    if (0 == lynx19gw_hydraulic_brake_pressure_2_unpack(&tmp, src, len)) {
                    {
                        opendlv::cfsdProxyCANReading::Sensors msg;
                        msg.hydraulicPressure2(static_cast<float>(lynx19gw_hydraulic_brake_pressure_2_hydraulic_pressure_decode(tmp.hydraulic_pressure)));
                        if (VERBOSE) {
                            std::stringstream sstr;
                            msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                       [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                       []() {});
                            std::cout << sstr.str() << std::endl;
                        } 
                        od4.send(msg, ts, ID);
                    }
                }
            }
            else if (LYNX19GW_HYDRAULIC_BRAKE_PRESSURE_2_FRAME_ID == canFrameID) {
                lynx19gw_hydraulic_brake_pressure_2_t tmp;
                    if (0 == lynx19gw_hydraulic_brake_pressure_2_unpack(&tmp, src, len)) {
                    {
                        opendlv::cfsdProxyCANReading::Sensors msg;
                        msg.hydraulicPressure2(static_cast<float>(lynx19gw_hydraulic_brake_pressure_2_hydraulic_pressure_decode(tmp.hydraulic_pressure)));
                        if (VERBOSE) {
                            std::stringstream sstr;
                            msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                       [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                       []() {});
                            std::cout << sstr.str() << std::endl;
                        } 
                        od4.send(msg, ts, ID);
                    }
                }
            }
            else if (LYNX19GW_BRAKE_DISK_TEMP_1_FRAME_ID == canFrameID) {
                lynx19gw_brake_disk_temp_1_t tmp;
                    if (0 == lynx19gw_brake_disk_temp_1_unpack(&tmp, src, len)) {
                    {
                        opendlv::cfsdProxyCANReading::Sensors msg;
                        msg.brakeDiscTemp1(static_cast<float>(lynx19gw_brake_disk_temp_1_brake_disk_temp_decode(tmp.brake_disk_temp)));
                        if (VERBOSE) {
                            std::stringstream sstr;
                            msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                       [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                       []() {});
                            std::cout << sstr.str() << std::endl;
                        } 
                        od4.send(msg, ts, ID);
                    }
                }
            }
                else if (LYNX19GW_BRAKE_DISK_TEMP_2_FRAME_ID == canFrameID) {
                lynx19gw_brake_disk_temp_2_t tmp;
                    if (0 == lynx19gw_brake_disk_temp_2_unpack(&tmp, src, len)) {
                    {
                        opendlv::cfsdProxyCANReading::Sensors msg;
                        msg.brakeDiscTemp2(static_cast<float>(lynx19gw_brake_disk_temp_2_brake_disk_temp_decode(tmp.brake_disk_temp)));
                        if (VERBOSE) {
                            std::stringstream sstr;
                            msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                       [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                       []() {});
                            std::cout << sstr.str() << std::endl;
                        } 
                        od4.send(msg, ts, ID);
                    }
                }
            }
            else if (LYNX19GW_DAMPER_POSITION_1_FRAME_ID == canFrameID) {
                lynx19gw_damper_position_1_t tmp;
                    if (0 == lynx19gw_damper_position_1_unpack(&tmp, src, len)) {
                    {
                        opendlv::cfsdProxyCANReading::Sensors msg;
                        msg.damperPosition1(static_cast<float>(lynx19gw_damper_position_1_damper_position_decode(tmp.damper_position)));
                        if (VERBOSE) {
                            std::stringstream sstr;
                            msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                       [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                       []() {});
                            std::cout << sstr.str() << std::endl;
                        } 
                        od4.send(msg, ts, ID);
                    }
                }
            }
            else if (LYNX19GW_DAMPER_POSITION_2_FRAME_ID == canFrameID) {
                lynx19gw_damper_position_2_t tmp;
                    if (0 == lynx19gw_damper_position_2_unpack(&tmp, src, len)) {
                    {
                        opendlv::cfsdProxyCANReading::Sensors msg;
                        msg.damperPosition2(static_cast<float>(lynx19gw_damper_position_2_damper_position_decode(tmp.damper_position)));
                        if (VERBOSE) {
                            std::stringstream sstr;
                            msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                       [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                       []() {});
                            std::cout << sstr.str() << std::endl;
                        } 
                        od4.send(msg, ts, ID);
                    }
                }
            }
            else if (LYNX19GW_PNUEMATIC_PRESSURE_1_FRAME_ID == canFrameID) {
                lynx19gw_pnuematic_pressure_1_t tmp;
                    if (0 == lynx19gw_pnuematic_pressure_1_unpack(&tmp, src, len)) {
                    {
                        opendlv::cfsdProxyCANReading::Sensors msg;
                        msg.pnuematicPressure1(static_cast<float>(lynx19gw_pnuematic_pressure_1_pnuematic_pressure_decode(tmp.pnuematic_pressure)));
                        if (VERBOSE) {
                            std::stringstream sstr;
                            msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                       [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                       []() {});
                            std::cout << sstr.str() << std::endl;
                        } 
                        od4.send(msg, ts, ID);
                    }
                }
            }
            else if (LYNX19GW_PNUEMATIC_PRESSURE_2_FRAME_ID == canFrameID) {
                lynx19gw_pnuematic_pressure_2_t tmp;
                    if (0 == lynx19gw_pnuematic_pressure_2_unpack(&tmp, src, len)) {
                    {
                        opendlv::cfsdProxyCANReading::Sensors msg;
                        msg.pnuematicPressure2(static_cast<float>(lynx19gw_pnuematic_pressure_2_pnuematic_pressure_decode(tmp.pnuematic_pressure)));
                        if (VERBOSE) {
                            std::stringstream sstr;
                            msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                       [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                       []() {});
                            std::cout << sstr.str() << std::endl;
                        } 
                        od4.send(msg, ts, ID);
                    }
                }
            }
            else if (LYNX19GW_PNUEMATIC_PRESSURE_3_FRAME_ID == canFrameID) {
                lynx19gw_pnuematic_pressure_3_t tmp;
                    if (0 == lynx19gw_pnuematic_pressure_3_unpack(&tmp, src, len)) {
                    {
                        opendlv::cfsdProxyCANReading::Sensors msg;
                        msg.pnuematicPressure3(static_cast<float>(lynx19gw_pnuematic_pressure_3_pnuematic_pressure_decode(tmp.pnuematic_pressure)));
                        if (VERBOSE) {
                            std::stringstream sstr;
                            msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                       [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                       []() {});
                            std::cout << sstr.str() << std::endl;
                        } 
                        od4.send(msg, ts, ID);
                    }
                }
            }
            else if (LYNX19GW_STEERING_POSITION_1_FRAME_ID == canFrameID) {
                lynx19gw_steering_position_1_t tmp;
                    if (0 == lynx19gw_steering_position_1_unpack(&tmp, src, len)) {
                    {
                        opendlv::cfsdProxyCANReading::Sensors msg;
                        msg.steeringPosition1(static_cast<float>(lynx19gw_steering_position_1_steering_position_decode(tmp.steering_position)));
                        if (VERBOSE) {
                            std::stringstream sstr;
                            msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                       [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                       []() {});
                            std::cout << sstr.str() << std::endl;
                        } 
                        od4.send(msg, ts, ID);
                    }
                }
            }
            else if (LYNX19GW_STEERING_POSITION_2_FRAME_ID == canFrameID) {
                lynx19gw_steering_position_2_t tmp;
                    if (0 == lynx19gw_steering_position_2_unpack(&tmp, src, len)) {
                    {
                        opendlv::cfsdProxyCANReading::Sensors msg;
                        msg.steeringPosition2(static_cast<float>(lynx19gw_steering_position_2_steering_position_decode(tmp.steering_position)));
                        if (VERBOSE) {
                            std::stringstream sstr;
                            msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                       [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                       []() {});
                            std::cout << sstr.str() << std::endl;
                        } 
                        od4.send(msg, ts, ID);
                    }
                }
            }
            else if (LYNX19GW_FRONT_NODE_STATUS_FRAME_ID == canFrameID) {
                lynx19gw_front_node_status_t tmp;
                    if (0 == lynx19gw_front_node_status_unpack(&tmp, src, len)) {
                    {
                        opendlv::cfsdProxyCANReading::NodeStatus msg;
                        msg.counter(static_cast<uint8_t>(lynx19gw_front_node_status_counter_decode(tmp.counter)));
                        msg.readyToDrive(static_cast<uint8_t>(lynx19gw_front_node_status_ready_to_drive_decode(tmp.ready_to_drive)));
                        if (VERBOSE) {
                            std::stringstream sstr;
                            msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                       [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                       []() {});
                            std::cout << sstr.str() << std::endl;
                        } 
                        od4.send(msg, ts, ID);
                    }
                }
            }
            else if (LYNX19GW_AUTONOMOUS_NODE_STATUS_FRAME_ID == canFrameID) {
                lynx19gw_autonomous_node_status_t tmp;
                    if (0 == lynx19gw_autonomous_node_status_unpack(&tmp, src, len)) {
                    {
                        opendlv::cfsdProxyCANReading::NodeStatus msg;
                        msg.counter(static_cast<uint8_t>(lynx19gw_autonomous_node_status_counter_decode(tmp.counter)));
                        msg.readyToDrive(static_cast<uint8_t>(lynx19gw_autonomous_node_status_ready_to_drive_decode(tmp.ready_to_drive)));
                        if (VERBOSE) {
                            std::stringstream sstr;
                            msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                       [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                       []() {});
                            std::cout << sstr.str() << std::endl;
                        } 
                        od4.send(msg, ts, ID);
                    }
                }
            }            
            else if (LYNX19GW_SAFETY_LAYER_FRAME_ID == canFrameID) {
                lynx19gw_safety_layer_t tmp;
                    if (0 == lynx19gw_safety_layer_unpack(&tmp, src, len)) {
                    {
                        opendlv::cfsdProxyCANReading::SafetyLayer msg;
                        msg.asmsOn(0 < std::fabs(lynx19gw_safety_layer_asms_on_decode(tmp.asms_on)));
                        msg.resState(0 < std::fabs(lynx19gw_safety_layer_res_state_decode(tmp.res_state)));
                        msg.resStopSignal(0 < std::fabs(lynx19gw_safety_layer_res_stop_signal_decode(tmp.res_stop_signal)));
                        msg.resGoSignal(0 < std::fabs(lynx19gw_safety_layer_res_go_signal_decode(tmp.res_go_signal)));
                        msg.resInitialized(0 < std::fabs(lynx19gw_safety_layer_res_initialized_decode(tmp.res_initialized)));
                        msg.brakesReleased(0 < std::fabs(lynx19gw_safety_layer_brakes_released_decode(tmp.brakes_released)));
                        msg.tsOn(0 < std::fabs(lynx19gw_safety_layer_ts_on_decode(tmp.ts_on)));
                        msg.waitToDrive(0 < std::fabs(lynx19gw_safety_layer_wait_to_drive_decode(tmp.wait_to_drive)));
                        if (VERBOSE) {
                            std::stringstream sstr;
                            msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                       [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                       []() {});
                            std::cout << sstr.str() << std::endl;
                        }

                        opendlv::proxy::SwitchStateReading msgAsmsOn;
                        msgAsmsOn.state(msg.asmsOn());
                        od4.send(msgAsmsOn, ts, senderStampAsmsOn);

                        opendlv::proxy::SwitchStateReading msgResState;
                        msgResState.state(msg.resState());
                        od4.send(msgResState, ts, senderStampResState);
                        
                        opendlv::proxy::SwitchStateReading msgResStopSignal;
                        msgResStopSignal.state(msg.resStopSignal());
                        od4.send(msgResStopSignal, ts, senderStampResStopSignal);

                        opendlv::proxy::SwitchStateReading msgResGoSignal;
                        msgResGoSignal.state(msg.resGoSignal());
                        od4.send(msgResGoSignal, ts, senderStampResGoSignal);

                        opendlv::proxy::SwitchStateReading msgResInitialized;
                        msgResInitialized.state(msg.resInitialized());
                        od4.send(msgResInitialized, ts, senderStampResInitialized);

                        opendlv::proxy::SwitchStateRequest msgBrakesReleased;
                        msgBrakesReleased.state(msg.brakesReleased());
                        od4.send(msgBrakesReleased, ts, senderStampBrakesReleased);

                        opendlv::proxy::SwitchStateRequest msgTsOn;
                        msgTsOn.state(msg.tsOn());
                        od4.send(msgTsOn, ts, senderStampTsOn);

                        opendlv::proxy::SwitchStateRequest msgWaitToDrive;
                        msgWaitToDrive.state(msg.waitToDrive());
                        od4.send(msgWaitToDrive, ts, senderStampWaitToDrive);
                    }
                }
            }
            else if (LYNX19GW_VEHICLE_SPEED_FRAME_ID == canFrameID) {
                lynx19gw_vehicle_speed_t tmp;
                    if (0 == lynx19gw_vehicle_speed_unpack(&tmp, src, len)) {
                    {
                        opendlv::cfsdProxyCANReading::VehicleSpeed msg;
                        msg.wheelFrontRight(static_cast<uint16_t>(lynx19gw_vehicle_speed_wheel_front_right_decode(tmp.wheel_front_right)));
                        msg.wheelFrontLeft(static_cast<uint16_t>(lynx19gw_vehicle_speed_wheel_front_left_decode(tmp.wheel_front_left)));
                        msg.wheelRearRight(static_cast<uint16_t>(lynx19gw_vehicle_speed_wheel_rear_right_decode(tmp.wheel_rear_right)));
                        msg.wheelRearLeft(static_cast<uint16_t>(lynx19gw_vehicle_speed_wheel_rear_left_decode(tmp.wheel_rear_left)));
                        if (VERBOSE) {
                            std::stringstream sstr;
                            msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                       [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                       []() {});
                            std::cout << sstr.str() << std::endl;
                        } 
                        opendlv::proxy::SwitchStateReading msgVehicleSpeed;
                        msgVehicleSpeed.state(msg.wheelFrontRight());
                        od4.send(msgVehicleSpeed, ts, senderStampVehicleSpeed);
                    }
                }
            }
            else if (LYNX19GW_EBS_FRAME_ID == canFrameID) {
                lynx19gw_ebs_t tmp;
                    if (0 == lynx19gw_ebs_unpack(&tmp, src, len)) {
                    {
                        opendlv::cfsdProxyCANReading::EBS msg;
                        msg.ebsState(static_cast<int8_t>(lynx19gw_ebs_ebs_state_decode(tmp.ebs_state)));
                        msg.ebsArmed(0 < std::fabs(lynx19gw_ebs_ebs_armed_decode(tmp.ebs_armed)));
                        msg.ebsActivated(0 < std::fabs(lynx19gw_ebs_ebs_activated_decode(tmp.ebs_activated)));
                        msg.ebsSpeakerOn(0 < std::fabs(lynx19gw_ebs_ebs_speaker_on_decode(tmp.ebs_speaker_on)));
                        if (VERBOSE) {
                            std::stringstream sstr;
                            msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                       [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                       []() {});
                            std::cout << sstr.str() << std::endl;
                        } 
                        opendlv::proxy::SwitchStateRequest msgEbsState;
                        msgEbsState.state(msg.ebsState());
                        od4.send(msgEbsState, ts, senderStampEbsState);

                        opendlv::proxy::SwitchStateRequest msgEbsArmed;
                        msgEbsArmed.state(msg.ebsArmed());
                        od4.send(msgEbsArmed, ts, senderStampEbsArmed);

                        opendlv::proxy::SwitchStateRequest msgEbsActivated;
                        msgEbsActivated.state(msg.ebsActivated());
                        od4.send(msgEbsActivated, ts, senderStampEbsActivated);

                        opendlv::proxy::SwitchStateRequest msgEbsSpeakerOn;
                        msgEbsSpeakerOn.state(msg.ebsSpeakerOn());
                        od4.send(msgEbsSpeakerOn, ts, senderStampEbsSpeakerOn);
                    }
                }
            }
            else if (LYNX19GW_AS_MISSION_FRAME_ID == canFrameID) {
                lynx19gw_as_mission_t tmp;
                    if (0 == lynx19gw_as_mission_unpack(&tmp, src, len)) {
                    {
                        opendlv::cfsdProxyCANReading::ASMission msg;
                        msg.missionSelect(static_cast<int8_t>(lynx19gw_as_mission_mission_select_decode(tmp.mission_select)));
                        if (VERBOSE) {
                            std::stringstream sstr;
                            msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                       [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                       []() {});
                            std::cout << sstr.str() << std::endl;
                        } 
                        opendlv::proxy::SwitchStateRequest msgMissionSelect;
                        msgMissionSelect.state(msg.missionSelect());
                        od4.send(msgMissionSelect, ts, senderStampAsMission);
                    }
                }
            }

        };

#ifdef __linux__
        struct sockaddr_can address;
#endif
        int socketCAN;

        std::cerr << "[opendlv-device-cangw-lynx] Opening " << CANDEVICE << "... ";
#ifdef __linux__
        // Create socket for SocketCAN.
        socketCAN = socket(PF_CAN, SOCK_RAW, CAN_RAW);
        if (socketCAN < 0) {
            std::cerr << "failed." << std::endl;

            std::cerr << "[opendlv-device-cangw-lynx] Error while creating socket: " << strerror(errno) << std::endl;
        }

        // Try opening the given CAN device node.
        struct ifreq ifr;
        memset(&ifr, 0, sizeof(ifr));
        strcpy(ifr.ifr_name, CANDEVICE.c_str());
        if (0 != ioctl(socketCAN, SIOCGIFINDEX, &ifr)) {
            std::cerr << "failed." << std::endl;

            std::cerr << "[opendlv-device-cangw-lynx] Error while getting index for " << CANDEVICE << ": " << strerror(errno) << std::endl;
            return retCode;
        }

        // Setup address and port.
        memset(&address, 0, sizeof(address));
        address.can_family = AF_CAN;
        address.can_ifindex = ifr.ifr_ifindex;

        if (bind(socketCAN, reinterpret_cast<struct sockaddr *>(&address), sizeof(address)) < 0) {
            std::cerr << "failed." << std::endl;

            std::cerr << "[opendlv-device-cangw-lynx] Error while binding socket: " << strerror(errno) << std::endl;
            return retCode;
        }
        std::cerr << "done." << std::endl;
#else
        std::cerr << "failed (SocketCAN not available on this platform). " << std::endl;
        return retCode;
#endif

        struct can_frame frame;
        fd_set rfds;
        struct timeval timeout;
        struct timeval socketTimeStamp;
        int32_t nbytes = 0;

        while (od4.isRunning() && socketCAN > -1) {
#ifdef __linux__
            timeout.tv_sec = 1;
            timeout.tv_usec = 0;

            FD_ZERO(&rfds);
            FD_SET(socketCAN, &rfds);

            select(socketCAN + 1, &rfds, NULL, NULL, &timeout);

            if (FD_ISSET(socketCAN, &rfds)) {
                nbytes = read(socketCAN, &frame, sizeof(struct can_frame));
                if ( (nbytes > 0) && (nbytes == sizeof(struct can_frame)) ) {
                    // Get receiving time stamp.
                    if (0 != ioctl(socketCAN, SIOCGSTAMP, &socketTimeStamp)) {
                        // In case the ioctl failed, use traditional vsariant.
                        cluon::data::TimeStamp now{cluon::time::now()};
                        socketTimeStamp.tv_sec = now.seconds();
                        socketTimeStamp.tv_usec = now.microseconds();
                    }
                    cluon::data::TimeStamp sampleTimeStamp;
                    sampleTimeStamp.seconds(socketTimeStamp.tv_sec)
                                   .microseconds(socketTimeStamp.tv_usec);
                    decode(sampleTimeStamp, frame.can_id, frame.data, frame.can_dlc);
                }
            }
#endif
        }

        std::clog << "[opendlv-device-cangw-lynx] Closing " << CANDEVICE << "... ";
        if (socketCAN > -1) {
            close(socketCAN);
        }
        std::clog << "done." << std::endl;

        retCode = 0;
    }
    return retCode;
}

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
        std::cerr << argv[0] << " translates messages from CAN to ODVD messages for PEAK CAN GPS." << std::endl;
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
            else if (LYNX19GW_APPS_FRAME_ID == canFrameID) {
                lynx19gw_apps_t tmp;
                    if (0 == lynx19gw_apps_unpack(&tmp, src, len)) {
                    {
                        opendlv::cfsdProxyCANReading::Apps msg;
                        msg.throttlePercentage(static_cast<float>(lynx19gw_apps_throttle_percentage_decode(tmp.throttle_percentage)));
                        msg.appsFault(static_cast<uint8_t>(lynx19gw_apps_apps_fault_decode(tmp.apps_fault)));
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
            else if (LYNX19GW_SWITCH_STATE_READING_FRAME_ID == canFrameID) {
                lynx19gw_switch_state_reading_t tmp;
                    if (0 == lynx19gw_switch_state_reading_unpack(&tmp, src, len)) {
                    {
                        opendlv::proxy::SwitchStateReading msg;
                        msg.vehicleSpeed(static_cast<float>(lynx19gw_switch_state_reading_vehicle_speed_decode(tmp.vehicle_speed)));
                        msg.asmsOn(static_cast<bool>(lynx19gw_switch_state_reading_asms_on_decode(tmp.asms_on)));
                        msg.saAvailable(static_cast<bool>(lynx19gw_switch_state_reading_sa_available_decode(tmp.sa_available)));
                        msg.resState(static_cast<bool>(lynx19gw_switch_state_reading_res_state_decode(tmp.res_state)));
                        msg.resStopSignal(static_cast<bool>(lynx19gw_switch_state_reading_res_stop_signal_decode(tmp.res_stop_signal)));
                        msg.resGoSignal(static_cast<bool>(lynx19gw_switch_state_reading_res_go_signal_decode(tmp.res_go_signal)));
                        msg.resInitialized(static_cast<bool>(lynx19gw_switch_state_reading_res_initialized_decode(tmp.res_initialized)));
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
            else if (LYNX19GW_SWITCH_STATE_REQUEST_FRAME_ID == canFrameID) {
                lynx19gw_switch_state_request_t tmp;
                    if (0 == lynx19gw_switch_state_request_unpack(&tmp, src, len)) {
                    {
                        opendlv::proxy::SwitchStateRequest msg;
                        msg.finishSignal(static_cast<bool>(lynx19gw_switch_state_request_finish_signal_decode(tmp.finish_signal)));
                        msg.ebsState(static_cast<bool>(lynx19gw_switch_state_request_ebs_state_decode(tmp.ebs_state)));
                        msg.ebsArmed(static_cast<bool>(lynx19gw_switch_state_request_ebs_armed_decode(tmp.ebs_armed)));
                        msg.ebsActivated(static_cast<bool>(lynx19gw_switch_state_request_ebs_activated_decode(tmp.ebs_activated)));
                        msg.ebsSpeakerOn(static_cast<bool>(lynx19gw_switch_state_request_ebs_speaker_on_decode(tmp.ebs_speaker_on)));
                        msg.waitToDrive(static_cast<bool>(lynx19gw_switch_state_request_ebs_wait_to_drive_decode(tmp.ebs_wait_to_drive)));
                        msg.brakesReleased(static_cast<bool>(lynx19gw_switch_state_request_brakes_released_decode(tmp.brakes_released)));
                        msg.tsOn(static_cast<bool>(lynx19gw_switch_state_request_ts_on_decode(tmp.ts_on)));
                        msg.asMission(static_cast<bool>(lynx19gw_switch_state_request_as_mission_decode(tmp.as_mission)));
                        msg.missionSelect(static_cast<bool>(lynx19gw_switch_state_request_mission_select_decode(tmp.mission_select)));
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

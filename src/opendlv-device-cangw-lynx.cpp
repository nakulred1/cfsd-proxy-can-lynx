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
#include <cstdint>
#include <cstring>

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

class TestClass {
    public:
        opendlv::proxy::TestMessageRequest step(double) noexcept;
};

std::mutex as_Sensor_update_mutex;//This is a mutex lock for 


//Test functions

opendlv::proxy::TestMessageRequest TestClass::step(double) noexcept
{
    opendlv::proxy::TestMessageRequest helloWorldMsg;
    helloWorldMsg.testLateral("Hello Lateral");
    helloWorldMsg.testLongitudinal("Hello Longitudinal");
    helloWorldMsg.testSensation("Hello Sensation");
    helloWorldMsg.testSafety("Hello Safety");
    return helloWorldMsg;
}




int32_t main(int32_t argc, char **argv) {
    int32_t retCode{1};
    auto commandlineArguments = cluon::getCommandlineArguments(argc, argv);
    if (0 == commandlineArguments.count("cid") || 0 == commandlineArguments.count("freq")) {
        std::cerr << argv[0] << " translates messages from CAN to ODVD messages and vice versa." << std::endl;
        std::cerr << "Usage:   " << argv[0] << " --cid=<OD4 session> [--id=ID] --can=<name of the CAN device> [--verbose]" << std::endl;
        std::cerr << "         --cid:    CID of the OD4Session to send and receive messages" << std::endl;
        std::cerr << "         --id:     ID to use as senderStamp for sending" << std::endl;
        std::cerr << "Example: " << argv[0] << " --cid=111 --can=can0 --verbose" << std::endl;
    }
    else {
        const std::string CANDEVICE{commandlineArguments["can"]};
        const uint32_t ID{(commandlineArguments["id"].size() != 0) ? static_cast<uint32_t>(std::stoi(commandlineArguments["id"])) : 0};
        const bool VERBOSE{commandlineArguments.count("verbose") != 0};
        float const FREQ = std::stof(commandlineArguments["freq"]);
        double const DT = 1.0 / FREQ;


        // Interface to a running OpenDaVINCI session; here, you can send and receive messages.
        cluon::OD4Session od4{static_cast<uint16_t>(std::stoi(commandlineArguments["cid"]))};

        //Sending test messages to microservices 2020
        TestClass testClass;

        auto atFrequency {[&od4, &VERBOSE, &DT, &testClass]() -> bool {
                cluon::data::TimeStamp ts;
                opendlv::proxy::TestMessageRequest helloWorldMessage = testClass.step(DT); 
                od4.send(helloWorldMessage,ts,1905);
                if (VERBOSE) {
                    std::cout << "Lateral Message = " << helloWorldMessage.testLateral()<<std::endl;
                    std::cout << "Longitudinal Message = " << helloWorldMessage.testLongitudinal()<<std::endl;
                    std::cout << "Sensation Message = " << helloWorldMessage.testSensation()<<std::endl;
                    std::cout << "Safety Message = " << helloWorldMessage.testSafety()<<std::endl;
                    std::cout << "--------------------------------------------------------------" <<std::endl;
                    std::cout << "--------------------------------------------------------------" <<std::endl;
                }
                return true;                
        }};      
        od4.timeTrigger(FREQ, atFrequency);
        std::thread frequencyThread(atFrequency);

        int brakeState = 0;//get the brake pressure to determin braking.
        // Delegate to convert incoming CAN frames into ODVD messages that are broadcast into the OD4Session.
        auto decode = [&od4, VERBOSE, ID,&brakeState](cluon::data::TimeStamp ts, uint16_t canFrameID, uint8_t *src, uint8_t len) {
            if ( (nullptr == src) || (0 == len) ) return;
            // pedals reading
            if (LYNX19GW_NF_NR_SENSORS_1_FRAME_ID == canFrameID) {
                lynx19gw_nf_nr_sensors_1_t tmp;
                if (0 == lynx19gw_nf_nr_sensors_1_unpack(&tmp, src, len)) {
                    opendlv::proxyCANReading::PedalRatio msg;
                    msg.brake(lynx19gw_nf_nr_sensors_1_brake_decode(tmp.brake));
                    msg.throttle(lynx19gw_nf_nr_sensors_1_throttle_decode(tmp.throttle));
                    // The following block is automatically added to demonstrate how to display the received values.
                    if (VERBOSE){
                        std::stringstream sstr;
                        msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                []() {});
                        std::cout << sstr.str() << std::endl;
                    }
                    opendlv::proxy::PedalPositionReading msgThrottlePedalReading;
                    msgThrottlePedalReading.position(msg.throttle());
                    od4.send(msgThrottlePedalReading,ts,1902);
                    
                    opendlv::proxy::PedalPositionReading msgBrakePedalReading;
                    msgBrakePedalReading.position(msg.brake());
                    od4.send(msgBrakePedalReading,ts,1901);
                }
            }
            // wheels speed Front Reading
            if (LYNX19GW_NF_NR_SENSORS_2_FRAME_ID == canFrameID) {
                lynx19gw_nf_nr_sensors_2_t tmp;
                if (0 == lynx19gw_nf_nr_sensors_2_unpack(&tmp, src, len)) {
                    opendlv::proxyCANReading::WheelSpeedFront msg;
                    msg.wheelFrontLeft(lynx19gw_nf_nr_sensors_2_wheel_speed_fl_decode(tmp.wheel_speed_fl));
                    msg.wheelFrontRight(lynx19gw_nf_nr_sensors_2_wheel_speed_fr_decode(tmp.wheel_speed_fr));
                    // The following block is automatically added to demonstrate how to display the received values.
                    if (VERBOSE) {
                        std::stringstream sstr;
                        msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                []() {});
                        std::cout << sstr.str() << std::endl;
                    }
                    opendlv::proxy::WheelSpeedReading msgWheelFrontRight;
                    msgWheelFrontRight.wheelSpeed(msg.wheelFrontRight());
                    od4.send(msgWheelFrontRight, ts, 1903); // 1903 for Front Right

                    opendlv::proxy::WheelSpeedReading msgWheelFrontLeft;
                    msgWheelFrontLeft.wheelSpeed(msg.wheelFrontLeft());
                    od4.send(msgWheelFrontLeft, ts, 1904); // 1904 for Front Left
                }
            }

            // wheels speed Rare Reading
            if (LYNX19GW_NR_DL_SENSORS_1_FRAME_ID == canFrameID) {
                lynx19gw_nr_dl_sensors_1_t tmp;
                if (0 == lynx19gw_nr_dl_sensors_1_unpack(&tmp, src, len)) {
                    opendlv::proxyCANReading::WheelSpeedRare msg;
                    msg.wheelRareLeft(lynx19gw_nr_dl_sensors_1_wheel_speed_rl_decode(tmp.wheel_speed_rl));
                    msg.wheelRareRight(lynx19gw_nr_dl_sensors_1_wheel_speed_rr_decode(tmp.wheel_speed_rr));
                    // The following block is automatically added to demonstrate how to display the received values.
                    if (VERBOSE) {
                        std::stringstream sstr;
                        msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                    [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                    []() {});
                        std::cout << sstr.str() << std::endl;
                    }

                    opendlv::proxy::WheelSpeedReading msgWheelRareRight;
                    msgWheelRareRight.wheelSpeed(msg.wheelRareRight());
                    od4.send(msgWheelRareRight, ts, 1901); // 1901 for Rare Right
                    
                    opendlv::proxy::WheelSpeedReading msgWheelRareLeft;
                    msgWheelRareLeft.wheelSpeed(msg.wheelRareLeft());
                    od4.send(msgWheelRareLeft, ts, 1902); //1902 for Rare Left

                }
            }

           
            
            // AS status Reading
            if (LYNX19GW_DL_AS_STATUS_FRAME_ID == canFrameID) {
                lynx19gw_dl_as_status_t tmp;
                if (0 == lynx19gw_dl_as_status_unpack(&tmp, src, len)) {
                    opendlv::proxyCANReading::AsStatus msg;
                    msg.asMission(lynx19gw_dl_as_status_as_mission_decode(tmp.as_mission));
                    msg.brakeFront(lynx19gw_dl_as_status_brake_front_decode(tmp.brake_front));
                    msg.brakeRear(lynx19gw_dl_as_status_brake_rear_decode(tmp.brake_rear));
                    msg.dlStatus(lynx19gw_dl_as_status_dl_status_decode(tmp.dl_status));
                    msg.accSoC(lynx19gw_dl_as_status_acc_so_c_decode(tmp.acc_so_c));
                    // The following block is automatically added to demonstrate how to display the received values.
                    if (VERBOSE) {
                        std::stringstream sstr;
                        msg.accept([](uint32_t, const std::string &, const std::string &) {},
                                [&sstr](uint32_t, std::string &&, std::string &&n, auto v) { sstr << n << " = " << v << '\n'; },
                                []() {});
                        std::cout << sstr.str() << std::endl;
                    }
                    
                    opendlv::proxy::SwitchStateReading msgAMI;
                    msgAMI.state(msg.asMission());
                    od4.send(msgAMI,ts,1406);

                    opendlv::proxy::PedalPositionReading msgBrakeFront;
                    msgBrakeFront.position(msg.brakeFront());
                    brakeState = msg.brakeFront();//update brake pressure
                    od4.send(msgBrakeFront,ts,1922);


                    opendlv::proxy::PedalPositionReading msgBrakeRare;
                    msgBrakeRare.position(msg.brakeRear());
                    od4.send(msgBrakeRare,ts,1923);

                    opendlv::proxy::VoltageReading msgAccSoC;
                    msgAccSoC.voltage(msg.accSoC());
                    od4.send(msgAccSoC,ts,1921);

                    opendlv::proxy::SwitchStateReading msgDlStatus;
                    msgDlStatus.state(msg.dlStatus());
                    od4.send(msgDlStatus,ts,1924);



                }
            }   
        };
        //testFunction();
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
        
// Encode Vehicle State
        opendlv::proxyCANWriting::ASStatus msgASStatus;
        auto onSwitchStateReading = [&msgASStatus,VERBOSE](cluon::data::Envelope &&env){
            opendlv::proxy::SwitchStateReading sstateReading = cluon::extractMessage<opendlv::proxy::SwitchStateReading>(std::move(env));
            std::lock_guard<std::mutex> l(as_Sensor_update_mutex);
            if(env.senderStamp() == 1401 ){//Switch AS State
                msgASStatus.asState(sstateReading.state());
                if (VERBOSE){
                    std::cerr << "received asState:"<< sstateReading.state() <<std::endl;
                }
            }else if(env.senderStamp() == 1404){// Ready to drive
                msgASStatus.asRedyToDrive(sstateReading.state());
                if (VERBOSE){
                    std::cerr << "received asRedyToDrive:"<< sstateReading.state() <<std::endl;
                }
            }
        };
        od4.dataTrigger(opendlv::proxy::SwitchStateReading::ID(), onSwitchStateReading);

        auto onGroundSteeringReading=[&msgASStatus,VERBOSE](cluon::data::Envelope &&env){
            std::lock_guard<std::mutex> l(as_Sensor_update_mutex);
            opendlv::proxy::GroundSteeringReading groundSpeedReading =  cluon::extractMessage<opendlv::proxy::GroundSteeringReading>(std::move(env));
            if(env.senderStamp() == 1200){//Steering actuator reading
                msgASStatus.steeringPosition(groundSpeedReading.groundSteering());
                if (VERBOSE){
                    std::cerr << "received steeringPosition:"<< groundSpeedReading.groundSteering() <<std::endl;
                }
            }else if(env.senderStamp() == 1206){//steering rack reading
                msgASStatus.rackPosition(groundSpeedReading.groundSteering());
                if (VERBOSE){
                    std::cerr << "received rackPosition:"<< groundSpeedReading.groundSteering() <<std::endl;
                }
            }
        };
        od4.dataTrigger(opendlv::proxy::GroundSteeringReading::ID(), onGroundSteeringReading);

        auto onPressureReading =[&msgASStatus,VERBOSE](cluon::data::Envelope &&env){
            opendlv::proxy::PressureReading pressureReading = cluon::extractMessage<opendlv::proxy::PressureReading>(std::move(env));

            std::lock_guard<std::mutex> l(as_Sensor_update_mutex);
            if (env.senderStamp() == 1201){ // EBS Line
                msgASStatus.pressureEBSLine(pressureReading.pressure());
                if (VERBOSE){
                    std::cerr << "received pressureEBSLine:"<<pressureReading.pressure()<<std::endl;
                }
            }else if (env.senderStamp() == 1202){ // Service tank
                msgASStatus.pressureService(pressureReading.pressure());
                if (VERBOSE){
                    std::cerr << "received pressureService:"<< pressureReading.pressure()<<std::endl;
                }
            }else if (env.senderStamp() == 1203){ // EBS Act
                msgASStatus.pressureEBSAct(pressureReading.pressure());
                if (VERBOSE){
                    std::cerr << "received pressureEBSAct:"<<pressureReading.pressure()<<std::endl;
                }
            }else if (env.senderStamp() == 1205){ // Service regulator
                msgASStatus.pressureRegulator(pressureReading.pressure());
                if (VERBOSE){
                    std::cerr << "received pressureRegulator:"<<pressureReading.pressure()<<std::endl;
                }
            }
        };
        od4.dataTrigger(opendlv::proxy::PressureReading::ID(), onPressureReading);
        

        // Set the Autonomus sensors sending the messages to via CAN to Datalogger with a certain frequency.
        int AS2DLFREQ = 33; //sest the update to 33 frame
        // writing the AS sensors state to the DL, by packing the current value and send it to the CAN for datalogger.
        auto as2dlThread{[&msgASStatus,&socketCAN,&od4,AS2DLFREQ](){
            auto as2dlAtFrequency{[&msgASStatus,&socketCAN]() -> bool{
            // The following msg would have to be passed to this encoder externally.
            opendlv::proxyCANWriting::ASStatus msgASStatusCpy;
            {
                std::lock_guard<std::mutex> l(as_Sensor_update_mutex);
                msgASStatusCpy = msgASStatus;
            }
            
            lynx19gw_as_dl_sensors_t tmp;
            memset(&tmp, 0, sizeof(tmp));
            tmp.as_state = lynx19gw_as_dl_sensors_as_state_encode(msgASStatusCpy.asState());
            tmp.steering_position = lynx19gw_as_dl_sensors_steering_position_encode(msgASStatusCpy.steeringPosition());
            tmp.rack_position = lynx19gw_as_dl_sensors_rack_position_encode(msgASStatusCpy.rackPosition());
            tmp.pressure_ebs_act = lynx19gw_as_dl_sensors_pressure_ebs_act_encode(msgASStatusCpy.pressureEBSAct());
            tmp.pressure_ebs_line = lynx19gw_as_dl_sensors_pressure_ebs_line_encode(msgASStatusCpy.pressureEBSLine());
            tmp.pressure_service = lynx19gw_as_dl_sensors_pressure_service_encode(msgASStatusCpy.pressureService());
            tmp.pressure_regulator = lynx19gw_as_dl_sensors_pressure_regulator_encode(msgASStatusCpy.pressureRegulator());
            tmp.as_rtd = lynx19gw_as_dl_sensors_as_rtd_encode(msgASStatusCpy.asRedyToDrive());
            // The following statement packs the encoded values into a CAN frame.
            uint8_t buffer[8];
            int len = lynx19gw_as_dl_sensors_pack(buffer, &tmp, 8);
            if ( (0 < len) && (-1 < socketCAN) ) {
#ifdef __linux__
                struct can_frame frame;
                frame.can_id = LYNX19GW_AS_DL_SENSORS_FRAME_ID;
                frame.can_dlc = len;
                memcpy(frame.data, buffer, 8);
                int32_t nbytes = ::write(socketCAN, &frame, sizeof(struct can_frame));
                if (!(0 < nbytes)) {
                    std::clog << "[SocketCANDevice] Writing ID = " << frame.can_id << ", LEN = " << +frame.can_dlc << ", strerror(" << errno << "): '" << strerror(errno) << "'" << std::endl;
                }
#endif
            }
            return true;
            }};
            od4.timeTrigger(AS2DLFREQ, as2dlAtFrequency);
        }};
        // creat a thread for updating because timetrigger will block the program
        std::thread dashboardThread(as2dlThread);
    
        // Torque setting Left and Right
        // Sending the Torque request via CAN tiggered by the Left torque (only after right value is updated). Right value is updating. 
        // another   is brake is not larger than 3 brakeState>2
        bool torqueRightGet = false;
        int torqueRightValue = 0;
        auto onTorqueRequest = [&torqueRightValue,&torqueRightGet,&socketCAN,&brakeState,VERBOSE](cluon::data::Envelope &&env){
            opendlv::proxy::TorqueRequest torqueReq = cluon::extractMessage<opendlv::proxy::TorqueRequest>(std::move(env));
            if(env.senderStamp() == 1501 ){//Right motor 
                torqueRightGet = true;
                torqueRightValue = torqueReq.torque();
            }else if(env.senderStamp() == 1500){// Left motor only send when torque Right and Left both received
                int tmpTorqueLeftValue  = torqueReq.torque();
                int tmpTorqueRightValue = torqueRightValue;
                if(torqueRightGet == true){
                    torqueRightGet = false;
                    //send the message
                    // Message to encode: LYNX19GW_AS_TORQUE_REQ_FRAME_ID
                    if(brakeState >= 2){
                        tmpTorqueRightValue = 0;
                        tmpTorqueLeftValue  = 0;
                    }
                    lynx19gw_as_torque_req_t tmp;
                    memset(&tmp, 0, sizeof(tmp));
                    // The following msg would have to be passed to this encoder externally.
                    opendlv::proxyCANWriting::ASTorque msg;
                    tmp.torque_set_point_left = lynx19gw_as_torque_req_torque_set_point_left_encode(tmpTorqueLeftValue);
                    tmp.torque_set_point_right = lynx19gw_as_torque_req_torque_set_point_right_encode(tmpTorqueRightValue);
                    //The following statement packs the encoded values into a CAN frame.
                    if (VERBOSE){
                        std::clog << "Received msg Torque: Left: " << tmp.torque_set_point_left << " Right: "<< tmp.torque_set_point_right;
                    }
                    uint8_t buffer[8];
                    int len = lynx19gw_as_torque_req_pack(buffer, &tmp, 8);
                    if ( (0 < len) && (-1 < socketCAN) ) {
#ifdef __linux__
                        struct can_frame frame;
                        frame.can_id = LYNX19GW_AS_TORQUE_REQ_FRAME_ID;
                        frame.can_dlc = len;
                        memcpy(frame.data, buffer, 8);
                        int32_t nbytes = ::write(socketCAN, &frame, sizeof(struct can_frame));
                        if (VERBOSE){
                            std::clog<<"wrote!"<<std::endl;
                        }
                        if (!(0 < nbytes)) {
                            std::clog << "[SocketCANDevice] Writing ID = " << frame.can_id << ", LEN = " << +frame.can_dlc << ", strerror(" << errno << "): '" << strerror(errno) << "'" << std::endl;
                        }
#endif
                }
                
            }
        }};
        od4.dataTrigger(opendlv::proxy::TorqueRequest::ID(), onTorqueRequest);

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


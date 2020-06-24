### CAN Mapping

lynx-v0.1.0.odvd <-> lynx19gw.dbc

|    CAN message    |       CAN signal       | Lynx message                            |    msg signal     | sensor/req/log |      unit       |
| :---------------: | :--------------------: | --------------------------------------- | :---------------: | :------------: | :-------------: |
| AS_Torque_Req*[1] | Torque_Set_Point_Right | opendlv.proxyCANWriting.ASTorque        |    torqueRight    |      req       |     0~24cNm     |
|                   | Torque_Set_Point_Left  |                                         |    torqueLeft     |      req       |       cNm       |
|  NR_DL_Sensors_1  |     Wheel_Speed_RR     | opendlv.proxyCANReading.WheelSpeedRare  |  wheelRareRight   |     sensor     |  rpm or rad/s   |
|                   |     Wheel_Speed_RL     |                                         |   wheelRareLeft   |     sensor     |  rpm or rad/s   |
|  NF_NR_Sensors_2  |     Wheel_Speed_FR     | opendlv.proxyCANReading.WheelSpeedFront |  wheelFrontRight  |     sensor     |  rpm or rad/s   |
|                   |     Wheel_Speed_FL     |                                         |  wheelFrontLeft   |     sensor     |  rpm or rad/s   |
|  NF_NR_Sensors_1  |         Brake          | opendlv.proxyCANReading.PedalRatio      |       brake       |     sensor     |        %        |
|                   |        Throttle        |                                         |     throttle      |     sensor     |        %        |
|   DL_AS_Status    |    accumulatorSoC      | opendlv.proxyCANReading.AsStatus        |      accSoC       |     sensor     | State of Charge |
|                   |    Brake_Front*[2]     |                                         |    brakeFront     |     sensor     |        %        |
|                   |     Brake_Rear*[3]     |                                         |     brakeRear     |     sensor     |        ?        |
|                   |       DL_Status        |                                         |     dlStatus      |     sensor     |       0/1       |
|                   |       AS_Mission       |                                         |     asMission     |     sensor     |       0-8       |
|   AS_DL_Sensors   |         AS_RTD         | opendlv.proxyCANWriting.ASStatus        |   asRedyToDrive   |      log       |       1/0       |
|                   |   Steering_Position    |                                         | steeringPosition  |      log       |       mm        |
|                   |     Rack_Position      |                                         |   rackPosition    |      log       |       mm        |
|                   |    Pressure_Service    |                                         |  pressureService  |      log       |       bar       |
|                   |   Pressure_Regulator   |                                         | pressureRegulator |      log       |       bar       |
|                   |   Pressure_EBS_Line    |                                         |  pressureEBSLine  |      log       |       bar       |
|                   |    Pressure_EBS_Act    |                                         |  pressureEBSAct   |      log       |       bar       |
|                   |        AS_State        |                                         |      asState      |      log       |     states      |

**CFSD20 new signals**

|    CAN message    |       CAN signal       | Lynx message                            |    msg signal     | sensor/req/log |      unit       |
| :---------------: | :--------------------: | --------------------------------------- | :---------------: | :------------: | :-------------: |
| xxxx              |    ASMSisOn            | opendlv.proxyCANReading.xxxxxx          |    ASMSisOn    |      gpio         |     0/1         |
| xxxx              |    SDCisOpen           | opendlv.proxyCANReading.xxxxxx          |    SDCisOpen   |      gpio         |     0/1         |
| xxxx              |    LongitudinalSpeed   | opendlv.proxyCANReading.xxxxxx          |  LongitudinalSpeed   |      sensor/filter   |     [m/s]      |
| xxxx              |    asHeartbeat         | opendlv.proxyCANWriting.xxxxxx          |  asHeartbeat         |      gpio   |    0/1     |
| xxxx              |    VoltSeg1Cell1           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell1    |      sensor       |     [V]        |
| xxxx              |    VoltSeg1Cell2           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell2    |      sensor       |     [V]        |
| xxxx              |    VoltSeg1Cell3           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell3    |      sensor       |     [V]        |
| xxxx              |    VoltSeg1Cell4           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell4    |      sensor       |     [V]        |
| xxxx              |    VoltSeg1Cell5           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell5    |      sensor       |     [V]        |
| xxxx              |    VoltSeg1Cell6           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell6    |      sensor       |     [V]        |
| xxxx              |    VoltSeg1Cell7           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell7    |      sensor       |     [V]        |
| xxxx              |    VoltSeg1Cell8           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell8    |      sensor       |     [V]        |
| xxxx              |    VoltSeg1Cell9           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell9    |      sensor       |     [V]        |
| xxxx              |    VoltSeg1Cell10           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell10    |      sensor       |     [V]        |
| xxxx              |    VoltSeg1Cell11          | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell11    |      sensor       |     [V]        |
| xxxx              |    VoltSeg1Cell12          | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell12    |      sensor       |     [V]        |
| xxxx              |    VoltSeg1Cell13           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell13    |      sensor       |     [V]        |
| xxxx              |    VoltSeg1Cell14           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell14    |      sensor       |     [V]        |
| xxxx              |    VoltSeg1Cell15           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell15    |      sensor       |     [V]        |
| xxxx              |    VoltSeg1Cell16           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell16    |      sensor       |     [V]        |
| xxxx              |    VoltSeg1Cell17           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell17    |      sensor       |     [V]        |
| xxxx              |    VoltSeg1Cell18           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell18    |      sensor       |     [V]        |
| xxxx              |    VoltSeg1Cell19           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell19    |      sensor       |     [V]        |
| xxxx              |    VoltSeg1Cell20           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell20    |      sensor       |     [V]        |
| xxxx              |    VoltSeg1Cell21           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell21    |      sensor       |     [V]        |
| xxxx              |    VoltSeg1Cell22           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell22    |      sensor       |     [V]        |
| xxxx              |    VoltSeg1Cell23           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell23    |      sensor       |     [V]        |
| xxxx              |    TempSeg1Cell1           | opendlv.proxyCANReading.xxxxxx          |    TempSeg1Cell1    |      sensor       |     [degC]        |
| xxxx              |    TempSeg1Cell2           | opendlv.proxyCANReading.xxxxxx          |    TempSeg1Cell2    |      sensor       |     [degC]        |
| xxxx              |    TempSeg1Cell3           | opendlv.proxyCANReading.xxxxxx          |    TempSeg1Cell3    |      sensor       |     [degC]        |
| xxxx              |    TempSeg1Cell4           | opendlv.proxyCANReading.xxxxxx          |    TempSeg1Cell4    |      sensor       |     [degC]        |
| xxxx              |    TempSeg1Cell5           | opendlv.proxyCANReading.xxxxxx          |    TempSeg1Cell5   |      sensor       |     [degC]        |
| xxxx              |    VoltSeg2Cell1           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell1    |      sensor       |     [V]        |
| xxxx              |    VoltSeg2Cell2           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell2    |      sensor       |     [V]        |
| xxxx              |    VoltSeg2Cell3           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell3    |      sensor       |     [V]        |
| xxxx              |    VoltSeg2Cell4           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell4    |      sensor       |     [V]        |
| xxxx              |    VoltSeg2Cell5           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell5    |      sensor       |     [V]        |
| xxxx              |    VoltSeg2Cell6           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell6    |      sensor       |     [V]        |
| xxxx              |    VoltSeg2Cell7           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell7    |      sensor       |     [V]        |
| xxxx              |    VoltSeg2Cell8           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell8    |      sensor       |     [V]        |
| xxxx              |    VoltSeg2Cell9           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell9    |      sensor       |     [V]        |
| xxxx              |    VoltSeg2Cell10           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell10    |      sensor       |     [V]        |
| xxxx              |    VoltSeg2Cell11          | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell11    |      sensor       |     [V]        |
| xxxx              |    VoltSeg2Cell12          | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell12    |      sensor       |     [V]        |
| xxxx              |    VoltSeg2Cell13           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell13    |      sensor       |     [V]        |
| xxxx              |    VoltSeg2Cell14           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell14    |      sensor       |     [V]        |
| xxxx              |    VoltSeg2Cell15           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell15    |      sensor       |     [V]        |
| xxxx              |    VoltSeg2Cell16           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell16    |      sensor       |     [V]        |
| xxxx              |    VoltSeg2Cell17           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell17    |      sensor       |     [V]        |
| xxxx              |    VoltSeg2Cell18           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell18    |      sensor       |     [V]        |
| xxxx              |    VoltSeg2Cell19           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell19    |      sensor       |     [V]        |
| xxxx              |    VoltSeg2Cell20           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell20    |      sensor       |     [V]        |
| xxxx              |    VoltSeg2Cell21           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell21    |      sensor       |     [V]        |
| xxxx              |    VoltSeg2Cell22           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell22    |      sensor       |     [V]        |
| xxxx              |    VoltSeg2Cell23           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell23    |      sensor       |     [V]        |
| xxxx              |    TempSeg2Cell1           | opendlv.proxyCANReading.xxxxxx          |    TempSeg2Cell1    |      sensor       |     [degC]        |
| xxxx              |    TempSeg2Cell2           | opendlv.proxyCANReading.xxxxxx          |    TempSeg2Cell2    |      sensor       |     [degC]        |
| xxxx              |    TempSeg2Cell3           | opendlv.proxyCANReading.xxxxxx          |    TempSeg2Cell3    |      sensor       |     [degC]        |
| xxxx              |    TempSeg2Cell4           | opendlv.proxyCANReading.xxxxxx          |    TempSeg2Cell4    |      sensor       |     [degC]        |
| xxxx              |    TempSeg2Cell5           | opendlv.proxyCANReading.xxxxxx          |    TempSeg2Cell5   |      sensor       |     [degC]        |
| xxxx              |    VoltSeg3Cell1           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell1    |      sensor       |     [V]        |
| xxxx              |    VoltSeg3Cell2           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell2    |      sensor       |     [V]        |
| xxxx              |    VoltSeg3Cell3           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell3    |      sensor       |     [V]        |
| xxxx              |    VoltSeg3Cell4           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell4    |      sensor       |     [V]        |
| xxxx              |    VoltSeg3Cell5           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell5    |      sensor       |     [V]        |
| xxxx              |    VoltSeg3Cell6           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell6    |      sensor       |     [V]        |
| xxxx              |    VoltSeg3Cell7           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell7    |      sensor       |     [V]        |
| xxxx              |    VoltSeg3Cell8           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell8    |      sensor       |     [V]        |
| xxxx              |    VoltSeg3Cell9           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell9    |      sensor       |     [V]        |
| xxxx              |    VoltSeg3Cell10           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell10    |      sensor       |     [V]        |
| xxxx              |    VoltSeg3Cell11          | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell11    |      sensor       |     [V]        |
| xxxx              |    VoltSeg3Cell12          | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell12    |      sensor       |     [V]        |
| xxxx              |    VoltSeg3Cell13           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell13    |      sensor       |     [V]        |
| xxxx              |    VoltSeg3Cell14           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell14    |      sensor       |     [V]        |
| xxxx              |    VoltSeg3Cell15           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell15    |      sensor       |     [V]        |
| xxxx              |    VoltSeg3Cell16           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell16    |      sensor       |     [V]        |
| xxxx              |    VoltSeg3Cell17           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell17    |      sensor       |     [V]        |
| xxxx              |    VoltSeg3Cell18           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell18    |      sensor       |     [V]        |
| xxxx              |    VoltSeg3Cell19           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell19    |      sensor       |     [V]        |
| xxxx              |    VoltSeg3Cell20           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell20    |      sensor       |     [V]        |
| xxxx              |    VoltSeg3Cell21           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell21    |      sensor       |     [V]        |
| xxxx              |    VoltSeg3Cell22           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell22    |      sensor       |     [V]        |
| xxxx              |    VoltSeg3Cell23           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell23    |      sensor       |     [V]        |
| xxxx              |    TempSeg3Cell1           | opendlv.proxyCANReading.xxxxxx          |    TempSeg3Cell1    |      sensor       |     [degC]        |
| xxxx              |    TempSeg3Cell2           | opendlv.proxyCANReading.xxxxxx          |    TempSeg3Cell2    |      sensor       |     [degC]        |
| xxxx              |    TempSeg3Cell3           | opendlv.proxyCANReading.xxxxxx          |    TempSeg3Cell3    |      sensor       |     [degC]        |
| xxxx              |    TempSeg3Cell4           | opendlv.proxyCANReading.xxxxxx          |    TempSeg3Cell4    |      sensor       |     [degC]        |
| xxxx              |    TempSeg3Cell5           | opendlv.proxyCANReading.xxxxxx          |    TempSeg3Cell5   |      sensor       |     [degC]        |
| xxxx              |    VoltSeg4Cell1           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell1    |      sensor       |     [V]        |
| xxxx              |    VoltSeg4Cell2           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell2    |      sensor       |     [V]        |
| xxxx              |    VoltSeg4Cell3           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell3    |      sensor       |     [V]        |
| xxxx              |    VoltSeg4Cell4           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell4    |      sensor       |     [V]        |
| xxxx              |    VoltSeg4Cell5           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell5    |      sensor       |     [V]        |
| xxxx              |    VoltSeg4Cell6           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell6    |      sensor       |     [V]        |
| xxxx              |    VoltSeg4Cell7           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell7    |      sensor       |     [V]        |
| xxxx              |    VoltSeg4Cell8           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell8    |      sensor       |     [V]        |
| xxxx              |    VoltSeg4Cell9           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell9    |      sensor       |     [V]        |
| xxxx              |    VoltSeg4Cell10           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell10    |      sensor       |     [V]        |
| xxxx              |    VoltSeg4Cell11          | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell11    |      sensor       |     [V]        |
| xxxx              |    VoltSeg4Cell12          | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell12    |      sensor       |     [V]        |
| xxxx              |    VoltSeg4Cell13           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell13    |      sensor       |     [V]        |
| xxxx              |    VoltSeg4Cell14           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell14    |      sensor       |     [V]        |
| xxxx              |    VoltSeg4Cell15           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell15    |      sensor       |     [V]        |
| xxxx              |    VoltSeg4Cell16           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell16    |      sensor       |     [V]        |
| xxxx              |    VoltSeg4Cell17           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell17    |      sensor       |     [V]        |
| xxxx              |    VoltSeg4Cell18           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell18    |      sensor       |     [V]        |
| xxxx              |    VoltSeg4Cell19           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell19    |      sensor       |     [V]        |
| xxxx              |    VoltSeg4Cell20           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell20    |      sensor       |     [V]        |
| xxxx              |    VoltSeg4Cell21           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell21    |      sensor       |     [V]        |
| xxxx              |    VoltSeg4Cell22           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell22    |      sensor       |     [V]        |
| xxxx              |    VoltSeg4Cell23           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell23    |      sensor       |     [V]        |
| xxxx              |    TempSeg4Cell1           | opendlv.proxyCANReading.xxxxxx          |    TempSeg4Cell1    |      sensor       |     [degC]        |
| xxxx              |    TempSeg4Cell2           | opendlv.proxyCANReading.xxxxxx          |    TempSeg4Cell2    |      sensor       |     [degC]        |
| xxxx              |    TempSeg4Cell3           | opendlv.proxyCANReading.xxxxxx          |    TempSeg4Cell3    |      sensor       |     [degC]        |
| xxxx              |    TempSeg4Cell4           | opendlv.proxyCANReading.xxxxxx          |    TempSeg4Cell4    |      sensor       |     [degC]        |
| xxxx              |    TempSeg4Cell5           | opendlv.proxyCANReading.xxxxxx          |    TempSeg4Cell5   |      sensor       |     [degC]        |
| xxxx              |    VoltSeg5Cell1           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell1    |      sensor       |     [V]        |
| xxxx              |    VoltSeg5Cell2           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell2    |      sensor       |     [V]        |
| xxxx              |    VoltSeg5Cell3           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell3    |      sensor       |     [V]        |
| xxxx              |    VoltSeg5Cell4           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell4    |      sensor       |     [V]        |
| xxxx              |    VoltSeg5Cell5           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell5    |      sensor       |     [V]        |
| xxxx              |    VoltSeg5Cell6           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell6    |      sensor       |     [V]        |
| xxxx              |    VoltSeg5Cell7           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell7    |      sensor       |     [V]        |
| xxxx              |    VoltSeg5Cell8           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell8    |      sensor       |     [V]        |
| xxxx              |    VoltSeg5Cell9           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell9    |      sensor       |     [V]        |
| xxxx              |    VoltSeg5Cell10           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell10    |      sensor       |     [V]        |
| xxxx              |    VoltSeg5Cell11          | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell11    |      sensor       |     [V]        |
| xxxx              |    VoltSeg5Cell12          | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell12    |      sensor       |     [V]        |
| xxxx              |    VoltSeg5Cell13           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell13    |      sensor       |     [V]        |
| xxxx              |    VoltSeg5Cell14           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell14    |      sensor       |     [V]        |
| xxxx              |    VoltSeg5Cell15           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell15    |      sensor       |     [V]        |
| xxxx              |    VoltSeg5Cell16           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell16    |      sensor       |     [V]        |
| xxxx              |    VoltSeg5Cell17           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell17    |      sensor       |     [V]        |
| xxxx              |    VoltSeg5Cell18           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell18    |      sensor       |     [V]        |
| xxxx              |    VoltSeg5Cell19           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell19    |      sensor       |     [V]        |
| xxxx              |    VoltSeg5Cell20           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell20    |      sensor       |     [V]        |
| xxxx              |    VoltSeg5Cell21           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell21    |      sensor       |     [V]        |
| xxxx              |    VoltSeg5Cell22           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell22    |      sensor       |     [V]        |
| xxxx              |    VoltSeg5Cell23           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell23    |      sensor       |     [V]        |
| xxxx              |    TempSeg5Cell1           | opendlv.proxyCANReading.xxxxxx          |    TempSeg5Cell1    |      sensor       |     [degC]        |
| xxxx              |    TempSeg5Cell2           | opendlv.proxyCANReading.xxxxxx          |    TempSeg5Cell2    |      sensor       |     [degC]        |
| xxxx              |    TempSeg5Cell3           | opendlv.proxyCANReading.xxxxxx          |    TempSeg5Cell3    |      sensor       |     [degC]        |
| xxxx              |    TempSeg5Cell4           | opendlv.proxyCANReading.xxxxxx          |    TempSeg5Cell4    |      sensor       |     [degC]        |
| xxxx              |    TempSeg5Cell5           | opendlv.proxyCANReading.xxxxxx          |    TempSeg5Cell5   |      sensor       |     [degC]        |
| xxxx              |    VoltSeg6Cell1           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell1    |      sensor       |     [V]        |
| xxxx              |    VoltSeg6Cell2           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell2    |      sensor       |     [V]        |
| xxxx              |    VoltSeg6Cell3           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell3    |      sensor       |     [V]        |
| xxxx              |    VoltSeg6Cell4           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell4    |      sensor       |     [V]        |
| xxxx              |    VoltSeg6Cell5           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell5    |      sensor       |     [V]        |
| xxxx              |    VoltSeg6Cell6           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell6    |      sensor       |     [V]        |
| xxxx              |    VoltSeg6Cell7           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell7    |      sensor       |     [V]        |
| xxxx              |    VoltSeg6Cell8           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell8    |      sensor       |     [V]        |
| xxxx              |    VoltSeg6Cell9           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell9    |      sensor       |     [V]        |
| xxxx              |    VoltSeg6Cell10           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell10    |      sensor       |     [V]        |
| xxxx              |    VoltSeg6Cell11          | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell11    |      sensor       |     [V]        |
| xxxx              |    VoltSeg6Cell12          | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell12    |      sensor       |     [V]        |
| xxxx              |    VoltSeg6Cell13           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell13    |      sensor       |     [V]        |
| xxxx              |    VoltSeg6Cell14           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell14    |      sensor       |     [V]        |
| xxxx              |    VoltSeg6Cell15           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell15    |      sensor       |     [V]        |
| xxxx              |    VoltSeg6Cell16           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell16    |      sensor       |     [V]        |
| xxxx              |    VoltSeg6Cell17           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell17    |      sensor       |     [V]        |
| xxxx              |    VoltSeg6Cell18           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell18    |      sensor       |     [V]        |
| xxxx              |    VoltSeg6Cell19           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell19    |      sensor       |     [V]        |
| xxxx              |    VoltSeg6Cell20           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell20    |      sensor       |     [V]        |
| xxxx              |    VoltSeg6Cell21           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell21    |      sensor       |     [V]        |
| xxxx              |    VoltSeg6Cell22           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell22    |      sensor       |     [V]        |
| xxxx              |    VoltSeg6Cell23           | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell23    |      sensor       |     [V]        |
| xxxx              |    TempSeg6Cell1           | opendlv.proxyCANReading.xxxxxx          |    TempSeg6Cell1    |      sensor       |     [degC]        |
| xxxx              |    TempSeg6Cell2           | opendlv.proxyCANReading.xxxxxx          |    TempSeg6Cell2    |      sensor       |     [degC]        |
| xxxx              |    TempSeg6Cell3           | opendlv.proxyCANReading.xxxxxx          |    TempSeg6Cell3    |      sensor       |     [degC]        |
| xxxx              |    TempSeg6Cell4           | opendlv.proxyCANReading.xxxxxx          |    TempSeg6Cell4    |      sensor       |     [degC]        |
| xxxx              |    TempSeg6Cell5           | opendlv.proxyCANReading.xxxxxx          |    TempSeg6Cell5   |      sensor       |     [degC]        |

*[1] math equation: from speed to torque see: opendlv-logic-action-motion-cfsd

*[2] The Brake Front reading = brake pedal Ratio

*[3] The Brake Rare reading read Data type not confirmed



### Lynx Message to OpenDLV message

lynx-v0.1.0.odvd <-> opendlv-standard-message-set-v0.9.7.odvd

|            OpenDLV message            | sender stamp | Lynx message                            |    msg signal     | sensor/req/log |      unit       |
| :-----------------------------------: | :----------: | --------------------------------------- | :---------------: | :------------: | :-------------: |
|     opendlv.proxy.TorqueRequest     |     1501     | opendlv.proxyCANWriting.ASTorque        |    torqueRight    |      req       |     0~24cNm     |
|                                       |     1500     |                                         |    torqueLeft     |      req       |       cNm       |
|    opendlv.proxy.WheelSpeedReading    |     1901     | opendlv.proxyCANReading.WheelSpeedRare  |  wheelRareRight   |     sensor     |      Km/h       |
|                                       |     1902     |                                         |   wheelRareLeft   |     sensor     |      Km/h       |
|                                       |     1903     | opendlv.proxyCANReading.WheelSpeedFront |  wheelFrontRight  |     sensor     |      Km/h       |
|                                       |     1904     |                                         |  wheelFrontLeft   |     sensor     |      Km/h       |
|         PedalPositionReading          |     1901     | opendlv.proxyCANReading.PedalRatio      |       brake       |     sensor     |        %        |
|                                       |     1902     |                                         |     throttle      |     sensor     |        %        |
|     opendlv.proxy.VoltageReading      |     1921     | opendlv.proxyCANReading.AsStatus        |      accSoC       |     sensor     | State of Charge |
|  opendlv.proxy.PedalPositionReading   |     1922     |                                         |    brakeFront     |     sensor     |        %        |
|  opendlv.proxy.PedalPositionReading   |     1923     |                                         |     brakeRear     |     sensor     |        ?        |
|  opendlv.proxy.SwitchStateReading   |     1924     |                                         |     dlStatus      |     sensor     |       0/1       |
|  opendlv.proxy.SwitchStateReading   |     1406     |                                         |     asMission     |     sensor     |       0-8       |
|  opendlv.proxy.SwitchStateReading   |     1404     | opendlv.proxyCANWriting.ASStatus        |   asRedyToDrive   |      log       |       1/0       |
| opendlv.proxy.GroundSteeringReading |     1200     |                                         | steeringPosition  |      log       |       mm        |
|                                       |     1206     |                                         |   rackPosition    |      log       |       mm        |
|    opendlv.proxy.PressureReading    |     1202     |                                         |  pressureService  |      log       |       bar       |
|                                       |     1205     |                                         | pressureRegulator |      log       |       bar       |
|                                       |     1201     |                                         |  pressureEBSLine  |      log       |       bar       |
|                                       |     1203     |                                         |  pressureEBSAct   |      log       |       bar       |
|  opendlv.proxy.SwitchStateReading   |     1401     |                                         |      asState      |      log       |     states      |

**CFSD20 new signals**

|            OpenDLV message            | sender stamp | Lynx message                            |    msg signal     | sensor/req/log |      unit       |
| :-----------------------------------: | :----------: | --------------------------------------- | :---------------: | :------------: | :-------------: |
|  opendlv.proxy.SwitchStateReading     |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    ASMSisOn       |      gpio      |     0/1         |
|  opendlv.proxy.SwitchStateReading     |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    SDCisOpen      |      gpio      |     0/1         |
|  opendlv.proxy.GroundSpeedReading     |     xxxx     | opendlv.proxyCANReading.xxxxxx          |  LongitudinalSpeed   |      sensor/filter   |     [m/s]      |
|  opendlv.proxy.SwitchStateRequest     |     xxxx     | opendlv.proxyCANWriting.xxxxxx          |  asHeartbeat     |      gpio      |     0/1         |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell1      |      sensor      |      [V]         |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell2    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell3    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell4    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell5    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell6    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell7    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell8    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell9    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell10    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell11    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell12    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell13    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell14    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell15    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell16    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell17    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell18    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell19    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell20    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell21    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell22    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg1Cell23    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg1Cell1    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg1Cell2    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg1Cell3    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg1Cell4    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg1Cell5   |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell1    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell2    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell3    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell4    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell5    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell6    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell7    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell8    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell9    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell10    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell11    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell12    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell13    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell14    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell15    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell16    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell17    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell18    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell19    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell20    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell21    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell22    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg2Cell23    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg2Cell1    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg2Cell2    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg2Cell3    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg2Cell4    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg2Cell5   |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell1    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell2    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell3    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell4    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell5    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell6    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell7    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell8    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell9    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell10    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell11    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell12    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell13    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell14    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell15    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell16    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell17    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell18    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell19    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell20    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell21    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell22    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg3Cell23    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg3Cell1    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg3Cell2    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg3Cell3    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg3Cell4    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg3Cell5   |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell1    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell2    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell3    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell4    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell5    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell6    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell7    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell8    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell9    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell10    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell11    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell12    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell13    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell14    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell15    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell16    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell17    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell18    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell19    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell20    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell21    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell22    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg4Cell23    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg4Cell1    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg4Cell2    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg4Cell3    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg4Cell4    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg4Cell5   |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell1    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell2    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell3    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell4    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell5    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell6    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell7    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell8    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell9    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell10    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell11    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell12    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell13    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell14    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell15    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell16    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell17    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell18    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell19    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell20    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell21    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell22    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg5Cell23    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg5Cell1    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg5Cell2    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg5Cell3    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg5Cell4    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg5Cell5   |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell1    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell2    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell3    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell4    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell5    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell6    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell7    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell8    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell9    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell10    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell11    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell12    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell13    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell14    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell15    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell16    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell17    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell18    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell19    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell20    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell21    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell22    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     |  opendlv.proxyCANReading.xxxxxx          |    VoltSeg6Cell23    |      sensor       |     [V]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg6Cell1    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg6Cell2    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg6Cell3    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg6Cell4    |      sensor       |     [degC]        |
|  opendlv.proxy.VoltageReading         |     xxxx     | opendlv.proxyCANReading.xxxxxx          |    TempSeg6Cell5   |      sensor       |     [degC]        |

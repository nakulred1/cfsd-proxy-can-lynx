#!/usr/bin/python3
from pynput.keyboard import Key, Listener
import can

import cantools
from pprint import pprint
db = cantools.database.load_file('lynx19gw.dbc')
# print(db.messages)
missionselect_message = db.get_message_by_name('AS_MISSION')
ebs_message = db.get_message_by_name('EBS')
safetylayer_message = db.get_message_by_name('SAFETY_LAYER')
# pprint(example_message.signals)
can_bus = can.interface.Bus('vcan0', bustype='socketcan')

# candump vcan0 | cantools decode --single-line lynx19gw.dbc

def on_press(key):
    check_key(key)

def on_release(key):
    if key == Key.esc:
        return False

def check_key(key):
    """
    # Put Your Code Here:
    """
    if str(key) == "'a'": # Mission select messsage
        print("Success!")
        data = missionselect_message.encode({'Mission_Select': 4})
        message = can.Message(arbitration_id=missionselect_message.frame_id, data=data)
        can_bus.send(message)
    elif str(key) == "'s'": # Set EBS Armed
        print("Success!")
        data = ebs_message.encode({'EBS_State': 0, 'EBS_Armed': 1, 'EBS_Activated': 0, 'EBS_Speaker_On': 0})
        message = can.Message(arbitration_id=ebs_message.frame_id, data=data)
        can_bus.send(message)
    elif str(key) == "'d'": # AS OFF > AS READY
        print("Success!")
        data = safetylayer_message.encode({'ASMS_On': 1, 'RES_State': 0, 'RES_Stop_Signal': 0, 'RES_Go_Signal': 0, 'RES_Initialized': 1, 'Brakes_Released': 0, 'TS_On': 1, 'Wait_To_Drive': 0, 'Finished_Signal': 0, 'AS_State': 0, 'AS_Heartbeat': 0})
        message = can.Message(arbitration_id=safetylayer_message.frame_id, data=data)
        can_bus.send(message)  
    elif str(key) == "'f'": # AS READY > AS DRIVING
        print("Success!")
        data = safetylayer_message.encode({'ASMS_On': 1, 'RES_State': 0, 'RES_Stop_Signal': 0, 'RES_Go_Signal': 1, 'RES_Initialized': 1, 'Brakes_Released': 0, 'TS_On': 1, 'Wait_To_Drive': 1, 'Finished_Signal': 0, 'AS_State': 0, 'AS_Heartbeat': 1})
        message = can.Message(arbitration_id=safetylayer_message.frame_id, data=data)
        can_bus.send(message)
    else:
        print("Failure!")

# Collect events until released
with Listener(
        on_press=on_press,
        on_release=on_release) as listener:
    listener.join()
    



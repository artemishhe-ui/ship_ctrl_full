from inputs import get_gamepad
import socket


#DIRECTION  : 1 - forward , -1 - backward, 0 - stay
#TURN       : 1 - right   , -1 - left    , 0 - straight 
#GAMEPAD_MOD: 0 - standart,  1 - fasts 


def analise_gamepad(event, data):

    if event.state == 0:
        print("skipping futction")
        return data
    
    print("Analising button...")
    if event.code == "ABS_HAT0Y":
        if event.state != 0:
            data["direction"] -= (event.state * (1 + data["gamepad_mod"]))

    if event.code == "ABS_HAT0X":
        if event.state != 0:
            data["turn"] += (event.state * (1 + data["gamepad_mod"]))
        
    if event.code == "BTN_NORTH":
        data["direction"] = 0

    if event.code == "BTTN_EAST":
        data["turn"] = 0

    if event.code == "BTN_START":
        print("button start")
        print("Окончание работы")
        get_gamepad()
        get_gamepad()
        get_gamepad()       
        data["turn"], data["direction"], data["work"] = 0, 0 ,0
        return data

    if event.code == "BTN_SELECT":
        data["gamepad_mod"] += event.state
        if data["gamepad_mod"] > 1:
            data["gamepad_mod"] = 0

    if data["direction"] >= 1:
        data["direction"] = 1
    elif data["direction"] <= -1:
        data["direction"] = -1

    if data["turn"] >= 1:
        data["turn"] = 1
    elif data["turn"] <= -1:
        data["turn"] = -1
    get_gamepad()
    get_gamepad()
    get_gamepad()
        

    return data

    

'''from inputs import get_gamepad


def main():
    """Just print out some event infomation when the gamepad is used."""
    while 1:
        events = get_gamepad()
        for event in events:
            print(event.ev_type, event.code, event.state)


if __name__ == "__main__":
    main()'''
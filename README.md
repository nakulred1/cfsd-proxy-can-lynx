# cfsd-proxy-can-lynx
cfsd proxy CAN getway

Mapping the CAN messages to Opendlv messages

This version is for the communicate with the lynx car

messages:

The mapping info of messages can be found at CAN Mapping.md

lynx-v0.1.0.odvd is the message set for talking to CAN should only be used in these CAN getway microservice.

lynx19gw.dbc is the CAN database file which is a reference for decoding and encoding the CAN message.

lynx19gw.dbc.map is the mapping setting file for the microservice knowing how to map the messsages.

Messege senderStamps See: CAN Mapping.md



**Instructions to run the microservice**

First clone the git repository with

```
git clone https://git.chalmers.se/cfs/driverless20/cfsd-proxy-can-lynx.git
```

Then go to the directory and checkout to branch test_messages

```
cd cfsd-proxy-can-lynx/
git checkout test_messages_recieve
```

Now you can see the files that are in test_messages_recieve branch in remote

Then install can utilities

```
sudo apt-get install can-utils
```

Then setup a virtual can 

```
source vcan_setup.sh
```

Now you can build the microservice:

```
source building_recieve.sh
```

Then run the microservice:

```
source running_recieve.sh
```
In another terminal window:

```
git checkout test_messages
source building.sh
source running.sh
```

Now you can see messages are recieved in the first terminal.



**Optional things you can try**

generate the dbc map file:

```
docker run --rm -ti -v $PWD/src/:/in -w /in chalmersrevere/dbc2odvd-amd64:v0.0.6 generateHeaderOnly.sh lynx19gw.dbc lynx-v0.1.0.odvd
```

get the code Snippet:

```
docker run --rm -ti -v $PWD/src/:/in -w /in chalmersrevere/dbc2odvd-amd64:v0.0.6 generateMappingCodeSnippet.awk lynx19gw.dbc.map
```

watch the CAN message:

```
candump vcan0
```

*If you were able to do all the above steps, Great Work!! :grinning:*
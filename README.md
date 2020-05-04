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



Instructions to run the microservice

First install can utilities

```
apt-get install can-utils
```

Then setup a virtual can 

```
source vcan_setup.sh
```

Now you can build the microservice:

```
source building.sh
```

Then run the microservice:

```
source running.sh
```


Optional steps

generate the dbc map file:

```
docker run --rm -ti -v $PWD/src/:/in -w /in dbc2odvd:v0.0.0 generateHeaderOnly.sh lynx19gw.dbc lynx.odvd
```

get the code Snippet:

```
docker run --rm -ti -v $PWD/src/:/in -w /in dbc2odvd:v0.0.0 generateMappingCodeSnippet.awk lynx19gw.dbc.map
```

watch the CAN message:

```
candump vcan0
```
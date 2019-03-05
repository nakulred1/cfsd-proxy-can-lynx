# cfsd-proxy-cangw
cfsd proxy CAN getway

Mapping the CAN messages to Opendlv messages

This version is for the communicate with the lynx car

messages:

The mapping info of messages can be found at CAN Mapping.md

lynx-v0.1.0.odvd is the message set for talking to CAN should only be used in these CAN getway microservice.

lynx19gw.dbc is the CAN database file which is a reference for decoding and encoding the CAN message.

lynx19gw.dbc.map is the mapping setting file for the microservice knowing how to map the messsages.

Messege senderStamps See: CAN Mapping.md

run the microservice:

```
docker run --rm -ti --net=host --privileged cfsd-proxy-cangw:v0.0.0 --cid=111 --can=can0 --verbose
```


generate the dbc map file:

```
docker run --rm -ti -v $PWD/src/:/in -w /in dbc2odvd:v0.0.0 generateHeaderOnly.sh lynx19gw.dbc lynx.odvd
```

get the code Snippet:

```
docker run --rm -ti -v $PWD/src/:/in -w /in dbc2odvd:v0.0.0 generateMappingCodeSnippet.awk lynx19gw.dbc.map
```

Setting the CAN:

```
sudo ip link set can0 up type can bitrate 500000
sudo ifconfig can0 up
```

watch the CAN message:

```
candump can0
```
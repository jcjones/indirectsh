# Indirect Shell
*Get at a server without opening a port.*

This project consists of a daemon, `indirectshd`, which listens to an indirect messaging service (like [SAIFE](https://www.saifeinc.com/)  or [PubNub](https://www.pubnub.com/)) to receive commmands and send responses. This lets you do clever things like find and manage servers without punching a hole in your firewall.

## SAIFE Module
The SAIFE module provides strong bidirectional authentication based on ECDSA with the 384-bit prime field, and covers messages using AES in Galois Counter Mode.

## PubNub Module
The PubNub module provides no real security; anyone who knows your `publish_key` on PubNub can command your server.

# Installation

This program requires several dependencies:
* libpubnub [github](https://github.com/pubnub/c#installation)
* libjson
* libcurlpp

To install dependencies on debian, you can do:

```shell
sudo apt-get install libevent-dev libjson0-dev libcurl4-openssl-dev libssl-dev libcurlpp-dev

# PubNub
git clone https://github.com/pubnub/c.git libpubnub-c
cd libpubnub-c
make
sudo make install
```

# License
This software is licensed under terms of the Apache 2.0 license. It utilizes external libraries from SAIFE, Inc. and Pubnub.


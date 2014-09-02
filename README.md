# Indirect Shell
*Get at a server without opening a port.*

This project consists of a daemon, `indirectshd`, which listens to an indirect messaging service (like [SAIFE](https://www.saifeinc.com/)  or [PubNub](https://www.pubnub.com/)) to receive commmands and send responses. This lets you do clever things like find and manage servers without punching a hole in your firewall.

## SAIFE Module
The SAIFE module provides strong bidirectional authentication based on ECDSA with the 384-bit prime field, and covers messages using AES in Galois Counter Mode.

The SAIFE module is coming soon; it will be released shortly after SAIFE launches its library.

## PubNub Module
The PubNub module provides no real security; anyone who knows your `publish_key` on PubNub can command your server.

You will need a PubNub account to really play with the shell.

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

Then installing `indirectshd` is a simple matter of running `make` and copying the binary where you like.

```shell
cd indirectsh
make
sudo cp indirectshd /usr/local/bin/
```
TODO: Pull in automake.

# Configuration
You need a configuration file to define your account parameters for your chosen indirection module. It can either be:
* named `ishrc.json` in your current working directory, or
* `.ishrc.json` in your home directory.

The file format is a simple JSON structure:

```json
{
    "pubnub": {
        "subscribe_key" : "demo",
        "publish_key" : "demo",
        "channel" : "my_channel"
    }
}

```

# License
This software is licensed under terms of the Apache 2.0 license. It utilizes external libraries from SAIFE, Inc. and Pubnub.


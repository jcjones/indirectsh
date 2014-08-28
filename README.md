# Indirect Shell
*Get at a server without opening a port.*

This project consists of a daemon, `indirectshd`, which listens to an indirect messaging service (like [SAIFE](https://www.saifeinc.com/)  or [PubNub](https://www.pubnub.com/)) to receive commmands and send responses. This lets you do clever things like find and manage servers without punching a hole in your firewall.

## SAIFE Module
The SAIFE module provides strong bidirectional authentication based on ECDSA with the 384-bit prime field, and covers messages using AES in Galois Counter Mode.

## PubNub Module
The PubNub module provides no real security; anyone who knows your `publish_key` on PubNub can command your server.

# License
This software is licensed under terms of the Apache 2.0 license. It utilizes external libraries from SAIFE, Inc. and Pubnub.


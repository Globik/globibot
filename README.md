globibot
========

# Porting [uap-c](https://github.com/Klowner/uap-c) to the nodejs addon

Some experiments with [Node.js](https://nodejs.org) [N-API](https://nodejs.org/dist/latest-v9.x/docs/api/n-api.html)

# uap-c

It's a C implementation of the user-agent string parser described in ua-parser/uap-core.

# Build Dependencies 

* libyaml
* libpcre3

Node Add-on Example with uap-c for native module

# P.S.

One can end up this project. Alas, javascript version of uap-core is much faster than addon itself. x4 faster. No benefit from C code.

C is a king and shines when it is in the native environments among C-applications. But it is not the case when javascript addon based on C/C++.

Addons are shining when you need some C library solution. For example libnice, stun etc.

# END!

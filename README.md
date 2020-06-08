# SimpleTCP Client/Server
[![Build Status](https://travis-ci.com/sergeyampo/SimpleTCPServer.svg?branch=master)](https://travis-ci.com/sergeyampo/SimpleTCPServer)

A simple TCP client-server application written on C, with worker pool and requests queue. With factorial calculation example.
### Building server and client
You should have **cmake and gcc** installed!
```bash
./src/scripts/build.sh
```
All built files will be written an ./src/build folder.

### Starting server and client
```bash
cd ./src/scripts
./start_server.sh &
./start_client.sh
```

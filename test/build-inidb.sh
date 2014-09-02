#!/bin/sh
g++ -m32 -fPIC -shared -o iniDB.so ../src/main.cpp ../src/base64.cpp ../src/crc32.cpp ../src/ini.cpp ../src/logger.cpp ../src/md5.cpp ../src/privateprofile.cpp

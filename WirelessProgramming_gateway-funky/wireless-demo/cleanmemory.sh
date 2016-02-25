#!/bin/sh

ls -1 /dev/ttyACM* | grep -v ACM0
PORT=$(ls -1 /dev/ttyACM* | grep -v ACM0)
#PORT=ACM2
avrdude -v -v -patmega32u4 -cavr109  -b57600 -e -Ulock:w:0x3F:m -Uefuse:w:0xce:m -Uhfuse:w:0xd8:m -Ulfuse:w:0xff:m -P $PORT
avrdude -v -v -patmega32u4 -cavr109  -b57600 -Uflash:w:CleanMemory.hex:i -Ulock:w:0x2F:m   -P $PORT  || exit

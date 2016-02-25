#!/bin/sh
rm new_firmware.hex*

ls -1 /dev/ttyACM* | grep -v ACM0
PORT=$(ls -1 /dev/ttyACM* | grep -v ACM0)
#PORT=ACM2

avrdude -v -v -patmega32u4 -cavr109  -b57600 -P $PORT -U flash:r:new_firmware.hex20:i
srec_cat new_firmware.hex20  -intel -o new_firmware.hex -intel -Line_Length 44

nezapomenou pridat dva bajty delky na zacatek souboru

Use padhextopage.sh to fix length of hex file

./WirelessProgramming.py -h
 -d                   debug
 -f or -file          HEX file to upload (Default:  flash.hex )
 -t or -target {ID}   Specify WirelessProgramming node target
 -s or -serial {port} Specify serial port of WirelessProgramming gateway (Default:  COM101 )
 -b or -baud {baud}   Specify serial port baud rate (Default:  115200 )
 -h or -help or ?     Print this message


time ./WirelessProgramming.py -d -t 123 -s /dev/ttyACM0 -f WirelessProgramming_node-funky.ino.hex

Sample output

time ./WirelessProgramming.py -d -t 123 -s /dev/ttyACM0 -f Blink.ino.hex
 
TO:123
Moteino: [TO:123:OK]
TARGET SET OK
File found, passing to Moteino...
FLX?

FLX?

Moteino: [FLX?OK]
HANDSHAKE OK!
TX > FLX:0:100000000C94E2000C940A010C940A010C940A016D
Moteino: FLX:0:OK
TX > FLX:1:100010000C940A010C940A010C940A010C940A0134
Moteino: FLX:1:OK
TX > FLX:2:100020000C940A010C940A010C9466060C94F804D2
Moteino: FLX:2:OK
....
TX > FLX:277:10114A0000000000000000FC0643072607360712CD
Moteino: FLX:277:OK
TX > FLX:278:04115A000723070060
Moteino: FLX:278:OK
Moteino: [FLX?OK]
HANDSHAKE OK!
SUCCESS!
 

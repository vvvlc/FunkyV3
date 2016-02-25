#!/bin/sh
echo Padding $1 to 128 to be allign with page size
SZ=$(srec_cat $1 -intel -o - -bin | wc -c)
SZANDLENGTH=$(($SZ + 2))
if [ $SZANDLENGTH -gt 14336 ] ; then
        echo $1 is too big, remove: $(( $SZANDLENGTH - 14336)) bytes
        ls -la $1
        exit
else
        echo We have space for: $((14336-$SZANDLENGTH)) bytes.
fi

srec_cat -generate 0x000 0x002 -l-e-constant $SZ 2 -o len.hex -intel
srec_cat len.hex -intel $1 -intel -offset 0x2 -o len.hex -intel
srec_cat len.hex -intel -fill 0xFF -within len.hex -intel -range-padding 128 -o len.hex -intel -Line_Length 44
tail -n+2 len.hex > $1.padded.hex

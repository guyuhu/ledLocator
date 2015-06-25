CC = iccavr
LIB = ilibw
CFLAGS =  -e -D__ICC_VERSION=722 -DATMega16  -l -g -MLongJump -MHasMul -MEnhanced -Wf-r20_23 -Wf-const_is_flash -DCONST="" 
ASFLAGS = $(CFLAGS) 
LFLAGS =  -g -e:0x4000 -ucrtatmega.o -bfunc_lit:0x54.0x4000 -dram_end:0x45f -bdata:0x60.0x45f -dhwstk_size:30 -beeprom:0.512 -fihx_coff -S2
FILES = ledLoctor.o 

LEDLOCTOR:	$(FILES)
	$(CC) -o LEDLOCTOR $(LFLAGS) @LEDLOCTOR.lk   -lcatmegagr
ledLoctor.o: D:\ICC\include\iom16v.h D:\ICC\include\macros.h D:\ICC\include\AVRdef.h
ledLoctor.o:	ledLoctor.c
	$(CC) -c $(CFLAGS) ledLoctor.c

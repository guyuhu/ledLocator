NOTE: AVR Code addresses are word addresses
All other addresses (including ones in FLASH) are byte addresses

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                           idata   0054   0023 =     35. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       0054  __idata_start
       0077  __idata_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            text   0078   01FE =    510. bytes (rel,con,rom)

       Addr  Global Symbol
      -----  --------------------------------
       003C  __text_start
       003C  __start
       005E  _exit
       005F  __delay_us
       0072  _checkOut
       00A1  _SPI1_Send
       00C5  _setMessage
       00E1  _timer0_init
       00E8  _init_devices
       00F9  _main
       0107  _timer0_ovf_isr
       012B  pop_xgset003C
       0130  push_xgsetF0FC
       0132  push_xgset30FC
       0134  push_xgset00FC
       0136  push_xgset003C
       013B  __text_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                            data   0060   0023 =     35. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0060  __data_start
       0060  _guideMessage
       0068  _idMessage
       0070  _coordMessage
       0078  _checkMessage
       0080  _addTime
       0082  _endlineFlag
       0083  __data_end

Area                               Addr   Size   Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                             bss   0083   0001 =      1. bytes (rel,con,ram)

       Addr  Global Symbol
      -----  --------------------------------
       0083  __bss_start
       0083  _i
       0084  __bss_end

Area                               Start  End    Decimal Bytes (Attributes)
--------------------------------   ----   ----   ------- ----- ------------
                          vector   0000   0028 =     40. bytes (abs,ovr,rom)

Files Linked      [ module(s) ]

D:\ICC\lib\crtatmega.o	[ crtatmega.s ]
ledLoctor.o	[ ledLoctor.c ]
<library>	[ gpop2.s, gpush.s ]

User Global Definitions

ram_end = 0x45f
hwstk_size = 0x1e

User Base Address Definitions

func_lit = 0x54
data = 0x60
eeprom:0.512


### Programming the Southern Cross SBC in C

Using SDCC and a custom CRT0 (C Run Time 0 'The very beginning' *Wikipedia)
we can write a C program and compile it with SDCC ( Small Device C Compiler) and download it to the
RAM of the Southern Cross SBC to execute.

To take advantage of the monitor subroutines available in the monitor you can use the System Call mechanism in the monitor
which is similar to the CP/M BDOS call.
The system calls are wrapped in a C function in the SCMonitor.c C file and SCmonitor.h header file.

An example C program that emulates the Southern Cross SBC 7 segment display and keyboard monitor using these files is included.


## prerequisites

The Southern Cross Monitor Version 1.8 running on a Southern Cross SBC with a USB to Serial Converter connected to a computer running a terminal program.
Small Device C Compiler (SDCC) 

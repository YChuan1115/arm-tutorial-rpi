#!/bin/sh

arm-none-eabi-gcc -fomit-frame-pointer -Ofast -ftree-loop-distribution -DRPI3 -march=armv8-a -mtune=cortex-a53 -marm -mfpu=neon-fp-armv8 -mfloat-abi=hard -nostartfiles -g -Wl,-T,rpi.x armc-09.c armc-09-cstubs.c armc-09-cstartup.c armc-09-start.S -o kernel.elf
arm-none-eabi-objdump -d kernel.elf | arm-none-eabi-c++filt > kernel.list
arm-none-eabi-objcopy kernel.elf -O binary kernel8-32.img

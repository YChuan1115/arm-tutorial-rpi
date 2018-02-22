#!/bin/sh

arm-none-eabi-gcc -O4 -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -nostartfiles -g -Wl,-T,rpi.x armc-09.c armc-09-cstubs.c armc-09-cstartup.c armc-09-start.S -o kernel.elf
arm-none-eabi-objdump -d kernel.elf | arm-none-eabi-c++filt > kernel.list
arm-none-eabi-objcopy kernel.elf -O binary kernel.img

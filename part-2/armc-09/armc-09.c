/*

    Part of the Raspberry-Pi Bare Metal Tutorials
    Copyright (c) 2013, Brian Sidebotham
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice,
        this list of conditions and the following disclaimer.

    2. Redistributions in binary form must reproduce the above copyright notice,
        this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
    LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
    CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
    SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
    INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
    CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
    ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
    POSSIBILITY OF SUCH DAMAGE.

*/

/*
    C-Library stubs introduced for newlib
*/

#include <string.h>
#include <stdlib.h>

#include "rpi-gpio.h"

#define RPMV_D0	(1 << 0)
#define MD00_PIN	0
#define RA08	(1 << 8)
#define RA09	(1 << 9)
#define RA10	(1 << 10)
#define RA11	(1 << 11)
#define RA12	(1 << 12)
#define RA13	(1 << 13)
#define RA14	(1 << 14)
#define RA15	(1 << 15)
#define LE_A	(1 << 16)
#define LE_B	(1 << 17)
#define LE_D	(1 << 26)
#define RCLK	(1 << 25)
#define RWAIT	(1 << 24)
#define RINT	(1 << 20)
#define RBUSDIR (1 << 22)

#define SLTSL	RA11
#define MREQ	RA10
#define IORQ	RA12
#define RD		RA08
#define WR		RA14
#define RESET	RA13

unsigned char ROM[] = {
#include "rom.c"
};	

/** GPIO Register set */
volatile unsigned int* gpio = (unsigned int*)GPIO_BASE;

/** Main function - we'll never return from here */
void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{
    int loop;
    unsigned int* counters;
	unsigned char *addr;
	unsigned short addr0;
	unsigned char byte;
	int i = 0;
	
    /* Set the LED GPIO pin to an output to drive the LED */
    gpio[GPIO_GPFSEL0] = 0x49249249;
	gpio[GPIO_GPFSEL1] = 0x49249249;
	gpio[GPIO_GPFSEL2] = (1 << 6*3);
	
	gpio[GPIO_GPCLR0] = LE_A | 0xffff;
	gpio[GPIO_GPSET0] = LE_B;

    while(1)
    {
		if (!(gpio[GPIO_GPLEV0] & SLTSL))
		{
			gpio[GPIO_GPSET0] = (LE_A);
			gpio[GPIO_GPCLR0] = (LE_B | 0xffff);
			asm ( "nop; nop;" );
			asm ( "nop; nop;" );
			asm ( "nop; nop;" );
			asm ( "nop; nop;" );
			asm ( "nop; nop;" );
			asm ( "nop; nop;" );
			asm ( "nop; nop;" );
			asm ( "nop; nop;" );
			asm ( "nop; nop;" );
			asm ( "nop; nop;" );
			byte = ROM[((gpio[GPIO_GPLEV0] & 0xffff) - 0x4000)];
			gpio[GPIO_GPSET0] = 0xff & (gpio[GPIO_GPLEV0]);
			gpio[GPIO_GPSET0] = LE_B;
			gpio[GPIO_GPCLR0] = (LE_A);
			while(!(gpio[GPIO_GPLEV0] & SLTSL));
		}		
		
    }
}

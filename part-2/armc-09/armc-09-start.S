
//  Part of the Raspberry-Pi Bare Metal Tutorials
//  Copyright (c) 2013, Brian Sidebotham
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are met:
//
//  1. Redistributions of source code must retain the above copyright notice,
//      this list of conditions and the following disclaimer.
//
//  2. Redistributions in binary form must reproduce the above copyright notice,
//      this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
//  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
//  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
//  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
//  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
//  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
//  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
//  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
//  POSSIBILITY OF SUCH DAMAGE.

.equ	SCTLR_ENABLE_DATA_CACHE,        0x4
.equ	SCTLR_ENABLE_BRANCH_PREDICTION, 0x800
.equ	SCTLR_ENABLE_INSTRUCTION_CACHE, 0x1000

.section ".text.startup"

.global _start
.global _get_stack_pointer

_start:
    // Set it at 64MB which we know our application will not crash into
    // and we also know will be available to the ARM CPU. No matter what
    // settings we use to split the memory between the GPU and ARM CPU
    // ldr     sp, =0x8000
    ldr     sp, =(64 * 1024 * 1024)

    // R0 = System Control Register
    mrc p15,0,r0,c1,c0,0
	
    // Enable caches and branch prediction
//    orr r0,#SCTLR_ENABLE_BRANCH_PREDICTION
//    orr r0,#SCTLR_ENABLE_DATA_CACHE
    orr r0,#SCTLR_ENABLE_INSTRUCTION_CACHE
	
    // System Control Register = R0
    mcr p15,0,r0,c1,c0,0
	
    // Run the c startup function - should not return and will call kernel_main
    b       _cstartup

_inf_loop:
    b       _inf_loop


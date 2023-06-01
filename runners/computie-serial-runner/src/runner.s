
    .global run_test
    .global current_initial
    .global current_final

    .global jump_to_address
    .global jump_back_address

    .section .text

    .equ    REG_PC, 68
    .equ    PREFETCH, 74


.macro save_registers
    | Save registers
    move.l      %a6, -(%sp)
    move.l      %a5, -(%sp)
    move.l      %a4, -(%sp)
    move.l      %a3, -(%sp)
    move.l      %a2, -(%sp)
    move.l      %a1, -(%sp)
    move.l      %a0, -(%sp)
    move.l      %d7, -(%sp)
    move.l      %d6, -(%sp)
    move.l      %d5, -(%sp)
    move.l      %d4, -(%sp)
    move.l      %d3, -(%sp)
    move.l      %d2, -(%sp)
    move.l      %d1, -(%sp)
    move.l      %d0, -(%sp)
.endm


.macro restore_registers
    | Restore registers
    move.l      (%sp)+, %d0
    move.l      (%sp)+, %d1
    move.l      (%sp)+, %d2
    move.l      (%sp)+, %d3
    move.l      (%sp)+, %d4
    move.l      (%sp)+, %d5
    move.l      (%sp)+, %d6
    move.l      (%sp)+, %d7
    move.l      (%sp)+, %a0
    move.l      (%sp)+, %a1
    move.l      (%sp)+, %a2
    move.l      (%sp)+, %a3
    move.l      (%sp)+, %a4
    move.l      (%sp)+, %a5
    move.l      (%sp)+, %a6
.endm


run_test:
    save_registers
    move.l      %a7, stack_pointer

    move.l      #current_initial, %a0

    move.l      #exit_test, %a1
    move.l      %a1, jump_back_address

    | TODO load the memory

    /*
    | Load the instruction data into memory
    move.l      (PREFETCH,%a0), %a1
    move.l      (REG_PC,%a0), %a2
lprefetch:
    move.l      (%a1)+, %d0
    move.l      %d0, (%a2)+
    cmp.l       0, %d0
    bne         lprefetch

    |move.l     (%a2)
    */

    move.l      (REG_PC,%a0), %a1
    move.l      %a1, jump_to_address
    move.w      #0x4e71, (%a1)+
    |move.w      #0x4e76, (%a1)+
    move.w      #0x47f9, (%a1)+
    move.l      (jump_back_address), (%a1)+

    | Load the register values
    move.l      (64,%a0), %a1
    move.l      %a1, %usp
    move.l      (60,%a0), %a7
    move.l      (56,%a0), %a6
    move.l      (52,%a0), %a5
    move.l      (48,%a0), %a4
    move.l      (44,%a0), %a3
    move.l      (40,%a0), %a2
    move.l      (36,%a0), %a1
    | Skip %a0 until the end
    move.l      (28,%a0), %d7
    move.l      (24,%a0), %d6
    move.l      (20,%a0), %d5
    move.l      (16,%a0), %d4
    move.l      (12,%a0), %d3
    move.l      (8,%a0), %d2
    move.l      (4,%a0), %d1
    move.l      (0,%a0), %d0

    | Carefully jump to the target instruction
    move.w      (72,%a0), %sr
    move.l      (32,%a0), %a0
    |jmp         (jump_to_address)
    jmp         0x180000

    | TODO how will you actually call the instruction, and get the proper unmodified resulting state?
    | - you could leave nops and modify the running code live to have the instructions, followed by nops
    |   and then inline read the state
    | - you could insert only the minimal instructions into the prefetch location to save the state,
    |   including a call to a function to save the rest and return
    | - you will need a global variable location to store the context needed to restore the test runner's state
    |   or can you make it so that a reset will go straight into the runner again?
    | - I think a lot of the tests use a PC value of 1000 or something, which is in the Flash area of compute
    |   and I can use the VBR register on 68010, but the tests might not be correct for the 68010... especially
    |   the address exception-causing tests, which would produce a different stack trace format 
    | - I think I'm going to have to either modify the tests to work correctly the 0x100000 memory area, which
    |   might not be possible in a meaningful way, or to modify the computie hardware or build a new board to
    |   test with

exit_test:

    move.l     (stack_pointer), %ssp
    restore_registers
    rts

    .section .data

stack_pointer:
    .long 0x12345678

jump_to_address:
    .long 0x12345678

jump_back_address:
    .long 0x12345678


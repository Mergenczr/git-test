# factorial.s
# Adapted from Robert Plantz Introduction to Computer Architecture
# Computes n! recursively.        
# Calling sequence:
#       edi <- n
#       call    readLn
# returns n!
        .intel_syntax noprefix
# Stack frame
        .equ    nOffset,-4
        .equ    localSize,-16

result:
        .string "result = %i\n"

        .text
        .globl  main
        .type   main, @function
main:
        push    rbp                 # save frame pointer
        mov     rbp, rsp            # set new frame pointer
        add     rsp, localSize      # for local var.

        mov     edi, 5         # hard-coding 5 as n-value
        call    factorial       # passing n to factorial
        mov     esi, eax        # copy result to argument register for printing
        lea     rdi, result[rip]
        call    printf@PLT

        mov     rsp, rbp        # restore previous rsp value
        pop     rbp             # restore previous rbp
        ret
        
factorial:
        push    rbp                 # save frame pointer
        mov     rbp, rsp            # set new frame pointer
        add     rsp, localSize      # for local var.

        cmp     edi, 1       # check for base case
        jle     baseCase                

        mov     nOffset[rbp], edi         # save current n on stack
        sub     edi, 1                  # subtract 1 from n and recurse
        call    factorial
        mul     dword ptr nOffset[rbp]    # n! = n * (n - 1)!
        jmp     done

baseCase:
        mov     eax, 1          # factorial of 1 is 1
        jmp     done

done:
        mov     rsp, rbp            # restore stack pointer
        pop     rbp                 # and caller frame pointer
        ret

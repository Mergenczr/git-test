# sumKtoN.s
# written to help with stack comprehension

        .intel_syntax noprefix
        .text
        .section        .rodata
prompt:
        .string "Enter a low integer and a high integer: "
input:
        .string "%i %i"
result:
        .string "Intermediate: %i\n"
endResult:
        .string "End result: %i\n"

## saving constant offsets for readability
        .equ    k, -4
        .equ    n, -8

        .text
        .globl  main
        .type   main, @function
main:
        push    rbp
        mov     rbp, rsp
        sub     rsp, 16

        lea     rdi, prompt[rip]
        call    printf@PLT

        lea     rdx, n[rbp]           ## address of high integer
        lea     rsi, k[rbp]           ## address of low integer
        lea     rdi, input[rip]       ## format to interpret input
        call    scanf@PLT
    
        mov     eax, 0          #clear return register

loop:
        mov     esi, n[rbp]   # load 2nd argument register
        mov     edi, k[rbp]   # load 1st argument register
        cmp     esi, edi
        je      oddCase     # odd number of values being added
        jb      afterLoop   # if n (stored in esi) is below k (stored in edi)
        push    rax

        call    addTwo

        pop     r8
        add     eax, r8d

        sub     dword ptr n[rbp], 1     # decrement value of n
        inc     dword ptr k[rbp]     # increment value of loop counter
        jmp     loop

afterLoop:
        mov     esi, eax                # copy answer into esi
        lea     rdi, endResult[rip]        # load address of result template string
        call    printf@PLT
        add     rsp, 16     #restore rsp
        pop     rbp
        mov     eax, 0
        ret

oddCase:
        add     eax, dword ptr k[rbp]
        jmp     afterLoop

## Function to add two integers
addTwo:
        push    rbp
        mov     rbp, rsp
        add     edi, esi        # add the two arguments
        mov     eax, edi        # move result into return register
        pop     rbp
        ret

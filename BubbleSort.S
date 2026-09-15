.intel_syntax noprefix

.section .data

# Reference C++ code:
#
# void bubbleSort(vector<int>& v) {
#     int n = v.size();
#
#     for (int i = 0; i < n - 1; i++) {
#         for (int j = 0; j < n - i - 1; j++) {
/*            if (v[j] > v[j + 1]) */
#                 swap(v[j], v[j + 1]);
#         }
#     }
# }
#
# The assembly below follows the same two-loop structure.


array:
    .long 54,37,81,12,95,6,23,68,47,76,29,42

size:                                   
    .long 12                                    

originalMsg:
    .string "Original list: "

sortedMsg:
    .string "\nSorted list: "

format:
    .string "%d "

newline:
    .string "\n"


.section .text

.global main
.extern printf




bubbleSort:

    push rbp                            # bubbleSort(int arr[], int size)
                                        # rdi = array address, esi = size
                                        # r8d = i (outer loop), r9d = j (inner loop)
                                        # rbx = array address, r10d = array size
    mov rbp,rsp

    push rbx

    mov rbx,rdi
    mov r10d,esi

    # i = 0
    mov r8d,0

outerLoop:

                                        # Continue while i < size - 1
    mov eax,r10d
    sub eax,1

    cmp r8d,eax
    jge doneSorting

                                        # j = 0
    mov r9d,0

innerLoop:

                                        # Continue while j < size - i - 1
                                        # The last i elements are already sorted
    mov eax,r10d
    sub eax,r8d
    sub eax,1

    cmp r9d,eax
    jge nextPass

                                        # Compare arr[j] with arr[j + 1]
    mov eax,[rbx+r9*4]
    mov edx,[rbx+r9*4+4]

                                        # If arr[j] <= arr[j + 1], do not swap
    cmp eax,edx
    jle noSwap

                                        # Swap arr[j] and arr[j + 1]
    mov [rbx+r9*4],edx
    mov [rbx+r9*4+4],eax

noSwap:

                                        # j++
    inc r9d
    jmp innerLoop

nextPass:

                                        # i++
    inc r8d
    jmp outerLoop

doneSorting:

    pop rbx
    pop rbp
    ret


main:

    push rbp
    mov rbp,rsp

                                        # Print original list
    lea rdi,originalMsg[rip]
    mov eax,0
    call printf

                                        # Print original array
    lea rbx,array[rip]
    mov r12d,0

printOriginal:

    cmp r12d,12
    jge sortCall

    lea rdi,format[rip]
    mov esi,[rbx+r12*4]

    mov eax,0
    call printf

    inc r12d
    jmp printOriginal


sortCall:

                                        # bubbleSort(array, size)
    lea rdi,array[rip]
    mov esi,size[rip]
    call bubbleSort

                                        # Print sorted list
    lea rdi,sortedMsg[rip]
    mov eax,0
    call printf

                                        # Print sorted array
    lea rbx,array[rip]
    mov r12d,0

printSorted:

    cmp r12d,12
    jge endProgram

    lea rdi,format[rip]
    mov esi,[rbx+r12*4]

    mov eax,0
    call printf

    inc r12d
    jmp printSorted


endProgram:

    lea rdi,newline[rip]
    mov eax,0
    call printf

    mov eax,0

    pop rbp
    ret


.section .note.GNU-stack,"",@progbits
.text

.globl swap
swap:

        pushq   %rbp                # Save frame pointer
        movq    %rsp, %rbp          

        movq    (%rsi),%rcx         # temp = a[i]
        movq    (%rdi),%rax
        movq    %rcx,(%rdi)          # [j] = temp
        movq    %rax,(%rsi)          # [i] = [j]
        
        
        leave
        ret



.globl quicksort_asm

quicksort_asm:                      # rdi = a, rsi = first, rdx = last
                                    # first = 0, last = n-1
                                    # quicksort_asm(long*a, long first, long last)






        pushq   %rbp                # Save frame pointer
        movq    %rsp, %rbp          
                                    
       
        
        cmpq    %rsi,%rdx           # if(last>first)
        jle     afterif1     
        

        subq    $40,%rsp        

                                
        movq    %rdi,-8(%rbp)   # a
                                
        movq    %rsi,-16(%rbp)  # first

        movq    -16(%rbp),%rax
                                
        movq    %rdx,-24(%rbp)  # last

        movq    -24(%rbp),%rdi
        
        movq    %rdi,-32(%rbp)      # j = last
        movq    %rax,-40(%rbp)      # pivot = first
        movq    %rax,%r8            # i = first
      
              

        

while:  
        movq    %r8,%rdi
        cmpq    -32(%rbp) ,%rdi      # while(i<j)
        jge     afterw

whilei: 
        movq    -40(%rbp),%rdi       # [pivot] get location in the array
        salq    $3,%rdi
        addq    -8(%rbp),%rdi
        
        movq    (%rdi),%rdi

        movq    %r8,%rsi       # [i] get location in the array
        salq    $3,%rsi
        addq    -8(%rbp),%rsi
        cmpq    (%rsi),%rdi

        jl      whilej
        movq    %r8,%rdi      # store number i
        cmpq    %rdx,%rdi      # if(i<last)
        jge     whilej
        addq    $1,%r8        # i++
        jmp     whilei

whilej:
        movq    -40(%rbp),%rdi      # a[pivot]
        
        salq    $3,%rdi
        addq    -8(%rbp),%rdi
        movq    (%rdi),%rdi

        movq    -32(%rbp),%rsi      # [j]
        salq    $3,%rsi
        addq    -8(%rbp),%rsi
        cmpq    (%rsi),%rdi

        jge     ifinw
        subq    $1,-32(%rbp)        # j--
        jmp     whilej
ifinw:  
        movq    %r8,%rdi
        cmpq    -32(%rbp) ,%rdi
        jge     while

        

        movq    %r8,%rsi       # a[i]
        salq    $3,%rsi
        addq    -8(%rbp),%rsi

        movq    -32(%rbp) ,%rdi       # a[j]
        salq    $3,%rdi
        addq    -8(%rbp),%rdi

        call    swap
        jmp     while
afterw:
        movq    -40(%rbp),%rdi       # a[pivot]
        salq    $3,%rdi
        addq    -8(%rbp),%rdi

        movq    -32(%rbp) ,%rsi       # a[j]
        salq    $3,%rsi
        addq    -8(%rbp),%rsi

        call    swap




        movq    -32(%rbp) ,%rdx    # quicksort_c(array,first,j-1)
        movq    -16(%rbp),%rsi
        movq    -8(%rbp),%rdi
        subq    $1,%rdx
        call    quicksort_asm

        movq    -32(%rbp),%rsi     # quicksort_c(array,j+1,last)
        movq    -24(%rbp),%rdx
        movq    -8(%rbp),%rdi
        addq    $1,%rsi
        call    quicksort_asm
afterif1:
        leave
        ret
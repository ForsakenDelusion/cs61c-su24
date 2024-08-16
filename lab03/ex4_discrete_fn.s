.globl f # this allows other files to find the function f

# f takes in two arguments:
# a0 is the value we want to evaluate f at
# a1 is the address of the "output" array (read the lab spec for more information).
# The return value should be stored in a0
f:
    # Your code here
    #t2 store the Addr of a1
    mv t2 a1
    #bias
    addi t0 a0 3
    #bias to offset
    slli t1 t0 2
    #stroe the bAddr + offset
    add t2 t2 t1
    #load value of bAddr + offset
    lw a0 0(t2)
    # This is how you return from a function. You'll learn more about this later.
    # This should be the last line in your program.
    jr ra

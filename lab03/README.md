la 加载标签处的地址

ecall 系统调用

In C, we are used to functions looking like ecall(1, t0). In RISC-V, we cannot pass arguments in this way. To pass an argument, we need to place it in an argument register (a0-a7). When the function executes, it will look in these registers for the arguments. (If you haven't seen this in lecture yet, you will soon). The first argument should be placed in a0, the second in a1, etc.

To set up the arguments, we placed a 1 in a0 and we placed the integer that we wanted to print in a1.

Next, let's terminate our program! This also requires ecall

addi a0, x0, 10 # argument to ecall to terminate
ecall # terminate ecall
In this case, ecall only needs one argument. Setting a0 to 10 specifies that we want to terminate the program.

ecall就是通过传递给寄存器不同的参数来执行不同的命令

## EX3

Compare your answer to Question 2 and Question 4. Note that memcheck may change the memory address that malloc returns

应该说明了malloc分配的地址不是固定的，这个意思



在网上看到很多lab03 ex4实现都是错的，并没有根据bias计算index，而是直接无脑在offset上+4来不断访问连续的内存，虽然题目给的测试可以跑通（应为题目是按顺序来测试的），但是一旦调换顺序就不行了


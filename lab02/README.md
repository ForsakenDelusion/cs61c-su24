## 结构体初始化器

```C
Str make_Str(char *str) {
    /* Below is a designated initializer. It creates a Str struct and initializes
       its data field to str and its len field to strlen(str) */
    return (Str){.data=str,.len=strlen(str)};
}
```

`{.data=str,.len=strlen(str)};`这是一个结构体初始化器，前面的(Str)是将其类型转化为Str结构体类型。

## GDB

|Command|Abbreviation|Description|
|---|---|---|
|start|N/A|begin running the program and stop at line 1 in main|
|step|s|execute the current line of code (this command will step into functions)|
|next|n|execute the current line of code (this command will not step into functions)|
|finish|fin|executes the remainder of the current function and returns to the calling function|
|print [arg]|p|prints the value of the argument|
|quit|q|exits gdb|
|break [line num or function name]|b|set a breakpoint at the specified location, use `filename.c:linenum` to set a breakpoint in a specific file|
|conditional break (ex: break 3 if n==4)|(ex: b 3 if n==4)|set a breakpoint at the specified location only if a given condition is met|
|run|r|execute the program until termination or reaching a breakpoint|
|continue|c|continues the execution of a program that was paused|
|backtrace|bt|print one line per frame for frames in the stack|

## Valgrind

e.g.

```shell
#检查一个程序的错误
valgrind ./bork hello

#检查内存泄漏
valgrind --leak-check=full ./bork hello
```

## ex6

## Exercise 6: Using Valgrind to find segfaults

Above, we learned how to debug segfaults using GDB. Now, we're going to use valgrind to do something similar.

There's a bug in `ex6_valgrind`, let's see how we can detect it with valgrind.

1. **Compile** `ex6_valgrind.c`. Notice that there are no compiler errors or warnings, and we're using the `-g` flag in case we need to debug this program in the future.
    
    ```bash
    gcc -g -o ex6_valgrind ex6_valgrind.c
    ```
    
2. **Run** `ex6_valgrind`. Notice that the program doesn't throw any errors.
    
3. **Run** `valgrind` on `ex6_valgrind`. You should see that there are 2 errors.
    
4. **Read** the valgrind output carefully. In `ex6_answers.txt`, answer the following questions. Please don't change the formatting of the file. For question 1 through 7, we are referring to the first `valgrind` error (an invalid write error).
    
    1. How many bytes are the invalid write? (The answer should be a number without any units)
    2. Which function caused the invalid write? (The answer should be the name of the function)
    3. Which function called the answer to question 2? (The answer should be the name of a function)
    4. Which file did the call occur in? (The answer should be the name of a file)
    5. Which line did the call occur on? (The answer should be a number)
    6. How many bytes were actually allocated? (The answer should be a number without any units)
    7. How many bytes should have been allocated? Feel free to read the code. (The answer should be a number without any units)
    8. Are there any memory leaks? (The answer should be Yes or No)
    9. How many bytes were leaked? Write 0 if there are no memory leaks. (The answer should be a number without any units)

```shell
yu@ubuntu:/Users/yu/Documents/studyAbout/codeLearn/cs61c/cs61c-su24/lab02$ valgrind ./ex6_valgrind
==3876== Memcheck, a memory error detector
==3876== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==3876== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==3876== Command: ./ex6_valgrind
==3876== 
==3876== Invalid write of size 1
==3876==    at 0x488DEE0: strcpy (in /usr/libexec/valgrind/vgpreload_memcheck-arm64-linux.so)
==3876==    by 0x10887B: copy_str (ex6_valgrind.c:7)
==3876==    by 0x10889B: main (ex6_valgrind.c:12)
==3876==  Address 0x4a7e04c is 0 bytes after a block of size 12 alloc'd
==3876==    at 0x4885250: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-arm64-linux.so)
==3876==    by 0x10886B: copy_str (ex6_valgrind.c:6)
==3876==    by 0x10889B: main (ex6_valgrind.c:12)
==3876== 
==3876== Invalid read of size 1
==3876==    at 0x488DCF4: __GI_strlen (in /usr/libexec/valgrind/vgpreload_memcheck-arm64-linux.so)
==3876==    by 0x4931B13: puts (ioputs.c:35)
==3876==    by 0x1088A7: main (ex6_valgrind.c:13)
==3876==  Address 0x4a7e04c is 0 bytes after a block of size 12 alloc'd
==3876==    at 0x4885250: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-arm64-linux.so)
==3876==    by 0x10886B: copy_str (ex6_valgrind.c:6)
==3876==    by 0x10889B: main (ex6_valgrind.c:12)
==3876== 
hello world!
==3876== 
==3876== HEAP SUMMARY:
==3876==     in use at exit: 12 bytes in 1 blocks
==3876==   total heap usage: 2 allocs, 1 frees, 1,036 bytes allocated
==3876== 
==3876== LEAK SUMMARY:
==3876==    definitely lost: 12 bytes in 1 blocks
==3876==    indirectly lost: 0 bytes in 0 blocks
==3876==      possibly lost: 0 bytes in 0 blocks
==3876==    still reachable: 0 bytes in 0 blocks
==3876==         suppressed: 0 bytes in 0 blocks
==3876== Rerun with --leak-check=full to see details of leaked memory
==3876== 
==3876== For lists of detected and suppressed errors, rerun with: -s
==3876== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```

My answer

```txt
1. 1
2. strcpy
3. copy_str
4. ex6_valgrind.c
5. 7
6. 12
7. 13
8. Yes
9. 12
```

why 4. is ex6_valgrind.c instead of /usr/libexec/valgrind/vgpreload_memcheck-arm64-linux.so?

> 当问到“Which file did the call occur in?”时，我们是在寻找最初导致 错误的函数调用的位置。在这个例子中，copy_str 函数是第一个在用户代码中出现的函数，它调用了 strcpy，而 strcpy 的调用实际上发生在 ex6_valgrind.c 文件的第7行。虽然 strcpy 函数本身是在 /usr/libexec/valgrind/vgpreload_memcheck-arm64-linux.so 文件中实现的，但这个文件是Valgrind的一个预加载库，它并不是用户代码的一部分。Valgrind用它来检测内存错误。因此，当询问“Which file did the call occur in?”时，我们关注的是用户代码中最初发生调用的文件，而不是Valgrind的内部库。
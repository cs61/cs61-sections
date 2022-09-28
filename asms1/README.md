# Section Notes 2
## Outline

* [Debugging Tools](#debugging-tools)
    - [GDB](#gdb)
    - [LLDB](#lldb)
    - [Objdump](#objdump)
    - [The Address Sanitizer](#the-address-sanitizer)
* [Debugger Exercises](#debugger-exercises)
* [Assembly Review](#assembly-review)
* [Assembly Exercises](#assembly-exercises)

# Debugging Tools
This section discusses debugging tools that may aid you in future debugging. They are also important tools for exploring and solving the binary bomb problem set.

## GDB
`gdb` is a useful tool that allows the programmers to step through the execution of the program and examine the memory at each point.
There are many options and commands within `gdb` that allow one to accomplish specific tasks and fulfills different needs.
Here are some commands to get you started. You can use either the full name of the command (e.g., `run`) or the shortcut (e.g., `r`) in parentheses.

- `run` (`r`): Executes file passed as command line argument to `gdb`
- `backtrace` (`bt`): Prints the call stack
- `frame <NUMBER>`: Examines the stack frame at `<NUMBER>` given by backtrace
- `up <NUMBER>`: Moves up the call stack `<NUMBER>` frames
- `down <NUMBER>`: Moves down the call stack `<NUMBER>` frames
    -  `frame` is absolute while `up` and `down` move relative to the current frame
- `break` (`b`): Pauses execution when a particular point in the code is reached
    - `break <FILENAME>:<LINE NUMBER>`
    - `break <FUNCTION NAME>`
    - `break <FILENAME>:<FUNCTION NAME>`
- `step` (`s`): Steps into a line of code (enters function calls)
- `next` (`n`): Steps to next line of code (does '''not''' enter function calls)
- `stepi` (`si`): Steps into an instruction (enters function calls)
- `nexti` (`ni`): Steps to next instruction (does '''not''' enter function calls)
    - These may be useful in your binary bomb pset, for which you do not have source code
- `continue` (`c`): Resumes execution of the program but stops at the breakpoints; useful for passing over irrelevant code or finishing loops
- `advance <NUMBER>` (`adv`): Steps to a specific line of code (does '''not''' enter function calls); useful to break out of loops
- `finish`: Runs until the current function returns then break and print out the return value
- `examine` (`x`): Examines memory
    - Syntax: `x/<# of Elements><Type of Elements><Additional Size Info>`
    - Simple Example: `x/d 0x123`: Prints memory at address `0x123` as an integer
    - Complicated Example: `x/20xg 0x345`: Prints memory at address `0x345` as 20 hexadecimal "giant" words (8 bytes)
- `print <something>` (`p`): Prints content of a variable/memory location/register
- `display <something>` (`disp`) - Just like `print`, but gives the information on each step through the program; useful for keeping track of the value of something throughout execution.
- `set var <VARIABLE_NAME>=<VALUE>`: Sets a value in the executing program; useful for keeping track of values
    - Example: `set var addr=0x123`
- `thread <THREAD_NUMBER>` : Switches between threads in a given program (we will cover threads later in the semester)
- `q` - Quits `gdb`
- `disassemble <FUNCTION_NAME>` or `disassemble <START_ADDR>,<END_ADDR>` or `disassemble <START_ADDR>,+<LENGTH>` (`disas`):  Prints assembly instructions within a function name, or within specific addresses
- `Ctrl + X 2`: Switch into the TUI, which allows you to view assembly and source code alongside the debug console
    - `Ctrl + X 1`: Similar, but gives you only one view
    - `Ctrl + X O`: Switch the focus between views

`gdb` cheatsheet: [http://darkdust.net/files/GDB%20Cheat%20Sheet.pdf](http://darkdust.net/files/GDB%20Cheat%20Sheet.pdf)

## LLDB
`lldb` is a tool from the LLVM project similar to `gdb`. `lldb` is better supported on platforms like macOS. Its commands are similar, though not quite identical, to those of `gdb`:

- `run` (`r`): Executes file passed as command line argument to `lldb`
- `thread backtrace` (`bt`): Prints the call stack
- `frame select <NUMBER>` (`f <NUMBER>`): Examines the stack frame at `<NUMBER>` given by backtrace
- `up <NUMBER>`: Moves up the call stack `<NUMBER>` frames
- `down <NUMBER>`: Moves down the call stack `<NUMBER>` frames
    -  `frame` is absolute while `up` and `down` move relative to the current frame
- `breakpoint set` (`b`): Pauses execution when a particular point in the code is reached
    - `b <FILENAME>:<LINE NUMBER>`
    - `b <FUNCTION NAME>`
    - `b <FILENAME>:<FUNCTION NAME>`
- `step` (`s`): Steps into a line of code (enters function calls)
- `next` (`n`): Steps to next line of code (does '''not''' enter function calls)
- `stepi` (`si`): Steps into an instruction (enters function calls)
- `nexti` (`ni`): Steps to next instruction (does '''not''' enter function calls)
    - These may be useful in your binary bomb pset, for which you do not have source code
- `continue` (`c`): Resumes execution of the program but stops at the breakpoints; useful for passing over irrelevant code or finishing loops
- `finish`: Runs until the current function returns then break and print out the return value
- `memory read --size <SIZE> --format <FORMAT> --count <COUNT> <ADDRESS>` (`x`): Examines memory
    - Alternate Syntax: `x/<# of Elements><Type of Elements><Additional Size Info>`
    - Simple Example: `x/d 0x123`: Prints memory at address `0x123` as an integer
    - Complicated Example: `x/20xg 0x345`: Prints memory at address `0x345` as 20 hexadecimal "giant" words (8 bytes)
- `frame variable <VARIABLE NAME>` (`p`): print local variable
- `target variable <VARIABLE NAME>` (`ta`): print global variable
- `display <something>` (`disp`) - Just like `print`, but gives the information on each step through the program; useful for keeping track of the value of something throughout execution.
- `thread select <THREAD_NUMBER>` (`t`): Switches between threads in a given program (we will cover threads later in the semester)
- `q` - Quits `lldb`
- `disassemble --frame` (`di -f`): Disassemble the current frame

`lldb` cheatsheet: [https://lldb.llvm.org/lldb-gdb.html](https://lldb.llvm.org/lldb-gdb.html)

## Objdump
`objdump` displays information about object file (usually files with extension `.o`). If used as a disassembler, it works like `disas` in `gdb`.

Usage: `objdump -d <PROGRAM_NAME>` (the flag `-d` means disassemble)

## The Address Sanitizer
The address sanitizer is a feature of GCC and Clang that instruments your code at compile time to detect memory-associated undefined behavior. To do so, it inserts checks such as bounds checking for arrays, double free detection for allocations, alignment checks for pointer access, use after free detection, uninitialized memory accesses, and memory leaks. Should your program invoke any such undefined behavior, the address sanitizer will report this and potentially abort the program. You may have encountered this while completing the debugging allocator problem set. The address sanitizer can be very useful when you're debugging memory corruption or segmentation violations.

If you are using the address sanitizer with a debugger, you may have to follow the directions at [https://github.com/google/sanitizers/wiki/AddressSanitizerAndDebugger](https://github.com/google/sanitizers/wiki/AddressSanitizerAndDebugger) to properly catch the error.

# Debugger Exercises

So today we are going to have some fun! If you look at your folder you will find a lot of fun files which you can compile into binaries (woohoo). These binaries expect you to pass in some arguments. Now you may wonder how you can know that you passed in the right arguments. Then what are you waiting for? Go on and feed a few arguments to see what happens.

Compile the binaries with `make`. To run a fun binary *i* on some input, execute:
```
./fun[i] <your input>
```
Good luck and have **fuuunn**!!!

# Assembly Review
## Assembly and Calling Conventions
Please refer to the [lecture notes](https://cs61.seas.harvard.edu/site/2018/Asm1/) for information on calling conventions.


A few notes:

* The non-numeric registers follow a naming pattern (%r\_ for 64-bit, %e\_ for 32-bit, %\_l for 8-bit low, %\_h for 8-bit high)
* The numeric registers follow a similar pattern ($r\_ for 64-bit, %\_d for 32-bit, %\_w for 16-bit, %\_b for 8-bit low)
* Parameters are passed in the order `%rdi`, `%rsi`, `%rdx`, `%rcx`, `%r8`, `%r9`
* For functions with more than six parameters, subsequent parameters will be pushed onto the stack.



### A Quick Example
Consider the following C++ program.

```cpp
int my_operation(int a, int b, int c) {
  if (a < 0)
    return b;
  else
    return b + c;
}

int main(int argc, char **argv) {
  int op = my_operation(4, 5, 6);
  return 0;
}
```

1. What registers are the parameters to `my_operation` stored in?
2. What register will `main` find the return value of `my_operation` in?
3. What registers could have changed when control returns to `main` from `my_operation`?

### Addressing
| Type      | Example               | Value                                         |
| --------- | --------------------- | --------------------------------------------- |
| Immediate | `$0x100`              | `0x100`                                       |
| Register  | `%rcx`                | Contents of `%rcx`                            |
| Memory    | `0x04`                | The value at `0x04`                           |
|           | `(%rax)`              | The value located at `%rax`                   |
|           | `0x04(%rax)`          | The value located at `%rax + 0x04`            |
|           | `(%rax, %rbx)`        | The value located at `%rax + %rbx`            |
|           | `(%rax, %rbx, 4)`     | The value located at `%rax + %rbx * 4`        |
|           | `0x18(%rax, %rbx, 4)` | The value located at `%rax + 0x18 + %rbx * 4` |

In full form `0x18(%rax, %rbx, 4)`, `%rax` is the base, `0x18` is the offset, `%rbx` is the index, and `4` is the scale.

Consider the following declarations and definitions:

```c
struct my_struct_type {
  int number;
  char label;
  long size;
};

int my_array[8];
struct my_struct_type my_struct;
```

Using the addressing modes described above, answer the following questions:

1. Suppose that the address of `my_array` is stored in `%rcx`. How can we access the 3rd element of `my_array`?
2. Suppose that the address of `my_array` is stored in `%rcx`, and an index is stored in `%rdx`. How can we access the `%rdx`th element of `my_array`?
3. Suppose that the address of `my_struct` is stored in `%rcx`. How can we access `my_struct.label`?
4. When would the full form be useful?

#### Load Effective Address
Consider the following piece of code:
```asm
leaq    0x8(%rax, %rbx, 4), %rdx
movq    0x8(%rax, %rbx, 4), %rcx
```
In both cases, `0x18(%rax, %rbx, 4)` evaluates to `%rax + %rbx * 4 + 0x18`. However, `movq` moves the value at address `%rax + %rbx * 4 + 0x18` into `%rcx` while `leaq` does not perform any dereferences and simply puts `%rax + %rbx * 4 + 0x18` into `%rdx`.

An equivalent code in C++ could have been something like:
```cpp
struct {
    long val;
    int arr[4];
} a;                    // address to `a` to stored in %rax
int i = 2;              // `i` is stored in %rbx
int *p = &a.arr[i];     // leaq
int n = a.arr[i];       // movq
```
`leaq` is commonly used to generate pointers for later memory references but can also be used to do arithmetic.

### Conditions and Jumps

#### Condition Flags
Because the instructions are executed one-by-one, in order to implement non-linear behavior (conditionals or loops), assembly has condition codes and jump instructions. There many condition codes (you can read more about them [here](https://en.wikipedia.org/wiki/FLAGS_register)), but for the sake of simplicity, there are four that we care about: `CF` (carry flag), `ZF` (zero flag), `SF` (sign flag), `OF` (overflow flag). These flags are set after each instruction, with a exception of `leaq` (Bryant et al. 201).

To understand them better, let's look at an example:
```cpp
// a, b, t are ints
t = a + b;
```
After this instruction, we can evaluate the condition flags in the following manner (Bryant et al. 201):
* `CF: (unsigned)t < (unsigned)a`
* `ZF: t == 0`
* `SF: t < 0`
* `OF: (a < 0 == b < 0) && (t < 0 != a < 0)`

For those who are interested in why overflow flag is set the way described above, feel free to look into bonus material.

#### Comparison and Test Instructions
Integer arithmetic instructions like `add` and `sub`, `and` and `or`, `sal` and `sar`, etc. set the condition flags and modify the value the second argument. In addition to those, there are two classes of instructions that set the condition flags without modifying any of the arguments. The first one is `cmp` which calculates the difference between the second argument and the first one. The second one is `test` which calculates the bitwise and of two arguments.

#### Jump Instructions
To see how comparison and test instructions are helpful, we introduce jump instructions. In short, jump instructions modify the instruction pointer (stored in `%rip`) to point to another location in the program. Jumps can be *unconditional* (`%rip` changes regardless of the flag values) or *conditional* (`%rip` changes depending on the flag values).

Unconditional jumps can be *direct*, meaning that the jump targets are evaluated by the assembler during object file generation, or *indirect*, meaning that the jump targets are read from a register or a memory location during runtime.
```asm
jmp   .L1     ; direct jump to a label generated by the assembler
jmp   *%rax   ; indirect jump to a location stored in %rax
jmp   *(%rax) ; indirect jump to a location stored in memory at address %rax
```
Conditional jumps are often used in conjunction with `cmp` or `test`. Let's look at the following code to understand how these instructions are used together:
```cpp
int less(int a, int b) {
    if (a < b) {
        return a;
    } else {
        return b;
    }
}
```
The equivalent assembly code is:
```asm
less(int, int):
        pushq   %rbp
        movq    %rsp, %rbp
        movl    %edi, -4(%rbp)
        movl    %esi, -8(%rbp)
        movl    -4(%rbp), %eax
        cmpl    -8(%rbp), %eax
        jge     .L2
        movl    -4(%rbp), %eax
        jmp     .L3
.L2:
        movl    -8(%rbp), %eax
.L3:
        popq    %rbp
        ret
```
The two lines of interest are:
```asm
        cmpl    -8(%rbp), %eax
        jge     .L2
```
When we hit these instructions, `%eax` contains `a`, and `-8(%rbp)` contains `b`. The `cmp` instruction evaluates `%eax - -8(%rbp)` which is the same as `a - b`. The next jump instruction succeeds only if the value obtained on the last step, namely `a - b`, is greater than or equal (hence `jge`) zero. Therefore if `a - b >= 0` which is the same as `a >= b`, we jump to `.L2` which moves `b` into `%eax` and returns, otherwise we (redundantly) move `a` into `%eax` and jump to `.L3` which then returns.

As for the `test` instruction, it is often used to check if the value is zero, positive, or negative (how `test` is used is left as an exercise to the reader).

There are other conditional jump instructions (Bryant et al. 206) whose jump conditions can easily be inferred from their names.

### Function Calls and Return Addresses
Besides conditionals and loops which use jump instructions to modify the instruction register, function calls and returns from functions also modify `%rip`. The instruction `call` which takes an address of another function stores the address of the instruction after (!) the function call on the stack and then jumps to the first instruction of the function called. On the other hand, the instruction `ret` takes no argument and restores `%rip` to the return address that was stored by `call`, returning control to the function above. To make this clearer, try debugging the following code with `gdb`:
```c
int sum(int a, int b) {
    return a + b;
}

int main() {
    int s = sum(1, 2);
    return 0;
}
```
Start `gdb` on the executable, set a breakpoint on `main`, and run the program. If you did everything correctly, you should be right at the beginning of `main`. Run `disas` and you should see something similar to this:
```
(gdb) disas
Dump of assembler code for function main:
   0x000000000040050a <+0>:     push   %rbp
   0x000000000040050b <+1>:     mov    %rsp,%rbp
   0x000000000040050e <+4>:     sub    $0x10,%rsp
=> 0x0000000000400512 <+8>:     mov    $0x2,%esi
   0x0000000000400517 <+13>:    mov    $0x1,%edi
   0x000000000040051c <+18>:    callq  0x4004f6 <sum>
   0x0000000000400521 <+23>:    mov    %eax,-0x4(%rbp)
   0x0000000000400524 <+26>:    mov    $0x0,%eax
   0x0000000000400529 <+31>:    leaveq
   0x000000000040052a <+32>:    retq
End of assembler dump.
```
Remember the address of the instruction after `call`, in this case `0x0000000000400521`. Hit `si` multiple times until you jump to the start of `sum`. If you run `x/1xg $rsp`, you should get something similar to this:
```
(gdb) x/1xg $rsp
0x7fffffffeb48: 0x0000000000400521
```
But that's the same number as the one we remember from before. That is the return address that gets restored by `ret` after this function finishes, returning control back to `main`. Run `disas` to see the assembly code for `sum` (just for fun):
```
(gdb) disas
Dump of assembler code for function sum:
=> 0x00000000004004f6 <+0>:     push   %rbp
   0x00000000004004f7 <+1>:     mov    %rsp,%rbp
   0x00000000004004fa <+4>:     mov    %edi,-0x4(%rbp)
   0x00000000004004fd <+7>:     mov    %esi,-0x8(%rbp)
   0x0000000000400500 <+10>:    mov    -0x4(%rbp),%edx
   0x0000000000400503 <+13>:    mov    -0x8(%rbp),%eax
   0x0000000000400506 <+16>:    add    %edx,%eax
   0x0000000000400508 <+18>:    pop    %rbp
   0x0000000000400509 <+19>:    retq
End of assembler dump.
```
Hit `si` until you reach `retq` instruction (keep track of the number of the left each time you run `si`--that is the address of the instruction that is about to be executed). Now right before you execute `retq`, run `x/1xg $rsp` again and you should see that the stack pointer has returned to where it started and is pointing to the return address.

There are two more instructions that are related to function calls: `push` and `pop`. Assuming that registers are 8 byte, you can think of them as the shortcuts for the following:
* `pushq %reg` is equivalent to `subq $8, %rsp ; movq %reg, (%rsp)` (increase the stack and put the value in `%reg` onto its top)
* `popq %reg` is equivalent to `movq (%rsp), %reg ; addq $8, %rsp` (put the value on the top of the stack into `%reg` and decrease it)

There is a helpful illustration of stack modifications during each step of function entry and exit in the book (Bryant et al. 242) that can supplement the material in this section on function calls and return addresses.



# Assembly Exercises

Consider the following assembly functions. Try to describe what they are doing and write an equivalent program in C.

#### Assembly Sample 1:
```asm
my_func1:
  addl %edi,%esi
  movq %rsi,%rax
  retq
```

#### Assembly Sample 2:
```asm
my_func2:
  pushq	%rbp
  movq	%rsp, %rbp
  movb	(%rsi), %al
  testb	%al, %al
  je	LBB0_3
  xorl	%ecx, %ecx
LBB0_2:
  movb	%al, (%rdi,%rcx)
  movzbl	1(%rsi,%rcx), %eax
  incq	%rcx
  testb	%al, %al
  jne	LBB0_2
LBB0_3:
  popq	%rbp
  retq
```

#### Assembly Sample 3:
```asm
my_func3:
  pushq	%rbp
  movq	%rsp, %rbp
  pushq	%r14
  pushq	%rbx
  movl	%edi, %ebx
  testl	%ebx, %ebx
  je	LBB0_3
  cmpl	$1, %ebx
  jne	LBB0_5
  movl	$1, %ebx
LBB0_3:
  movl	%ebx, %eax
  popq	%rbx
  popq	%r14
  popq	%rbp
  retq
LBB0_5:
  leal	-1(%rbx), %edi
  callq	my_func3
  movl	%eax, %r14d
  addl	$-2, %ebx
  movl	%ebx, %edi
  callq	my_func3
  addl	%r14d, %eax
  popq	%rbx
  popq	%r14
  popq	%rbp
  retq
```


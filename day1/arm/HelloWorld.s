//
// Assembler program to print "Hello World!"
// to stdout.
//
// X0-X2 - parameters to linux function services
// X16 - linux function number
//
.global _start             // Provide program starting address to linker
.align 2


_loop:  
        cmp X4, #0
        mov X0, #1     // 1 = StdOut
        adr X1, helloworld // string to print
        mov X2, #13     // length of our string
        mov X16, #4     // MacOS write system call
        svc 0     // Call linux to output the string
        sub X4, X4, #1
        b.ne _loop
        ret

         
// Setup the parameters to print hello world
// and then call Linux to do it.

_start: 
        mov X4, #2
        bl _loop


// Setup the parameters to exit the program
// and then call Linux to do it.

        mov     X0, #0      // Use 0 return code
        mov     X16, #1     // Service command code 1 terminates this program
        svc     0           // Call MacOS to terminate the program

helloworld:      .ascii  "Hello World!\n"

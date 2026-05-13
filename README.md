# OS_Project1
Project 1 for the OS course
THe goal of this project was to create a C program that reverses a text input by line order. The program can be run three different ways. 

The first is ./reverse, in which the input comes from the terminal and the output is printed to the terminal.

The second is ./reverse \<input\>, in which the input comes from a text file specified and the output is printed to the terminal.

The third is ./reverse input \<output\>, in which the input comes from a text file and the output is printed to a text file.

Some additional assumptions on how the program is supposed to work:

If the input and output files are both specified and they are the same, prints out error: "Input and output file must differ".
Assumptions about string and file length are not made, meaning they can be very long.
If the given files are invalid, outputs error: "error: cannot open file 'input.txt'".
Malloc failures are captured.
Program takes in at most 2 parameters, otherwise prints "usage: reverse <input> <output>".
Program uses fprintf and outputs errors to stderr.


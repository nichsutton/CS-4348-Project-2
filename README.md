# Team 2
## Members: Daniel Dimitrov, Nicholas Sutton

### File Listings:
* main.cpp - This is the main program file. It includes all code used to implement the single threaded and multi-threaded sorting, as well as timing.
* README.md - This file includes all information regarding the project - including key commands, compilation and running instructions, and results.
* Results_Table.pdf - This file includes a table of the benchmark results, using different sizes for the array, both single and multi-threaded.

### Compiling the program:
To compile this program make sure you are in the project directory. Then type one of the two following commands:\
`g++ -std=c++11 main.cpp -o sort`\
or\
`gcc -o sort main.cpp -lstdc++`

### Running the program:
To run this program, simply type the following into the same directory as where you compiled the program. (this should be in the same directory as before)
`./sort`

### Results:
| N             | Using Non-Threading | Using Multithreading |
| ------------- |--------------------:| --------------------:|
| 1000          | 0.092 msec          | 0.107 msec           |
| 5000          | 0.549 msec          | 0.374 msec           |
| 10000         | 1.122 msec          | 0.698 msec           |
| 20000         | 4.951 msec          | 1.594 msec           |

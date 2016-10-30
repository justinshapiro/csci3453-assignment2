Lab 2
=====
Code by Justin Shapiro
CSCI 3453 (Operating System Concepts)
Fall 2016

#### Problem Statement ####

Use C or C++ to design a simulation of FCFS (First-Come, First-Served), SRTF (Shortest Remaining Time First), and RR (Round Robin) CPU scheduling algorithms. When a process is preempted, simulate a context switch by adding 0.5 ms to clock. In the RR case, a FCFS policy is used to break the tie. After parsing process data from an input file, ready and write process data directly from the ready queue, which is to be implemented without an STL container. 

The program will be run by means of three arguments: 

 1. Name of data file
 2. Mode (FCFS = 0, SRTF = 1, RR = 2)
 3. Time-Quantum (required only if Mode = 2)

The run of each algorithm will produce a table that is similar to a Gantt-Chart, but more detailed. This table will have the PID, Arrival Time, CPU Burst Time, Finish Time, Waiting Time, Turnaround Time, Response Time, and the number of context switches for each process. Additionally, the averages of all of the process' CPU Burst Times, Waiting Times, Turnaround Times, and Response times is computed along with the total number of context switches that occurred during the run.

#### Implementation & Accuracy ####
Each process is parsed from the input data file (*arg1*) and placed in an array that is used to construct a **`FakeProcess`** object. The **`FakeProcess`** object is an ADT that defines a PCB (Process Control Block) for each process. An array called `PROCESS_LIST` containing each **`FakeProcess`** (in the order that they have been placed in the file) is passed to the `schedule()` function that performs the CPU scheduling simulation using the requested algorithm and time-quantum (if applicable). 

`schedule()` uses while loop that terminates upon all processes having the status of `finished`. At the end of each loop iteration a counter named `time` is used to act as the system clock. The current `time` is compared to the `ARRIVAL_TIME` attribute of each **`FakeProcess`**. If the current time is equal to or no more distant than `time - (context_switch_count * 0.5)` from the next process in `PROCESS_LIST` that has not been added to a **`ReadyQueue`**, the process will be added to the queue.

**`ReadyQueue`** is an ADT that represents a FIFO queue of **`FakeProcess`'**.  **`ReadyQueue`** uses a standard dynamic array to simulate such a data structure, and contains functions such as `push()`, `pop()`, `remove(index)` and `sort()` to manage the queue.

 Within the while loop, conditional branching is used in following manner for each respective algorithm:

 - *FCFS*: The loop iterates, calling `progress()` at each iteration to decrement the `CPU_BURST` attribute of the current **`FakeProcess`** (that is, the process at index=0, the head of the **`ReadyQueue`**). When the current **`FakeProcess`** has `CPU_BURST == 0`, its information will be saved back into `PROCESS_LIST` and the taken off of the queue using `pop()`.
 - *SRTF*: This loop uses the same exact process as FCFS, with the exception that the `sort()` function is called on the **`ReadyQueue`** whenever a `push()` or a `pop()` has occurred. The `sort()` performs a bubble sort on the **`ReadyQueue`**, ordering its **`FakeProcess`'** from lowest to highest `CPU_BURST` values. Whichever **`FakeProcess`** ends up at the head of the **`ReadyQueue`** is the currently active process.
 - *RR*: At the insertion of each new element into the **`ReadyQueue`**, elements were swapped accordingly in order to abide by the Round Robin principle and to also use the FCFS policy to break any ties. Each currently active **`FakeProcess`** is active for a number of loop iterations equal to `quantum` (*arg3*). The rest of the algorithm uses the same constructs as FCFS.

The above implementations of the algorithms do indeed produce correct results. These algorithms were tested with the provided input10 and input100 files. Additionally, I tested program with input4 from the assignment description and input5 from the CPU scheduling in-class practice. Each algorithm produces the correct results for each input file.

#### Compile/Run Instructions ####
After unzipping the .tar folder, navigate to the directory and issue the `make` command. The `make` command simply compiles the program using `g++ -std:c++11 -w *.cpp -o myscheduler`. Please do not forget to run `g++` with the `-std:c++11` argument. The program requires a C++11 compiler in order to use the `stoi()` function. The easiest way to compile this is to simply use the makefile provided in the .tar archive.

Please note that program consists of the following files, each .cpp file needing to be compiled and linked:

 - myscheduler.cpp
 - FakeProcess.h
 - FakeProcess.cpp
 - ReadyQueue.h
 - ReadyQueue.cpp

After compiling, the program can be run by using the following syntax:

    ./myscheduler arg1 arg2 arg3
For example, to run a datafile of 10 processes in a RR fashion with time-quantum equal to 4, we would write:

    ./myscheduler input10 2 4

The input4, input5, input10, and input100 data files that I used to test the program with are also included in the .tar directory.



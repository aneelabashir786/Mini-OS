
 Mini Operating System (OS Lab Project)

A Linux-based Mini Operating System simulation developed as part of the Operating Systems Lab Final Project. This project demonstrates core OS concepts such as process management, memory allocation, scheduling, synchronization, and inter-process communication using C, pthreads, semaphores, and shell scripting.

 Project Overview

This Mini OS simulates the working of an operating system by providing a menu-driven interface that allows users to execute multiple applications while managing RAM usage, process queues, and system resources.

The system supports concurrent execution of processes, ensures synchronization using semaphores, and handles memory constraints using a ready queue mechanism.

 Key Features

 1. Boot Loader & Authentication

Secure login mechanism

Resource initialization (CPU cores, HDD, RAM)

2. Process Management

Process creation using fork()

Multi-threading using pthread

Process synchronization using semaphores

Graceful termination of all processes

3. Memory Management

Dynamic RAM allocation and restoration

Memory requirement checks before process execution

Ready Queue for memory-constrained processes

4. Scheduling & Ready Queue

Circular queue implementation

Automatic execution when memory becomes available

 Applications Included

1. Calculator (GUI & CLI)
2. Clock
3. Media Player
4. Browser
5. File Explorer
       Create, copy, move, delete files & folders
6. File Permission Manager
7. Text Editor (Create/Open files)
8.  Calendar
9.  Task Manager
10.  Games
    Tic Tac Toe
    Guess the Number
11. Refresh System (Restores RAM)


Technologies Used

Language: C / C++

OS Concepts:
Process Scheduling, Memory Management, IPC, Semaphores

Libraries:
pthread, semaphore, unistd, signal, sys/wait

Platform: Linux

Tools: GCC, Bash, GNOME Terminal

 How to Run
Prerequisites

Linux OS

GCC compiler

GNOME Terminal

Required shell scripts must be executable

Compilation
        
        gcc main.c -o os -lpthread

Execution
      
      ./os <number_of_cores> <storage_size_GB> <RAM_size_GB>


Example:

      ./os 4 500 8

 Login Credentials
           
           Password: 1122

 Project Structure

Mini-OS/
│── main.c
│── calculator/
│── clock.sh
│── browser.sh
│── taskM.sh
│── fileExplorer/
│── games/
│── texteditor/
│── scripts/
└── README.md

Learning Outcomes:

Hands-on understanding of OS internals

Practical experience with concurrency & synchronization

Process scheduling and memory handling

Linux system programming

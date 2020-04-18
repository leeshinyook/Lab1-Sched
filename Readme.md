# CPU Scheduling Algorithms

<img src="https://img.shields.io/github/issues/leeshinyook/Lab1-Sched"> <img src="https://img.shields.io/github/forks/leeshinyook/Lab1-Sched"> <img src="https://img.shields.io/github/stars/leeshinyook/Lab1-Sched"> <img src="https://img.shields.io/github/last-commit/leeshinyook/Lab1-Sched"> <img src="https://img.shields.io/github/repo-size/leeshinyook/Lab1-Sched"> [![HitCount](http://hits.dwyl.com/leeshinyook/Lab1-Sched.svg)](http://hits.dwyl.com/leeshinyook/Lab1-Sched)



## Team

|        [leeshinyook](https://github.com/leeshinyook)         |          [hs-krispy](https://github.com/hs-krispy)           |
| :----------------------------------------------------------: | :----------------------------------------------------------: |
| <img src="https://avatars3.githubusercontent.com/u/55838461?s=400&u=06a56002fd08e659a979557ea8d8a79efe9ba1ec&v=4" width="50%" align="center"> | <img align="center" src="https://avatars0.githubusercontent.com/u/58063806?s=400&v=4" width="50%"> |

We are students of Dankook University's software department. We are working on a project for the Cpu 

scheduling algorithm.

**Pull requests are always welcome.**

## Code Structure

1. `include/lab_sched_types.h` 

   This has structure of the process which has processName, arrivalTime etc. Create struct object in this file. 

~~~c++
// lab_sched_types.h, Setinit2()
void SetInit2() {
    v2[0].arriveTime = 0, v2[0].serviceTime = 4, v2[0].processName = 'A'
    v2[1].arriveTime = 1, v2[1].serviceTime = 2, v2[1].processName = 'B'
    v2[2].arriveTime = 5, v2[2].serviceTime = 6, v2[2].processName = 'C'
    v2[3].arriveTime = 7, v2[3].serviceTime = 5, v2[3].processName = 'D'
    v2[4].arriveTime = 10, v2[4].serviceTime = 3, v2[4].processName = 'E'
    InitVariable();
}
~~~

If you need Stride algorithm, Add `v2[0].ticket`. We have set the total number of stride repetitions to 100.

If you want to increase the number of iterations, increase the TC variable in the Stride function.

Also, We set the time quantum of RR and MLFQ to 1 and 2 or 1 and 4. 

To adjust this time quantum, adjust each scheduling factor in the Run function section.(`lab1_sched.cpp`)

1. `lab1_sched.cpp`

   This has structure of functions(algorithm func, common func etc).

2. `lab1_sched_test.cpp`

   This file has only one function. `void run()`. This function can make the whole function work.



## How to run

We have set up a makefile for convenient code execution.

Since it is a file written in c++ lang, so `g++` installation is required!

Also, `make` installation is required, so please install it first.

### 1. Clone Project

~~~
$ git clone https://github.com/leeshinyook/Lab1-Sched.git
~~~

### 2. Make 

~~~
$ make
~~~

The make command creates an executable file.
An executable file should have been created in your current directory.

If you want to delete the generated files, type  `make clean`

### 3. Run Executable file

~~~
$ ./lab1_sched
~~~


































































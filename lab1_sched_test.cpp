//
// Created by 이신육 on 12/04/2020.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <math.h>
#include "lab1_sched_types.h"
using namespace std;
int main() {
    cout<<"First workloads\n\n";
    SetInit1();
    FIFO(v1);
    RR(v1, 1);
    RR(v1, 4);
    MLFQ(v1, 1);
    MLFQ(v1, 2);
    Stride(v1);
    cout<<"Second workloads\n\n";
    SetInit2();
    FIFO(v2);
    RR(v2, 1);
    RR(v2, 4);
    MLFQ(v2, 1);
    MLFQ(v2, 2);
    Stride(v2);
}
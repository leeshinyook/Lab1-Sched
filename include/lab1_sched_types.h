//
// Created by 이신육 on 12/04/2020.
//

#ifndef LAB1_LAB1_SCHED_TYPES_H
#define LAB1_LAB1_SCHED_TYPES_H
#include <vector>
using namespace std;
struct process {
    char processName; // 프로세스 이름, priority
    int serviceTime; // 동작시간
    int arriveTime; // 도착시간
    int waitTime; // 대기시간
    int turnaroundTime; // 반환시간
    /*for stride----*/
    int stride;
    int ticket;
    int passValue; // initialize
    /*--------------*/
};
/* perform 5 processes */
queue<pair<char, int> > result;
vector<process> v1(5);
vector<process> v2(5);
/* end of 5 processes */
void InitVariable();
void SetInit1();
void SetInit2();
int GCD(int a, int b);
int LCM(int a, int b);
void Print(vector<process> p);
void calcWait(vector<process> p);
void calcTurnaround(vector<process> p);
void getPerformance(vector<process> p);
void Stride(vector<process> p);
void FIFO(vector<process> p);
void MLFQ(vector<process> p, int exPow);
void RR(vector<process> p, int ts);


#endif //LAB1_LAB1_SCHED_TYPES_H

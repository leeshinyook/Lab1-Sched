#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;
<<<<<<< HEAD
typedef struct process {
    char processName; // 프로세스 이름, priority
    int serviceTime; // 동작시간
    int arriveTime; // 도착시간
    int waitTime; // 대기시간
} process;
void SortByArriveTime(process *p, int n) { // 도착시간이 빠른 것 부터, 정렬
    process temp;
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < i; j++) {
            if(p[j].arriveTime > p[j + 1].arriveTime) {
                Swap(p[j], p[j + 1]);
            } else if(p[j].arriveTime == p[j + 1].arriveTime && p[j].processNumber > p[j + 1].processNumber) { // 번호가 빠른 것 부터
                Swap(p[j], p[j + 1]);
            }
        }
    }
}
void FIFO(process *ps, int count)
{
    int Turnaround[n] = {p[0].serviceTime, };
    int Wait[n] = {0, };
    printf("Process name : %c, Turnaround time : %d, Wait time : %d\n", p[0].processName, Turnaround[0], Wait[0])
    for(int i=1;i<n;i++)
    {
        Turnaround[i] = Turnaround[i-1] + p[i].serviceTime;
        Wait[i] = Turnaround[i-1] - p[i].arriveTime;
        printf("Process name : %c, Turnaround time : %d, Wait time : %d\n", p[i].processName, Turnaround[i], Wait[i])
    }
}
int main() {
    int count;
    cin >> count; // 프로세스 개수
    process ps[count];
    for(int i = 0; i < count; i++)//프로세스 정보 입력
        scanf("Process name : %c, Arrive time : %d, Service time : %d", &ps[i].processName, &ps[i].arriveTime, &ps[i].serviceTime);
    SortByArriveTime(ps, count);
=======

/* define process struct */
struct process {
    char processName; // 프로세스 번호, priority
    int serviceTime; // 동작시간
    int arriveTime; // 도착시간
    int waitTime; // 대기시간
    int turnaroundTime; // 반환시간
    /*for stride----*/
    int stride;
    int ticket;
    int passValue = 0; // initialize
    /*--------------*/
};
/* end of process struct */

/* perform 5 processes */
queue<pair<char, int>> result;
vector<process> v(5);
/* end of 5 processes */

/* for calculate and print performance */
float avgTurnaround = 0;
float avgWait = 0;
vector<int> turnaround(5, 0); // 5 processes
vector<int> pWait(5, -1); // 5 processes
/* end of calculate and print */



void SetInit() {
    v[0].arriveTime = 0, v[0].serviceTime = 3;
    v[1].arriveTime = 2, v[1].serviceTime = 6;
    v[2].arriveTime = 4, v[2].serviceTime = 4;
    v[3].arriveTime = 6, v[3].serviceTime = 5;
    v[4].arriveTime = 8, v[4].serviceTime = 2;
}
// scheduling table ■ □
void Print() {
    char task[5] = {'A', 'B', 'C', 'D', 'E'};
    int time = 0;
    int size = result.size();
    vector<pair<char, int>> arr(size);
    for(int i = 0; i < size; i++) {
        arr[i].first = result.front().first;
        arr[i].second = result.front().second;
        time += result.front().second;
        result.pop();
    }
    for(int i = 0; i < 5; i++) {
        time = 0;
        cout << task[i] << " ";
        for(int j = 0; j < arr.size(); j++) {
            if(task[i] == arr[j].first) {
                for(int k = 0; k < arr[j].second; k++) {
                    cout << "■ ";
                }
            } else {
                time += arr[j].second;
                for(int k = 0; k < time; k++) {
                    cout << "□ ";
                }
                time = 0;
            }
        }
        cout << '\n';
    }
}
void calcWait(vector<process> p, int ts) 
{
    queue<pair<char, int>> copy;
    copy = result;
    int time = 0;
    while(!copy.empty())
    {
        for(int i = 0; i < p.size(); i++)
        {
            if(pWait[i] == -1 && copy.front().first == p[i].processName)
            {
                p[i].waitTime = pWait[i] = time - p[i].arriveTime;
                avgWait += p[i].waitTime;
            }
        }
        time += copy.front().second;
        copy.pop();
    }
    avgWait /= p.size();
} 
void calcTurnaround(vector<process> p, int ts)
{
    queue<pair<char, int>> copy;
    copy = result;
    int time = 0;
    while(!copy.empty())
    {
        time += copy.front().second;
        for(int i = 0; i < p.size(); i++)
        {
            if(copy.front().first == p[i].processName)
            {
                p[i].turnaroundTime = turnaround[i] = time;
                avgTurnaround += p[i].turnaroundTime;
            }
        }
        copy.pop();
    }
    avgTurnaround /= p.size();
}
void getPerformance(vector<process> p)
{
    calcWait(p, 4);
    calcTurnaround(p, 4);
    for(int i = 0; i < p.size(); i++)
    {
        cout<<"process : "<<p[i].processName<<"\tturnaroundTime : "<<turnaround[i]<<"\twaitTime : "<<pWait[i]<<"\n";
    }
    cout<<"Average turnaroundTime : "<<avgTurnaround<<" Average waitTime : "<<avgWait<<"\n";
} // print Performance
int main() {
    SetInit();
    return 0;
>>>>>>> feature/common
}
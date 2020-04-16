#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <string>
#include <string.h>
using namespace std;

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
    v[0].arriveTime = 0, v[0].serviceTime = 3, v[0].processName = 'A', v[0].ticket = 100;
    v[1].arriveTime = 2, v[1].serviceTime = 6, v[1].processName = 'B', v[1].ticket = 50;
    v[2].arriveTime = 4, v[2].serviceTime = 4, v[2].processName = 'C', v[2].ticket = 250;
    v[3].arriveTime = 6, v[3].serviceTime = 5, v[3].processName = 'D', v[3].ticket = 400;
    v[4].arriveTime = 8, v[4].serviceTime = 2, v[4].processName = 'E', v[4].ticket = 200;
}

/* Euclidean algorithm for calculate stride */
int GCD(int a, int b) // Greatest common divisor
{
    int c;
    while(b > 0)
    {
        c = a % b;
        a = b;
        b = c;
    }
    return a;
}

int LCM(int a, int b) // Least common multiple
{
    return a * b / GCD(a, b);
}
/* end of Euclidean algorithm for calculate stride */

// scheduling table ■ □
void Print() {
    int time;
    int size = result.size();
    vector<pair<char, int>> arr(size);
    for(int i = 0; i < size; i++) {
        arr[i].first = result.front().first;
        arr[i].second = result.front().second;
        result.pop();
    }
    for(int i = 0; i < 5; i++) {
        time = 0;
        cout << v[i].processName << " ";
        for(int j = 0; j < arr.size(); j++) {
            if(v[i].processName == arr[j].first) {
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
void calcWait(vector<process> p) 
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
void calcTurnaround(vector<process> p)
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
                p[i].turnaroundTime = turnaround[i] = time - p[i].arriveTime;
        }
        copy.pop();
    }
    for(int i = 0; i < p.size(); i++)
        avgTurnaround += p[i].turnaroundTime;
    avgTurnaround /= p.size();
}
void getPerformance(vector<process> p)
{
    calcWait(p);
    calcTurnaround(p);
    for(int i = 0; i < p.size(); i++)
    {
        cout<<"process : "<<p[i].processName<<"\tturnaroundTime : "<<turnaround[i]<<"\twaitTime : "<<pWait[i]<<"\n";
    }
    cout<<"Average turnaroundTime : "<<avgTurnaround<<" Average waitTime : "<<avgWait<<"\n";
} // print Performance

void Stride(vector<process> p) {
    int TC = 100; // 반복 횟수
    int commonMulti = 0; // 최소공배수가 들어갈 변수
    int minIdx = 0;
    int temp = 0;
    for(int i = 2; i < p.size(); i++) { // 각 ticket값들의 최소공배수를 구함
        if(i == 2)
            temp = LCM(p[0].ticket, p[1].ticket);
        commonMulti = LCM(p[i].ticket, temp);
        temp = commonMulti;
        p[i].passValue = 0;
    }
    for(int i = 0; i < p.size(); i++) { // stride값 설정
        p[i].stride = commonMulti / p[i].ticket;
    }
    for(int i = 0; i < TC; i++) {
        int min = INT_MAX;
        for(int j = 0; j < p.size(); j++) {
            if(min > p[j].passValue) { // passValue가 가장 작은 프로세스부터 실행
                min = p[j].passValue;
                minIdx = j;
            }
        }
        result.push({p[minIdx].processName, 1});
        p[minIdx].passValue += p[minIdx].stride; // stride만큼 passValue 증가
    }
}

int main() {
    SetInit();
    Stride(v);
    Print();
    return 0;
}
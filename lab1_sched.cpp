#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <string>
#include <string.h>
#include <stdio.h>
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

/* Initvari(calculate and print) func */
void InitVariable() {
    avgTurnaround = 0;
    avgWait = 0;
    while(!result.empty()) result.pop();
    for(int i = 0; i < 5; i++) {
        turnaround[i] = 0;
        pWait[i] = -1;
    }
}
/* End of Initvari(calculate and print) func*/

void SetInit() {
    v[0].arriveTime = 0, v[0].serviceTime = 3, v[0].processName = 'A';
    v[1].arriveTime = 2, v[1].serviceTime = 6, v[1].processName = 'B';
    v[2].arriveTime = 4, v[2].serviceTime = 4, v[2].processName = 'C';
    v[3].arriveTime = 6, v[3].serviceTime = 5, v[3].processName = 'D';
    v[4].arriveTime = 8, v[4].serviceTime = 2, v[4].processName = 'E';
    InitVariable();
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
    Print();
} // print Performance
void FIFO(vector<process> p)
{
    /*
        if need to sort ( arriveTime, priority( processName ) )

        vector<pair<int, char>> arr;
        for(int i = 0; i < p.size(); i++) {
            arr[i].first = p[i].arriveTime;
            arr[i].second = p[i].processName;
        }
        sort(&arr[0], &arr[arr.size()]);
    */
    for(int i = 0; i < 5; i++)
        result.push({p[i].processName, p[i].serviceTime});
}
int main() {
    SetInit();
    FIFO(v);
    getPerformance(v);
    Print();
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <string>
#include <string.h>
#include <stdio.h>
#include <math.h>
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
    getPerformance(p);
}
void MLFQ(vector<process> p, int exPow) {
    queue<process> q[3]; // 3개의 큐,
    int ts[3];
    for(int i = 0; i < 3; i++) {
        ts[i] = pow(exPow, i);
    }
    int time = 0;
    int nextIdx = 1;
    bool newProcess = false;
    int killedProcess = 0;
    int ready = 1;
    q[0].push(p[0]);
    while (killedProcess < p.size()) {
        for(int j = 0; j < 3; j++)
        {
            while(!q[j].empty())
            {
                if((j == 1 || j == 2) && newProcess) // 새로운 프로세스가 들어왔으면 1 ,2 레벨 큐로 안내려감
                    break;
                newProcess = false;
                process temp = q[j].front();
                int restTime = temp.serviceTime - ts[j];
                if(restTime <= 0) { // 남은 시간이 없을 때,
                    time += temp.serviceTime;
                    result.push({temp.processName, q[j].front().serviceTime});
                    q[j].pop();
                    killedProcess++;
                    for(int i = nextIdx; i < p.size(); i++) {
                        if(time >= p[i].arriveTime) {
                            q[0].push(p[i]);
                            nextIdx = i + 1;
                            newProcess = true;
                            if(j == 0)
                                ready++;
                        }
                    }
                } else {
                    time += ts[j];
                    for(int i = nextIdx; i < p.size(); i++) {
                        if (time >= p[i].arriveTime) {
                            q[0].push(p[i]);
                            nextIdx = i + 1;
                            newProcess = true;
                            if(j == 0)
                                ready++;
                        }
                    }
                    temp.serviceTime -= ts[j];
                    result.push({temp.processName, ts[j]});
                    if(j == 0) // 0 레벨 큐
                    { // 프로세스가 수행되고 돌이올때까지 다른 프로세스가 큐에 다른 프로세스가 없으면 다음 레벨의 큐로 이동
                        if(ready != 1) {
                            q[0].pop();
                            q[1].push(temp);
                        } else {
                            q[0].pop();
                            q[0].push(temp);
                        }
                    }
                    else if(j == 2) // 2 레벨 큐
                    {
                        q[2].pop();
                        q[2].push(temp);
                    } else{ // 1 레벨 큐
                        q[1].pop();
                        q[2].push(temp);
                    }
                }
                if(newProcess) {
                    break;

                }
            }
        }
    }
}
void RR(vector<process> p, int ts) {
    int time = 0;
    int killedProcess = 0;
    int nextIdx = 1;
    queue<process> q;
    q.push(p[0]);
    while(killedProcess < p.size()) { // 모든 프로세스가 완료되면 종료
        process temp = q.front();
        int restTime = temp.serviceTime - ts; // 해당 프로세스의 남은 수행시간
        if(restTime <= 0) { // 프로세스의 남은 시간이 없을 때 (수행 종료)
            time += temp.serviceTime;
            result.push({temp.processName, q.front().serviceTime});
            q.pop();
            killedProcess++; // 완료된 프로세스 체크
            for(int i = nextIdx; i < p.size(); i++) { // 현재까지 시간보다 해당 프로세스의 도착시간이 같거나 작은 경우
                if(time >= p[i].arriveTime) {
                    q.push(p[i]);
                    nextIdx = i + 1;
                }
            }
        } else {
            time += ts;
            for(int i = nextIdx; i < p.size(); i++) { // 현재까지 시간보다 해당 프로세스의 도착시간이 같거나 작은 경우
                if(time >= p[i].arriveTime) {
                    q.push(p[i]);
                    nextIdx = i + 1;
                }
            }
            result.push({temp.processName, ts}); // 결과를 넣을 큐에 해당 프로세스 이름과, 타임슬라이스 넣어줌
            temp.serviceTime -= ts; // 수행시간 타임슬라이스 만큼 감소
            q.pop();
            q.push(temp); // 작업을 수행하고 다시 큐 안으로 들어옴
        }
    }
    getPerformance(p);
}
int main() {
    SetInit();
    FIFO(v);
    MLFQ(v, 1);
    RR(v, 1);
}

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
    v[0].arriveTime = 0, v[0].serviceTime = 3, v[0].processName = 'A';
    v[1].arriveTime = 2, v[1].serviceTime = 6, v[1].processName = 'B';
    v[2].arriveTime = 4, v[2].serviceTime = 4, v[2].processName = 'C';
    v[3].arriveTime = 6, v[3].serviceTime = 5, v[3].processName = 'D';
    v[4].arriveTime = 8, v[4].serviceTime = 2, v[4].processName = 'E';
}

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
void MLFQ(vector<process> p) {
    queue<process> q[3]; // 3개의 큐,
    int ts[3] = {1, 2, 4};
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
int main() {
    SetInit();
    MLFQ(v);
    Print();
    return 0;
}
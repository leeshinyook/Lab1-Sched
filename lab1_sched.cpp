#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <string>
#include <string.h>
using namespace std;
queue<pair<char, int>> qt;
struct process {
    char processName; // 프로세스 번호, priority
    int serviceTime; // 동작시간
    int arriveTime; // 도착시간
    int waitTime; // 대기시간
    /*for stride----*/
    int stride;
    int ticket;
    int passValue = 0; // initialize
    /*--------------*/
};
vector<process> v(5);
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
    int size = qt.size();
    vector<pair<char, int>> arr(size);
    for(int i = 0; i < size; i++) {
        arr[i].first = qt.front().first;
        arr[i].second = qt.front().second;
        time += qt.front().second;
        qt.pop();
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
    float avgWait = 0;
    vector<int> wait(p.size(), -1);
    while(!copy.empty())
    {
        for(int i = 0; i < p.size(); i++)
        {
            if(wait[i] == -1 && copy.front().first == p[i].processName)
            {
                p[i].waitTime = wait[i] = time - p[i].arriveTime;
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
    float avgTurnaround = 0;
    vector<int> turnaround(p.size(), 0);
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
int main() {
    SetInit();
    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <string>
#include <string.h>
using namespace std;
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
    v[0].arriveTime = 0, v[0].serviceTime = 3, v[0].processName = 'A';
    v[1].arriveTime = 2, v[1].serviceTime = 6, v[1].processName = 'B';
    v[2].arriveTime = 4, v[2].serviceTime = 4, v[2].processName = 'C';
    v[3].arriveTime = 6, v[3].serviceTime = 5, v[3].processName = 'D';
    v[4].arriveTime = 8, v[4].serviceTime = 2, v[4].processName = 'E';
}
void RR(vector<process> p, int timeSlice) {
    int timer = 0;
    int killedProcess = 0;
    int nextIdx = 1;
    queue<process> q;
    queue<pair<char, int>> qt; // 이름, 러닝타임
    q.push(p[0]);
    while(killedProcess < p.size()) {
        process temp = q.front();
        int restTime = temp.serviceTime - timeSlice;
        timer += timeSlice;
        if(restTime <= 0) {
            timer -= timeSlice;
            timer += temp.serviceTime;
            qt.push({temp.processName, q.front().serviceTime});
            q.pop();
            killedProcess++;
            for(int i = nextIdx; i < p.size(); i++) {
                if(timer >= p[i].arriveTime) {
                    q.push(p[i]);
                    nextIdx = i + 1;
                }
            }
        } else {
            for(int i = nextIdx; i < p.size(); i++) {
                if(timer >= p[i].arriveTime) {
                    q.push(p[i]);
                    nextIdx = i + 1;
                }
            }
            qt.push({temp.processName, timeSlice});
            temp.serviceTime -= timeSlice;
            q.pop();
            q.push(temp);
        }
    }
    int size = qt.size();
    for(int i = 0; i < size; i++) {
        cout << qt.front().first << " " << qt.front().second << "\n";
        qt.pop();
    }
}
int main() {
    SetInit();
    RR(v, 4);

    return 0;
}
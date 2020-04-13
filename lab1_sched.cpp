#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <string>
#include <string.h>
using namespace std;
<<<<<<< HEAD
int qsize = 0;
typedef struct process {
    char processName; // 프로세스 이름, priority
    int serviceTime; // 동작시간
    int arriveTime; // 도착시간
    int waitTime; // 대기시간
} process;
queue<char> qt;
void SortByArriveTime(vector<process> p, int n) { // 도착시간이 빠른 것 부터, 정렬
    process temp;
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < i; j++) {
            if(p[j].arriveTime > p[j + 1].arriveTime) {
                swap(p[j], p[j + 1]);
            } else if(p[j].arriveTime == p[j + 1].arriveTime && p[j].processName > p[j + 1].processName) { // 번호가 빠른 것 부터
                swap(p[j], p[j + 1]);
            }
        }
    }
}
void RR(vector<process> p, int ts)
{
    int time = 0;
    int killedProcess = 0;
    int nextIdx = 1;
    int j = 0;
    float avgWait = 0, avgTurn = 0;
    queue<process> q;
    vector<int> response(p.size(), -1);
    vector<int> turnaround(p.size(), -1);
    q.push(p[0]);
    response[0] = 0;
    while(killedProcess < p.size()) { // 모든 프로세스가 완료되면 종료
        process temp = q.front();
        for(int i = 1; i < p.size(); i++)
        {
            if(temp.serviceTime == p[i].serviceTime && temp.processName == p[i].processName && response[i] == -1)
            {
                response[i] = time - p[i].arriveTime;
            }
        } // 각 프로세스의 대기시간
        int restTime = temp.serviceTime - ts; // 해당 프로세스의 남은 수행시간
        if(restTime <= 0) { // 프로세스의 남은 시간이 없을 때 (수행 종료)
            time += temp.serviceTime;
            qt.push(temp.processName);
            q.pop();
            for(int i = 0; i < p.size(); i++)
            {
                if(temp.processName == p[i].processName)
                    turnaround[i] = time;
            } // 각 프로세스에 대한 반환시간
            killedProcess++; // 완료된 프로세스 체크
            for(int i = nextIdx; i < p.size(); i++) {
                if(time >= p[i].arriveTime) { // 현재까지 시간보다 해당 프로세스의 도착시간이 같거나 작은 경우
=======
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
>>>>>>> bde1dd8c886e92a3b1a0714af7c21466626f0808
                    q.push(p[i]);
                    nextIdx = i + 1;
                }
            }
        } else {
<<<<<<< HEAD
            time += ts;
            for(int i = nextIdx; i < p.size(); i++) {
                if(time >= p[i].arriveTime) { // 현재까지 시간보다 해당 프로세스의 도착시간이 같거나 작은 경우
=======
            for(int i = nextIdx; i < p.size(); i++) {
                if(timer >= p[i].arriveTime) {
>>>>>>> bde1dd8c886e92a3b1a0714af7c21466626f0808
                    q.push(p[i]);
                    nextIdx = i + 1;
                }
            }
<<<<<<< HEAD
            qt.push(temp.processName); // 결과를 넣을 큐에 해당 프로세스 넣어줌
            temp.serviceTime -= ts; // 수행시간 타임슬라이스 만큼 감소
            q.pop();
            q.push(temp); // 작업을 수행하고 다시 큐 안으로 들어옴
        }
    }
    for(int i = 0; i < p.size(); i++)
    {
        p[i].waitTime = response[i];
        cout<<p[i].processName<<" - "<<"waitTime : "<<p[i].waitTime<<" turnaroundTime : "<<turnaround[i]<<"\n";
        avgWait += p[i].waitTime;
        avgTurn += turnaround[i];
    }
    avgWait /= p.size();
    avgTurn /= p.size();
    cout<<"Average waitTime : "<<avgWait<<" Average turnaroundTime : "<<avgTurn<<"\n";
}
void Print(vector<process> p) {
    char task[p.size()];
    int Tname = 'A';
    for(int i = 0; i < p.size(); i++)
        task[i] = Tname++;
    int size = qt.size();
    vector<char> arr(size);
    for(int i = 0; i < size; i++) {
        arr[i] = qt.front();
        qt.pop();
    }
    for(int i = 0; i < p.size(); i++) {
        cout << task[i] << " ";
        for(int j = 0; j < arr.size(); j++) {
            if(task[i] == arr[j]) {
                cout << "■ ";
            } else {
                cout << "□ ";
=======
            qt.push({temp.processName, timeSlice});
            temp.serviceTime -= timeSlice;
            q.pop();
            q.push(temp);
        }
    }
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
>>>>>>> bde1dd8c886e92a3b1a0714af7c21466626f0808
            }
        }
        cout << '\n';
    }
}
int main() {
<<<<<<< HEAD
    int count, ts;
    cout<<"Count of process, Time slice\n";
    cin >> count >> ts; // 프로세스 개수, time slice
    vector<process> p(count);
    cout<<"Process name,  Arrive time, Service time\n";
    for(int i = 0; i < count; i++)//프로세스 정보 입력
    {
        cin>>p[i].processName>>p[i].arriveTime>>p[i].serviceTime;
        qsize += p[i].serviceTime;
    }
    SortByArriveTime(p, count);
    RR(p, ts);
    Print(p);
=======
    SetInit();
    RR(v, 4);
    Print();
    return 0;
>>>>>>> bde1dd8c886e92a3b1a0714af7c21466626f0808
}
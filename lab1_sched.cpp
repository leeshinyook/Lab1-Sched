#include "lab1_sched_types.h"

/* perform 5 processes */
queue<pair<char, int> > result;
vector<process> v1(5);
vector<process> v2(5);
/* end of 5 processes */
/* for calculate and print performance */
float avgTurnaround = 0;
float avgWait = 0;
vector<int> turnaround(5, 0); // 5 processes
vector<int> pWait(5, -1); // 5 processes
/* end of calculate and print */

/* Initvariable(calculate and print) func */
void InitVariable() {
    avgTurnaround = 0;
    avgWait = 0;
    while(!result.empty()) result.pop();
    for(int i = 0; i < 5; i++) {
        turnaround[i] = 0;
        pWait[i] = -1;
    }
}
/* End of Initvariable(calculate and print) func*/

/* Set initialize two workloads */
void SetInit1() {
    v1[0].arriveTime = 0, v1[0].serviceTime = 3, v1[0].processName = 'A', v1[0].ticket = 100;
    v1[1].arriveTime = 2, v1[1].serviceTime = 6, v1[1].processName = 'B', v1[1].ticket = 50;
    v1[2].arriveTime = 4, v1[2].serviceTime = 4, v1[2].processName = 'C', v1[2].ticket = 250;
    v1[3].arriveTime = 6, v1[3].serviceTime = 5, v1[3].processName = 'D', v1[3].ticket = 400;
    v1[4].arriveTime = 8, v1[4].serviceTime = 2, v1[4].processName = 'E', v1[4].ticket = 200;
    InitVariable();
}
void SetInit2() { 
    v2[0].arriveTime = 0, v2[0].serviceTime = 4, v2[0].processName = 'A', v2[0].ticket = 200;
    v2[1].arriveTime = 1, v2[1].serviceTime = 2, v2[1].processName = 'B', v2[1].ticket = 100;
    v2[2].arriveTime = 5, v2[2].serviceTime = 6, v2[2].processName = 'C', v2[2].ticket = 250;
    v2[3].arriveTime = 7, v2[3].serviceTime = 5, v2[3].processName = 'D', v2[3].ticket = 1000;
    v2[4].arriveTime = 10, v2[4].serviceTime = 3, v2[4].processName = 'E', v2[4].ticket = 500;
    InitVariable();
}
/* End of set initialize two workloads */

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
void Print(vector<process> p) {
    int time;
    int size = result.size();
    vector<pair<char, int> > arr(size);
    for(int i = 0; i < size; i++) {
        arr[i].first = result.front().first;
        arr[i].second = result.front().second;
        result.pop();
    }
    for(int i = 0; i < 5; i++) {
        time = 0;
        cout << p[i].processName << " ";
        for(int j = 0; j < arr.size(); j++) {
            if(p[i].processName == arr[j].first) {
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
    queue<pair<char, int> > copy;
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
    queue<pair<char, int> > copy;
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
    Print(p);
    cout << "--------------------------------------------------------------------------" << '\n';
} // print Performance

void Stride(vector<process> p) {
    cout << "TITLE : \tStride cpu scheduling" << '\n';
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
            /*
                if don't set sequence of processName, then always need to sort by processName ( processName, passValue )
                
                vector<pair<char, int>> arr;
                for(int i = 0; i < p.size(); i++) {
                    arr[i].first = p[i].processName;
                    arr[i].second = p[i].passValue;
                }
                 sort(&arr[0], &arr[arr.size()]);
            */
            if(min > p[j].passValue) { // passValue가 가장 작은 프로세스부터 실행
                min = p[j].passValue;
                minIdx = j;
            }
        }
        result.push(make_pair(p[minIdx].processName, 1));
        p[minIdx].passValue += p[minIdx].stride; // stride만큼 passValue 증가
    }
    Print(p);
}
void FIFO(vector<process> p)
{
    cout << "TITLE : \tFirst-In-First-Out cpu scheduling" << '\n';
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
        result.push(make_pair(p[i].processName, p[i].serviceTime));
    getPerformance(p);
    SetInit1();
    SetInit2();
}
void MLFQ(vector<process> p, int exPow) {
    cout << "TITLE : \tMulti Level Feedback Queue cpu scheduling" << "\tq - " << exPow << "^i" << '\n';
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
                    result.push(make_pair(temp.processName, q[j].front().serviceTime));
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
                    result.push(make_pair(temp.processName, ts[j]));
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
    getPerformance(p);
    SetInit1();
    SetInit2();
}
void RR(vector<process> p, int ts) {
    cout << "TITLE : \tRound-Robin cpu scheduling" << "\tq - " << ts << '\n';
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
            result.push(make_pair(temp.processName, q.front().serviceTime));
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
            result.push(make_pair(temp.processName, ts)); // 결과를 넣을 큐에 해당 프로세스 이름과, 타임슬라이스 넣어줌
            temp.serviceTime -= ts; // 수행시간 타임슬라이스 만큼 감소
            q.pop();
            q.push(temp); // 작업을 수행하고 다시 큐 안으로 들어옴
        }
    }
    getPerformance(p);
    SetInit1();
    SetInit2();
}
void Run() {
    cout<<"First workloads\n\n";
    SetInit1();
    FIFO(v1);
    RR(v1, 1);
    RR(v1, 4);
    MLFQ(v1, 1);
    MLFQ(v1, 2);
    Stride(v1);
    cout<<'\n';
    cout<< "==========================================================================\n";
    cout<<"Second workloads\n\n";
    SetInit2();
    FIFO(v2);
    RR(v2, 1);
    RR(v2, 4);
    MLFQ(v2, 1);
    MLFQ(v2, 2);
    Stride(v2);
}
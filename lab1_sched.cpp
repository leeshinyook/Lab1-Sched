#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;
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
}
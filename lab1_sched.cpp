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
    v[0].arriveTime = 0, v[0].serviceTime = 3;
    v[1].arriveTime = 2, v[1].serviceTime = 6;
    v[2].arriveTime = 4, v[2].serviceTime = 4;
    v[3].arriveTime = 6, v[3].serviceTime = 5;
    v[4].arriveTime = 8, v[4].serviceTime = 2;
}
int main() {
    SetInit();
    return 0;
}
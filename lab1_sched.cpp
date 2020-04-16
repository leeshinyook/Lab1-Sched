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
        int min = INT_MIN;
        for(int j = 0; j < p.size(); j++) {
            if(min > p[j].passValue) { // passValue가 가장 작은 프로세스부터 실행
                min = p[j].passValue;
                minIdx = j;
            }
        }
        result.push(p[minIdx].processName, 1);
        p[minIdx].passValue += p[minIdx].stride; // stride만큼 passValue 증가
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
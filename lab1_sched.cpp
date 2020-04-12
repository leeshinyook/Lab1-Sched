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
    int TC = 100; // 얼마나 반복할건지.
    queue<char> q;
    int commonMulti = 1;
    int minIdx = 0;
    for(int i = 0; i < p.size(); i++) {
        commonMulti *= p[i].ticket;
        p[i].passValue = 0;
    }
    for(int i = 0; i < p.size(); i++) {
        p[i].stride = commonMulti / p[i].ticket;
    }
    for(int i = i; i < TC; i++) {
        int min = INT_MIN;
        for(int j = 0; j < p.size(); j++) {
            if(min > p[j].passValue) {
                min = p[j].passValue;
                minIdx = j;
            }
        }
        q.push(p[minIdx].processName);
        p[minIdx].passValue += p[minIdx].stride;
    }
}
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
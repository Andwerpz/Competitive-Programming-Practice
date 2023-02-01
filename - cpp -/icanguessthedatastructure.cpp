#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 02 B

//simple implementation

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    while(!cin.eof()) {
        int n;
        cin >> n;
        if(cin.eof()) {
            break;
        }
        stack<int> s;
        queue<int> q;
        priority_queue<int> pq;
        bool stackValid = true;
        bool queueValid = true;
        bool pqueueValid = true;
        for(int i = 0; i < n; i++){
            int type, val;
            cin >> type >> val;
            if(type == 1) {
                s.push(val);
                q.push(val);
                pq.push(val);
            }
            else {
                if(s.size() == 0){
                    stackValid = false;
                    queueValid = false;
                    pqueueValid = false;
                    continue;
                }
                if(s.top() != val) {
                    stackValid = false;
                }
                s.pop();
                if(q.front() != val){
                    queueValid = false;
                }
                q.pop();
                if(pq.top() != val) {
                    pqueueValid = false;
                }
                pq.pop();
            }
        }
        if(!stackValid && !queueValid && !pqueueValid) {
            cout << "impossible\n";
        }
        else if((stackValid? 1 : 0) + (queueValid? 1 : 0) + (pqueueValid? 1 : 0) >= 2) {
            cout << "not sure\n";
        }
        else if(stackValid) {
            cout << "stack\n";
        }
        else if(queueValid) {
            cout << "queue\n";
        }
        else if(pqueueValid) {
            cout << "priority queue\n";
        }
    }
    
    return 0;
}

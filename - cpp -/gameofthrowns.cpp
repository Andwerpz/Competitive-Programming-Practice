#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 13 E

//keep track of previous moves on the stack. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, k;
    cin >> n >> k;
    stack<int> s;
    int ptr = 0;
    for(int i = 0; i < k; i++){
        string next;
        cin >> next;
        if(next[0] == 'u'){
            int amt;
            cin >> amt;
            for(int j = 0; j < amt; j++){
                ptr -= s.top();
                s.pop();
                while(ptr < 0){
                    ptr += n;
                }
                ptr %= n;
            }
        }
        else {
            int amt = stoi(next);
            ptr += amt;
            while(ptr < 0){
                ptr += n;
            }
            ptr %= n;
            s.push(amt);
        }
    }
    cout << ptr << "\n";
    
    return 0;
}

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 01 H

//you're pretty much trying to implement queue with two stacks. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    while(n != 0){
        int cnt1 = 0;   //to wash
        int cnt2 = 0;   //from waiter
        for(int i = 0; i < n; i++){
            string type;
            int amt;
            cin >> type >> amt;
            if(type == "DROP") {
                cout << "DROP 2 " << amt << "\n";
                cnt2 += amt;
            }
            else if(type == "TAKE") {
                if(cnt1 < amt && cnt1 != 0) {
                    cout << "TAKE 1 " << cnt1 << "\n";
                    amt -= cnt1;
                    cnt1 = 0;
                }
                if(cnt1 == 0){
                    cout << "MOVE 2->1 " << cnt2 << "\n";
                    cnt1 = cnt2;
                    cnt2 = 0;
                }
                cout << "TAKE 1 " << amt << "\n";
                cnt1 -= amt;
            }
        }
        cout << "\n";
        cin >> n;
    }
    
    return 0;
}

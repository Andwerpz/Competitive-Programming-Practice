
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces - 1606B

//there are two phases, one before we can utilize all our cables, and one after we can utilize our cables. 

//since k <= 10^18, we can simulate the first phase, as it won't take longer than log2(10^18) iterations. 
//this is because the number of computers that have the files double each iteration. 

//for the second phase, we can just directly compute the amount of hours required. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        ll n, k;
        cin >> n >> k;
        ll active = 1;
        if(n == 1){
            cout << 0 << endl;
            continue;
        }
        //'windup' phase
        ll hours = 0;
        bool done = false;
        while(true){
            hours ++;
            active += min(active, k);
            if(active >= n){
                done = true;
                break;
            }
            if(active >= k){
                break;
            }
        }
        if(done){
            cout << hours << endl;
            continue;
        }
        //calculate remaining time
        ll diff = n - active;
        hours += diff / k + (diff % k == 0? 0 : 1);
        cout << hours << endl;
    }
    
    return 0;
}

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC Weekly Problemset 3F

//for each station, keep track of the first and last time the train visits it. If you want to get from station a to b, 
//then you just need to check that the first time the train visits a is eariler than the last time the train visits b. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, k;
        cin >> n >> k;
        map<int, int> first;
        map<int, int> last;
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            if(first.find(next) == first.end()){
                first.insert({next, i});
                last.insert({next, i});
            }
            last.find(next) -> second = max(last.find(next) -> second, i);
        }
        for(int i = 0; i < k; i++){
           int a, b;
           cin >> a >> b;
           if(first.find(a) == first.end() || first.find(b) == first.end()){
                cout << "NO\n";
                continue;
           } 
           if(first.find(a) -> second <= last.find(b) -> second){
                cout << "YES\n";
           }
           else{
                cout << "NO\n";
           }
        }
    }
    
    return 0;
}

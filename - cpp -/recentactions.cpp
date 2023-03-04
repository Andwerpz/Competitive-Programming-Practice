#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1799A

//use a queue to represent the recent actions queue. 
//if items in the recent action queue were guaranteed to not be put back at the top, then this would suffice, 
//but unfortunately, items in the recent actions queue can be put back at the top. 

//thus, what you can do if something gets put back at the top is to just insert it into the queue again, and use a
//map to keep track of how many instances of that item are in the queue. 

//items only get removed if something that was not in the stack gets added

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        map<int, int> mp;
        queue<int> q;
        for(int i = 0; i < n; i++){
            q.push(n - i);
            mp.insert({n - i, 1});
        }
        vector<int> ans(n, -1);
        for(int i = 0; i < m; i++){
            int next;
            cin >> next;
            if(mp.find(next) != mp.end()) {
                mp.find(next) -> second ++;
                q.push(next);
            }
            else {
                q.push(next);
                mp.insert({next, 1});
                while(mp.find(q.front()) -> second != 1){
                    mp.find(q.front()) -> second --;
                    q.pop();
                }
                if(q.front() >= 1 && q.front() <= n) {
                    ans[q.front() - 1] = i + 1;
                }
                mp.erase(q.front());
                q.pop();
            }
        }
        for(int i = 0; i < n; i++){
            cout << ans[i] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}

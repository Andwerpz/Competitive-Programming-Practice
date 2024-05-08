#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//2024 ICPC EUC - G

//just do a greedy strategy. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n;
    cin >> n;
    string ctype, ptype;
    cin >> ctype >> ptype;
    queue<int> start, c_end, m_end, mc, cm;
    for(int i = 0; i < n; i++){
        if(ctype[i] == '-' && (ptype[i] == 'C' || ptype[i] == 'M')) {
            start.push(i + 1);
        }
        if(ctype[i] == 'M' && ptype[i] == '-') {
            m_end.push(i + 1);
        }
        if(ctype[i] == 'C' && ptype[i] == '-') {
            c_end.push(i + 1);
        }
        if(ctype[i] == 'C' && ptype[i] == 'M') {
            cm.push(i + 1);
        }
        if(ctype[i] == 'M' && ptype[i] == 'C') {
            mc.push(i + 1);
        }
    }
    vector<string> ans(0);
    while(start.size() != 0){
        int ptr = start.front();
        start.pop();
        char cur = ptype[ptr - 1];
        ans.push_back("DRIVE " + to_string(ptr));
        while(true){
            int next = -1;
            if(cur == 'C' && cm.size() != 0){
                next = cm.front();
                cm.pop();
            }
            else if(cur == 'M' && mc.size() != 0){
                next = mc.front();
                mc.pop();
            }
            else {
                break;
            }
            ans.push_back("PICKUP");
            ans.push_back("DRIVE " + to_string(next));
            ans.push_back("DROPOFF");
            ptr = next;
            cur = cur == 'C'? 'M' : 'C';
        }   
        int next = -1;
        if(cur == 'C' && c_end.size() != 0) {
            next = c_end.front();
            c_end.pop();
        }
        else if(cur == 'M' && m_end.size() != 0){
            next = m_end.front();
            m_end.pop();
        }
        if(next != -1){
            ans.push_back("PICKUP");
            ans.push_back("DRIVE " + to_string(next));
            ans.push_back("DROPOFF");
        }
    }
    cout << ans.size() << "\n";
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << "\n";
    }
    
    return 0;
}

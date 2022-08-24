#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1552F

//in the case that all portals are active, it is pretty apparent that you can use dp to solve this problem. 
//the problem is that not all portals start active, and portal states can change during the walk. 

//the key is to notice that if an ant is to the right of a portal entrance, then that entrance must be active. 
//this is true simply because an ant can only pass a portal entrance if it is inactive, thus turning it active. 

//so the solution is to use dp to compute for each portal, what is the time required to move from exit to 
//entrance. To compute this, we also have to save two other things, the time required to move from 0 to entrance, 
//and the time required to move from 0 to exit. 

//it can be shown that time from exit to entrance is equal to time from 0 to entrance - 0 to exit. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll mod = 998244353;
    int n;
    cin >> n;
    vector<ll> ts(n);  //get from 0 to p[i][0] for the first time
    vector<ll> te(n);
    vector<ll> tes(n); //time from end to start
    vector<vector<ll>> p(n, vector<ll>(3));   //s, e, active
    vector<vector<ll>> a(n * 2, vector<ll>(3)); //loc, 1 : s; 0 : e, id
    for(int i = 0; i < n; i++){
        cin >> p[i][0] >> p[i][1] >> p[i][2];
    }
    sort(p.begin(), p.end(), [](vector<ll>& b, vector<ll>& c) {return b[0] < c[0];});
    for(int i = 0; i < n; i++){
        a[i * 2 + 0][0] = p[i][0];
        a[i * 2 + 0][1] = 1;
        a[i * 2 + 0][2] = i;
        a[i * 2 + 1][0] = p[i][1];
        a[i * 2 + 1][1] = 0;
        a[i * 2 + 1][2] = i;
    }
    sort(a.begin(), a.end(), [](vector<ll>& b, vector<ll>& c) {return b[0] < c[0];});
    te[a[0][2]] = a[0][0];
    for(int i = 1; i < n * 2; i++){        
        int id = (int) a[i][2];
        int prevId = (int) a[i - 1][2];
        if(a[i][1] == 0){   //looking at an exit
            int prevType = a[i - 1][1];
            if(prevType == 1){
                //cout << "PREV IS PORTAL\n";
                //cout << ts[prevId] << " " << tes[prevId] << " " << prevId << "\n";
                te[id] = (ts[prevId] + tes[prevId]) % mod + (a[i][0] - a[i - 1][0]);
                te[id] %= mod;
            }
            else{
                te[id] = te[prevId] + (a[i][0] - a[i - 1][0]);
                te[id] %= mod;
            }
            continue;
        }
        //looking at a start
        //cout << "START: " << a[i][0] << "\n";
        ll curEnd = p[id][1];
        ll curStart = p[id][0];
        ll prevStart = id == 0? 0 : p[id - 1][0];
        if(id == 0){    //first portal
            //cout << "FIRST\n";
            ts[id] = a[i][0];
            tes[id] = p[id][0] - p[id][1];
            continue;
        }
        //find prev start
        if(curEnd > prevStart){ //we didn't go backwards far enough to trigger other portals
            //cout << "NOT ENOUGH\n";
            ts[id] = (ts[id - 1] + tes[id - 1]) % mod + (curStart - prevStart);
            ts[id] %= mod;
            tes[id] = p[id][0] - p[id][1];
        }
        else{
            //cout << "PORTAL\n";
            ts[id] = ((ts[id - 1] + tes[id - 1]) % mod) + (curStart - prevStart);
            ts[id] %= mod;
            tes[id] = ((ts[id - 1] - te[id]) + tes[id - 1]) % mod + (curStart - prevStart);
            tes[id] %= mod;
        }
    }
    ll ans = 0;
    int ptr = 0;
    for(int i = 0; i < n; i++){
        //cout << ts[i] << " " << te[i] << " " << tes[i] << "\n";
        int start = p[i][0];
        ans += p[i][0] - ptr;
        ans %= mod;
        ptr = p[i][0];
        if(p[i][2] == 0){
            continue;
        }
        ans += tes[i];
        ans %= mod;
    }
    while(ans < 0){
        ans += mod;
    }
    ans %= mod;
    cout << (ans + 1) % mod << "\n";
    
    return 0;
}

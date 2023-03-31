#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 09 A

//implementation. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        map<string, vector<ll>> car;
        for(int i = 0; i < n; i++){
            string s;
            cin >> s;
            int a, b, c;
            cin >> a >> b >> c;
            car.insert({s, {a, b, c}});
        }
        map<string, ll> cost;
        set<string> incon;
        map<string, string> hascar;
        for(int i = 0; i < m; i++){
            int time;
            string s, e;
            cin >> time >> s >> e;
            ll add = 0;
            if(e == "p"){
                if(hascar.find(s) != hascar.end()) {
                    incon.insert(s);
                }
                string c;
                cin >> c;
                hascar.insert({s, c});
                add = car.find(c) -> second[1];
            }
            else if(e == "r") {
                ll dist;
                cin >> dist;
                if(hascar.find(s) == hascar.end()) {
                    incon.insert(s);
                }
                else {
                    add = dist * car.find(hascar.find(s) -> second) -> second[2];
                    hascar.erase(s);
                }
            }
            else if(e == "a") {
                ld sev;
                cin >> sev;
                sev = sev * 0.01;
                if(hascar.find(s) == hascar.end()) {
                    incon.insert(s);
                }
                else {
                    ld rep = sev * (ld) car.find(hascar.find(s) -> second) -> second[0];
                    add = (ll) floor(rep + 0.9999999);
                }
            }
            if(cost.find(s) == cost.end()) {
                cost.insert({s, 0});
            }
            cost.find(s) -> second += add;
        }
        for(auto i = hascar.begin(); i != hascar.end(); i++){
            string s = i -> first;
            incon.insert(s);
        }
        for(auto i = cost.begin(); i != cost.end(); i++){
            cout << i -> first << " ";
            if(incon.find(i -> first) != incon.end()) {
                cout << "INCONSISTENT";
            }
            else {
                cout << i -> second;
            }
            cout << "\n";
        }
    }
    
    return 0;
}

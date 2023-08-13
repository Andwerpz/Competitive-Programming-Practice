#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1811F

//implementation. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<vector<int>> c(n, vector<int>(0));
        for(int i = 0; i < m; i++){
            int a, b;
            cin >> a >> b;
            a --; 
            b --;
            c[a].push_back(b);
            c[b].push_back(a);
        }
        //find all nodes in the 'main cycle'.
        bool isValid = true;
        set<int> main;
        for(int i = 0; i < n; i++){
            if(c[i].size() == 4) {
                main.insert(i); 
            }
            else if(c[i].size() != 2){
                //cout << "BAD EDGE AMOUNT\n";
                isValid = false;
            }
        }
        //see if main cycle nodes actually form a cycle
        int k = main.size();
        vector<bool> v(n, false);
        if(main.size() == 0){
            //cout << "SIZE 0 MAIN\n";
            isValid = false;
        }
        else {
            int cur = *main.begin();
            int nrv = 1;
            v[cur] = true;
            while(true) {
                for(int i = 0; i < 4; i++){
                    int next = c[cur][i];
                    if(main.find(next) != main.end() && !v[next]) {
                        cur = next;
                        break;
                    }
                }
                if(!v[cur]) {
                    v[cur] = true;
                    nrv ++;
                    continue;
                }
                break;
            }
            if(nrv != k){
                //cout << "CAN'T FIND MAIN CYCLE\n";
                isValid = false;
            }
        }
        //check all of the other cycles to make sure they are size k
        for(auto i = main.begin(); i != main.end(); i++){
            int mn = *i;
            int cur = -1;
            int end = -1;
            for(int j = 0; j < 4; j++){
                int next = c[mn][j];
                if(main.find(next) != main.end() || v[next]) {
                    continue;
                }
                cur = next;
                v[cur] = true;
                break;
            }
            if(cur == -1){
                //cout << "CAN'T FIND SUBCYCLE\n";
                isValid = false;
                break;
            }
            for(int j = 0; j < 4; j++){
                int next = c[mn][j];
                if(main.find(next) != main.end() || v[next]) {
                    continue;
                }
                end = next;
                break;
            }
            if(end == -1){
                isValid = false;
                break;
            }
            int nrv = 2;
            while(true) {
                //cout << "CUR : " << cur << "\n";
                for(int j = 0; j < c[cur].size(); j++){
                    int next = c[cur][j];
                    if(main.find(next) != main.end() || v[next]) {
                        //cout << "BAD NEXT " << next << "\n";
                        continue;
                    }
                    cur = next;
                    break;
                }
                if(!v[cur]) {
                    v[cur] = true;
                    nrv ++;
                    continue;
                }
                break;
            }
            if(cur != end) {
                isValid = false;
            }
            if(nrv != k){
                //cout << "BAD SUBCYCLE " << nrv << " " << k << "\n";
                isValid = false;
            }
        }
        //check that everything is visited
        for(int i = 0; i < n; i++){
            if(!v[i]) {
                //cout << "UNVISITED\n";
                isValid = false;
            }
        }
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}

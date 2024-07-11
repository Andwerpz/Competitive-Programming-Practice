#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1975E

//misread problem during contest, missed the part where they said that every node on the simple path had to be
//black. 

//let's root the tree at node 0. First thing we can observe is that there should only be 1 black node that has
//a white parent. Second, is that there should be at most 1 black node that has 2 black children, and no 
//black nodes should have more than 2 children. If those two conditions are satisfied, then the black
//nodes form a simple path through the tree. 

//we can maintain those counts in O(1) time for every query, but O(log(n)) works as well. 

void insert(map<int, int>& m, int val) {
    m[val] ++;
}

void erase(map<int, int>& m, int val) {
    m[val] --;
    if(m[val] == 0){
        m.erase(m.find(val));
    }
}

void find_parent(int cur, int p, vector<vector<int>>& c, vector<int>& parent) {
    parent[cur] = p;
    for(int i = 0; i < c[cur].size(); i++){
        int next = c[cur][i];
        if(next == p){
            continue;
        }
        find_parent(next, cur, c, parent);
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, q;
        cin >> n >> q;
        vector<bool> is_black(n, false);
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            is_black[i] = next;
        }
        vector<vector<int>> c(n);
        for(int i = 0; i < n - 1; i++){
            int x, y;
            cin >> x >> y;
            x --;
            y --;
            c[x].push_back(y);
            c[y].push_back(x);
        }
        vector<int> parent(n, -1);
        find_parent(0, -1, c, parent);
        int nr_no_parent = 0;   //nr black nodes without a parent black node
        map<int, int> m;    //for every number of children, how many black nodes are there that match?
        vector<int> nr_bc(n, 0);
        vector<int> nr_tc(n, 0);    //nr top childs?
        int nr_occ_tc = 0;
        for(int i = 0; i < n; i++){
            if(!is_black[i]) {
                continue;
            }
            if(parent[i] == -1){
                nr_no_parent ++;
                continue;
            }
            if(!is_black[parent[i]]) {
                nr_no_parent ++;
            }
            nr_bc[parent[i]] ++;
            // cout << "INC NR_BC : " << i << "\n";
        }
        for(int i = 0; i < n; i++){
            if(!is_black[i]) {
                continue;
            }
            insert(m, nr_bc[i]);
            if(nr_bc[i] >= 2 && parent[i] != -1){
                nr_tc[parent[i]] ++;
                if(is_black[parent[i]]) {
                    nr_occ_tc ++;
                }
            }
            // cout << "INSERT : " << nr_bc[i] << "\n";
        }
        for(int i = 0; i < q; i++){
            int x;
            cin >> x;
            x --;
            if(is_black[x]) {
                if(parent[x] == -1 || !is_black[parent[x]]) {
                    nr_no_parent --;
                }
                nr_occ_tc -= nr_tc[x];
                nr_no_parent += nr_bc[x];
                erase(m, nr_bc[x]);
                if(parent[x] != -1){
                    int p = parent[x];
                    nr_bc[p] --;
                    if(is_black[parent[x]]) {
                        erase(m, nr_bc[p] + 1);
                        insert(m, nr_bc[p]);
                    }
                    if(nr_bc[p] == 1 && parent[p] != -1){
                        int pp = parent[p];
                        nr_tc[pp] --;
                        if(is_black[pp]) {
                            nr_occ_tc --;
                        }
                    }
                }
            }
            else {
                if(parent[x] == -1 || !is_black[parent[x]]) {
                    nr_no_parent ++;
                }
                nr_occ_tc += nr_tc[x];
                nr_no_parent -= nr_bc[x];
                insert(m, nr_bc[x]);
                if(parent[x] != -1){
                    int p = parent[x];
                    nr_bc[p] ++;
                    if(is_black[parent[x]]) {
                        erase(m, nr_bc[p] - 1);
                        insert(m, nr_bc[p]);
                    }
                    if(nr_bc[p] == 2 && parent[p] != -1){
                        int pp = parent[p];
                        nr_tc[pp] ++;
                        if(is_black[pp]) {
                            nr_occ_tc ++;
                        }
                    }
                }
            }
            is_black[x] = !is_black[x];
            //do check
            // cout << "NR NO PARENT : " << nr_no_parent << "\n";
            bool is_valid = false;
            if(nr_no_parent != 1){
                goto done_check;
            }
            if(m.size() == 0 || m.rbegin() -> first > 2) {
                goto done_check;
            }
            if(nr_occ_tc != 0){
                goto done_check;
            }
            is_valid = true;
            done_check:
            cout << (is_valid? "Yes" : "No") << "\n";
        }
    }
    
    return 0;
}
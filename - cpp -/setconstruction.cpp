#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1761C

//denote A_i as the ith set. 

//they literally give us an adjacency matrix, so we should probably view this problem as a graph. An edge is drawn 
//from i to j if i is a subset of j. A natural approach to solve this problem is to process the sets in topological
//order. 

//First, we can assign to each set an element that matches their index, A_1 = {1}, A_2 = {2} and so on. Then, we sort
//all the sets in topological order, and process them one by one. When processing a set, we look at all the sets it 
//should be a 'parent' to, and add all of their elements to itself. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<vector<int>> c(n, vector<int>(0));
        vector<vector<int>> cr(n, vector<int>(0));
        vector<int> indeg(n, 0);
        for(int i = 0; i < n; i++){
            string s;
            cin >> s;
            for(int j = 0; j < n; j++){
                if(s[j] == '1') {
                    //i is a subset of j
                    cr[j].push_back(i);
                    indeg[j] ++;
                    c[i].push_back(j);
                }
            }
        }
        int ptr = 1;
        queue<int> q;
        vector<set<int>> s(n, set<int>());
        for(int i = 0; i < n; i++){
            if(indeg[i] == 0){
                q.push(i);
            }
        }
        while(q.size() != 0){
            int cur = q.front();
            q.pop();
            s[cur].insert(ptr ++);
            for(int i = 0; i < cr[cur].size(); i++){
                for(auto j = s[cr[cur][i]].begin(); j != s[cr[cur][i]].end(); j++){
                    s[cur].insert(*j);
                }
            }
            for(int i = 0; i < c[cur].size(); i++){
                int next = c[cur][i];
                indeg[next] --;
                if(indeg[next] == 0){
                    q.push(next);
                }
            }   
        }
        for(int i = 0; i < n; i++){
            cout << s[i].size() << " ";
            for(auto j = s[i].begin(); j != s[i].end(); j++){
                cout << *j << " ";
            }
            cout << "\n";
        }
    }
    
    return 0;
}
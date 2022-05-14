#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 920E

//we can just do a normal bfs. 

//maintain a set of unvisited nodes. Since the graph is undirected, if we can visit it from a source node, then
//it is part of that source node's component. 

//when we try to visit other nodes from a given node, we can iterate through all the unvisited nodes. An attempt to visit
//a new node will fail if that connection is one of the m unordered pairs specified. When we successfully visit a node, we
//can remove that node from the set of unvisited nodes. 

//notice that since there are only m unordered pairs, the amount of times that a visit can fail, given the above strategy
//is 2m. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    set<pair<int, int>> noC;
    for(int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        noC.insert({x - 1, y - 1});
        noC.insert({y - 1, x - 1});
    }
    set<int> notV;
    for(int i = 0; i < n; i++){
        notV.insert(i);
    }
    vector<int> ans(0);
    for(int i = 0; i < n; i++){
        if(notV.find(i) == notV.end()){
            continue;
        }
        //cout << "START: " << i << endl;
        int cnt = 0;
        stack<int> s;
        notV.erase(i);
        s.push(i);
        //cout << "START: " << notV.size() << endl;
        while(s.size() != 0){
            cnt ++;
            int cur = s.top();
            s.pop();
            vector<int> visit(0);
            for(int i : notV){
                //cout << "TEST: " << cur << " " << i << endl;
                if(noC.find({cur, i}) == noC.end()){
                    //cout << "PUSH: " << i << endl;
                    visit.push_back(i);
                    s.push(i);
                }
            }
            for(int i : visit){
                //cout << "ERASE: " << i << endl;
                notV.erase(i);
            }
        }
        ans.push_back(cnt);
    }
    cout << ans.size() << endl;
    sort(ans.begin(), ans.end());
    for(int i : ans){
        cout << i << " ";
    }
    cout << endl;
    
    return 0;
}

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1534D

//notice that all trees are bipartite. 

//lets say that the nodes are colored red and blue. Notice that min(number of red, number of blue) <= floor(n / 2).
//also notice that if we search across only red or blue nodes, then we can reconstruct the graph, as all blue nodes are 
//adjacent to a red node, and vice versa. 

//so, use one operation to figure out the amounts of red and blue nodes. Then, search across the group that is smaller. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    //figure out starting node
    cout << "? 1" << endl;
    vector<int> a(n);
    int oddi = -1;
    int even = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        if(a[i] % 2 == 1){
            oddi = i;
        }
        else {
            even ++;
        }
    }
    stack<int> s;   
    vector<pair<int, int>> c(0);
    vector<bool> v(n);
    if(even <= n - even){
        v[0] = true;
        for(int i = 1; i < n; i++){
            if(a[i] == 1){
                v[i] = true;
                c.push_back({0, i});
            }
            if(a[i] == 2){
                v[i] = true;
                s.push(i);
            }
        }
    }
    else {
        s.push(oddi);
        v[oddi] = true;
    }
    while(s.size() != 0){
        int cur = s.top();
        s.pop();
        cout << "? " << cur + 1 << endl;
        for(int i = 0; i < n; i++){
            int dist;
            cin >> dist;
            if(dist == 1){
                c.push_back({cur, i});
                v[i] = true;
            }
            if(v[i]){
                continue;
            }
            if(dist == 2){
                v[i] = true;
                s.push(i);
            }
        }
    }
    cout << "!\n";
    for(int i = 0; i < n - 1; i++){
        cout << (c[i].first + 1) << " " << (c[i].second + 1) << "\n";
    }
    cout << endl;
    
    return 0;
}

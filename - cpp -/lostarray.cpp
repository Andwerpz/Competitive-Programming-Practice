#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1534E

//there's not much else we can do other than taking each query and adding it to an xor total. 

//with this in mind, probably the most important thing we can keep track of is how many elements are currently inside the
//xor total. It doesn't actually matter which elements are inside, just the count. 

//so, to find the minimum amount of queries to get from 0 elements inside to n elements, we can just run bfs. This will
//also give us the way to get from 0 to n. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ll n, k;
    cin >> n >> k;
    vector<int> d(n + 1, 1e9), p(n + 1, -1), p_took(n + 1, -1);
    d[0] = 0;
    queue<int> q;
    q.push(0);
    while(q.size() != 0){
        int cur = q.front();
        q.pop();
        // cout << "CUR : " << cur << " " << d[cur] << endl;
        //where can we go from here?
        for(int i = 0; i <= k; i++){
            //how many included can we take?
            if(i > cur || k - i > n - cur) {
                continue;
            }
            int next = cur - i + k - i;
            if(d[next] <= d[cur] + 1) {
                continue;
            }
            d[next] = d[cur] + 1;
            q.push(next);
            p[next] = cur;
            p_took[next] = i;
        }
    }
    if(d[n] == 1e9) {
        cout << "-1\n";
        return 0;
    }
    //find path from n to 0
    vector<int> path(0);
    int ptr = n;
    while(ptr != 0){
        path.push_back(ptr);
        ptr = p[ptr];
    }
    reverse(path.begin(), path.end());
    //execute path using queries
    int ans = 0;
    stack<int> in, out;
    for(int i = 1; i <= n; i++){
        out.push(i);
    }
    vector<int> cq(k);
    for(int i = 0; i < path.size(); i++){
        // cout << "I : " << i << endl;
        int cur = path[i];
        int took = p_took[cur];
        for(int j = 0; j < k; j++){
            if(j < took){
                cq[j] = in.top();
                in.pop();
            }
            else {
                cq[j] = out.top();
                out.pop();
            }
        }
        cout << "? ";
        for(int j = 0; j < k; j++){
            cout << cq[j] << " ";
            if(j < took) {
                out.push(cq[j]);
            }
            else {
                in.push(cq[j]);
            }
        }
        cout << endl;
        int next;
        cin >> next;
        ans ^= next;
    }
    cout << "! " << ans << "\n";
    
    return 0;
}

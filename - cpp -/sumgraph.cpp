#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1815B

//first, we can use two type one operations where x = n + 1 and x = n + 2. 
//after these two operations, the graph will look like a linked list, for example when n = 6, then it will look like
//1--6--2--5--3--4

//then, we can try to find the two ends of this linked list, one of which has to be 1. 
//once we found an end of the list, then we can try to figure out the rest of the values based off of their distance from the end. 

int findone(int n) {
    int base = 0;
    vector<pair<int, int>> d(0);    //dist, index
    set<int> v;
    bool baseone = true;
    for(int i = 1; i < n; i++){
        cout << "? " << (base + 1) << " " << (i + 1) << endl;
        int dist;
        cin >> dist;
        if(v.find(dist) != v.end()){
            baseone = false;
        }
        v.insert(dist);
        d.push_back({dist, i});
    }
    sort(d.begin(), d.end());
    reverse(d.begin(), d.end());
    return d[0].second;
}

vector<int> solve(int n, vector<int>& m, vector<int>& d, int one) {
    vector<int> ans(n, 0);
    for(int i = 0; i < n; i++){
        int dist = d[i];
        ans[i] = m[dist];
    }
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> m(n, 0);
        int lptr = 0;
        int rptr = n - 1;
        for(int i = 0; i < n; i += 2){
            m[i] = lptr ++;
            if(i != n - 1){
                m[i + 1] = rptr --;
            }
        }
        int addstatus = -1;
        cout << "+ " << n + 1 << endl;
        cin >> addstatus;
        cout << "+ " << n + 2 << endl;
        cin >> addstatus;
        vector<int> d(n, 0);
        int o1 = findone(n);   //tentative one
        //find the other one
        int o2 = -1;
        for(int i = 0; i < n; i++){
            if(i == o1){
                continue;
            }
            int dist;
            cout << "? " << (o1 + 1) << " " << (i + 1) << endl;
            cin >> dist;
            if(dist == n - 1) {
                o2 = i;
            }
            d[i] = dist;
        }
        vector<int> a1 = solve(n, m, d, o1);
        //reverse distance for the second one
        for(int i = 0; i < n; i++){
            d[i] = n - 1 - d[i];
        }
        vector<int> a2 = solve(n, m, d, o2);
        cout << "! ";
        for(int i = 0; i < a1.size(); i++){
            cout << (a1[i] + 1) << " ";
        }
        for(int i = 0; i < a2.size(); i++){
            cout << (a2[i] + 1) << " ";
        }
        cout << endl;
        cin >> addstatus;
    }
    
    return 0;
}

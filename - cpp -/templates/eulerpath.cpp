#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void euler_path(vector<vector<int>>& c, vector<int>& ptr, vector<int>& ans, int i) {
    while(ptr[i] < c[i].size()) {
        int next = c[i][ptr[i] ++];
        euler_path(c, ptr, ans, next);
    }
    ans.push_back(i);
}

//an euler tour only exists if the degrees of all vertices are even
//an euler path only exists if the number of vertices with odd degrees are two, or zero, in which case an euler cycle exists. 
//and of course, the graph is sufficiently connected. 

//this function doesn't check any of those. TODO make it do that
vector<int> euler_path(vector<vector<int>>& c, int i) {
    int n = c.size();
    vector<int> ptr(n, 0);
    vector<int> ans(0);
    euler_path(c, ptr, ans, i);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    
    
    return 0;
}

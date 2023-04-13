#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1740E

//notice that the hearts always form some sort of rooted tree. 

//it is always ideal to put the smaller numbers closer to the leaves, and the largest number at the root. 
//i can't prove it, but just trust me bro D:

//we can notice when we place the numbers like this, if the tree is like a linked list, then any heart that we remove
//from the tree will have the minimum number, 1, written on it. 

//notice that if a node has two or more children, then to include it into the nondecreasing subsequence, we have to 
//not include all but one of the children. Alternatively, we can include all of the children, but not include the root. 

pair<int, int> solve(vector<vector<int>>& c, int i) {
    pair<int, int> ans = {0, 1};
    for(int j = 0; j < c[i].size(); j++){
        pair<int, int> next = solve(c, c[i][j]);
        ans.second = max(ans.second, next.second + 1);
        ans.first += next.first;
    }
    ans.first = max(ans.first, ans.second);
    //cout << "I : " << i << " " << ans.first << " " << ans.second << "\n";
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<int>> c(n, vector<int>(0));
    for(int i = 1; i < n; i++){
        int a;
        cin >> a;
        a--;
        c[a].push_back(i);
    }
    cout << solve(c, 0).first << "\n";
    
    return 0;
}

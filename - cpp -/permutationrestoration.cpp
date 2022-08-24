#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1701D

//default behaviour in set<pair<int, int>> is return a.first < b.first;

//for each number, we can calculate a range of numbers that it can be. For example: if the index is 4 
//and the b_4 = 1, then a_4 can be any value from 3 to 4. 

//the problem now is to match up each number from 1 to n to a segment that contains it. 

//when iterating i from 1 to n, we can choose the segment with the lowest right bound that contains i. 

//to do so, we can maintain a set s that sorts the segments in ascending right bounds. If we initially
//have all the segments in s, then it won't work, since it is possible that the left bound is greater than i. 

//to fix this, we can gradually add segments to s. On the ith iteration, add all segments with left bound equal
//to i to s. Then choose the minimum segment from s. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        vector<vector<int>> b(n, vector<int>(3));   //order, low, high
        for(int i = 0; i < n; i++){
            int ind = i + 1;
            b[i][0] = i;
            b[i][1] = ind / (a[i] + 1) + 1;
            b[i][2] = a[i] == 0? n : ind / a[i];
        }
        sort(b.begin(), b.end(), [](vector<int> &a, vector<int> &b){
            return a[1] == b[1]? a[2] < b[2] : a[1] < b[1];
        });
        set<pair<int, int>> s;
        int p = 0;
        vector<int> ans(n);
        for(int i = 0; i < n; i++){
            int next = i + 1;
            while(p != n && b[p][1] <= next){
                s.insert({b[p][2], b[p][0]});
                p++;
            }
            ans[s.begin() -> second] = next;
            s.erase(s.begin());
        }
        for(int i : ans){
            cout << i << " ";
        }
        cout << "\n";
    }
    
    return 0;
}

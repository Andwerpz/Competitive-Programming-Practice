#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1678D

//since the number of good rows and columns are independent, we can calculate them seperately and 
//add them together to get the final answer. 

//to calculate the number of columns, notice that as the students move around, they always follow a cycle. 
//we can use a boolean array of size m to keep track of which portion of the cycle is already occupied. 
//if we try to add a new student into an unoccupied section of the cycle, then we increment our ans. 

//for rows, we can imagine iterating a range of size m across s. If there exists a 1 in our range, then 
//that row is good. Notice that like the columns, there is a cycle of length m. When we have iterated the range
//the m-th time, the row above starts. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m;
        cin >> n >> m;
        string s;
        cin >> s;
        vector<int> ans(n * m);
        vector<int> col(m);
        int cnt = 0;
        for(int i = 0; i < s.length(); i++){
            if(s[i] == '1' && col[i % m] == 0){
                col[i % m] = 1;
                cnt ++;
            }
            ans[i] += cnt;
        }
        vector<int> r(m);
        cnt = 0;
        for(int i = 0; i < s.length(); i++){
            if(s[i] == '1'){
                cnt ++;
            }
            if(i - m >= 0 && s[i - m] == '1'){
                cnt --;
            }
            r[i % m] += cnt != 0? 1 : 0;
            ans[i] += r[i % m];
        }
        for(int i : ans){
            cout << i << " ";
        }
        cout << endl;
    }
    
    return 0;
}

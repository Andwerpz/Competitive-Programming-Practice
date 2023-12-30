#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1898E

//i claim that any transformation you can do with the second operation, you can also do if the second operation was
//restricted to substrings of length 2. 
//this is because by swapping two adjacent elements, you can already sort a subarray, which is effectively just the
//original operation. 

//using this modified operation, we will try to greedily build 'b' from left to right. Letters can travel
//to the left as long as they are less than the letter to their left. So if the ith letter of b is b[i], then
//we want to greedily pick the earliest letter in a that's equal to it, and that is also able to travel to the proper
//location. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        vector<vector<int>> letter_loc(26, vector<int>(0));
        vector<int> letter_ptr(26, 0);
        vector<int> letter_maxind(26, -1);
        int n, m;
        cin >> n >> m;
        string a, b;
        cin >> a >> b;
        for(int i = 0; i < n; i++){
            letter_loc[a[i] - 'a'].push_back(i);
        }
        bool is_valid = true;
        for(int i = 0; i < m; i++){
            int ind = b[i] - 'a';
            int geq_ind = -1;
            for(int j = b[i] - 'a' + 1; j < 26; j++){
                geq_ind = max(geq_ind, letter_maxind[j]);
            }
            //cout << "GEQ_IND : " << geq_ind << "\n";
            while(letter_ptr[ind] != letter_loc[ind].size() && letter_loc[ind][letter_ptr[ind]] < geq_ind) {
                letter_ptr[ind] ++;
            }
            if(letter_ptr[ind] == letter_loc[ind].size()) {
                is_valid = false;
                break;
            }
            //cout << "USING LETTER " << b[i] << " INDEX " << letter_loc[ind][letter_ptr[ind]] << "\n";
            letter_maxind[ind] = letter_loc[ind][letter_ptr[ind]];
            letter_ptr[ind] ++;
        }
        cout << (is_valid? "YES\n" : "NO\n");
    }
    
    return 0;
}

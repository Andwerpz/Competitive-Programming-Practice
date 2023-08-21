#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1858D

//if for each target maximum length of subarray of '1's, we compute the maximum subarray of '0's we can construct, 
//we can easily query the answer to any 'a' in O(n) time, by just going through all the possible lengths of maximum '1' subarrays. 

//to find the maximum subarray length of '0' given a length of '1', we can try to solve for every possible '1' subarray of that length. 
//we just need to know the maximum possible length of a '0' subarray on each prefix and suffix of the array, for each of j moves where 0 <= j <= k. 

//this third step can be computed in O(n^2) time. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        //maximum length of '0' subarray in the ith prefix, using exactly j moves. 
        vector<vector<int>> pfx(n + 1, vector<int>(k + 1, 0));
        vector<vector<int>> sfx(n + 1, vector<int>(k + 1, 0));
        for(int i = 0; i <= k; i++){
            int nr_one = 0;
            int l = 0;
            for(int j = 1; j <= n; j++){
                if(s[j - 1] == '1'){
                    nr_one ++;
                }
                while(nr_one > i) {
                    if(s[l] == '1'){
                        nr_one --;
                    }
                    l ++;
                }
                pfx[j][i] = max(j - l, pfx[j - 1][i]);
            }
        }
        for(int i = 0; i <= k; i++){
            int nr_one = 0;
            int r = n;
            for(int j = n - 1; j >= 0; j--){
                if(s[j] == '1'){
                    nr_one ++;
                }
                while(nr_one > i){
                    if(s[r - 1] == '1'){
                        nr_one --;
                    }
                    r --;
                }
                sfx[j][i] = max(r - j, sfx[j + 1][i]);
            }
        }
        vector<int> lng_zero(n + 1, -1);    //for each length of '1' subarray, what is the maximum length of '0' subarray that can be formed?
        for(int i = 0; i <= n; i++){
            int nr_zero = 0;
            int l = 0;
            for(int j = 0; j < i; j++){
                if(s[j] == '0'){
                    nr_zero ++;
                }
            }
            for(int j = i; j <= n; j++){
                int rem_moves = k - nr_zero;
                if(rem_moves >= 0){
                    lng_zero[i] = max(lng_zero[i], max(pfx[l][rem_moves], sfx[j][rem_moves]));
                }
                if(j != n && s[j] == '0'){
                    nr_zero ++;
                }
                if(s[l] == '0'){
                    nr_zero --;
                }
                l ++;
            }
        }
        for(int i = 1; i <= n; i++){
            int ans = 0;
            for(int j = 0; j <= n; j++){
                if(lng_zero[j] == -1){
                    continue;
                }
                ans = max(ans, j + lng_zero[j] * i);
            }
            cout << ans << " ";
        }
        cout << "\n";
    }
    
    return 0;
}

#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1721D

//the idea is to try to calculate the answer bit by bit. You can test given 'a' and 'b' whether or not a 
//it is possible that a certain bit is present in the final answer by counting the amount of times it
//shows up in 'a' and 'b'. If the amount of times it shows up is equal to |a|, then it is possible to 
//rearrange 'b' to make it appear in f(a, b). 

//Notice that larger bits will have more value than all of the smaller bits combined, so the solution is
//to greedily add the largest bits to the answer. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<vector<int>> a(1, vector<int>(n));
        vector<vector<int>> b(1, vector<int>(n));
        for(int i = 0; i < n; i++){
            cin >> a[0][i];
        }
        for(int i = 0; i < n; i++){
            cin >> b[0][i];
        }
        int ans = 0;
        int pow = 1 << 30;
        while(pow != 0){
            bool isValid = true;
            for(int i = 0; i < a.size(); i++){
                int cnt = 0;
                for(int j = 0; j < a[i].size(); j++){
                    cnt += ((a[i][j] & pow) != 0? 1 : 0);
                    cnt += ((b[i][j] & pow) != 0? 1 : 0);
                }
                if(cnt != a[i].size()){
                    isValid = false;
                }
            }
            if(isValid){
                ans += pow;
                vector<vector<int>> na(0);
                vector<vector<int>> nb(0);
                for(int i = 0; i < a.size(); i++){
                    vector<int> ha(0);
                    vector<int> la(0);
                    vector<int> hb(0);
                    vector<int> lb(0);
                    for(int j = 0; j < a[i].size(); j++){
                        if((a[i][j] & pow) != 0){
                            ha.push_back(a[i][j]);
                        }
                        else {
                            la.push_back(a[i][j]);
                        }
                        if((b[i][j] & pow) != 0){
                            hb.push_back(b[i][j]);
                        }
                        else{
                            lb.push_back(b[i][j]);
                        }
                    }
                    if(ha.size() != 0){
                        na.push_back(ha);
                        nb.push_back(lb);
                    }
                    if(la.size() != 0){
                        na.push_back(la);
                        nb.push_back(hb);
                    }
                }
                a = na;
                b = nb;
            }
            pow /= 2;
        }
        cout << ans << "\n";
    }
    
    return 0;
}

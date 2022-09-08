#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1728C

//Notice that since a[i] is limited to 10^9, when you apply the logarithm operation, you always get
//a number from 1 - 9. And when you apply the logarithm to 1 - 9, you always get 1. 

//So the upper bound is to just apply the logarithm operation to every number until it's equal to 1. 

//notice that the logarithm operation can only decrease the value of an element. So if we can somehow start
//pairing off numbers from a and b starting from the greatest values, and apply the logarithm when they don't have
//a pair, each value will only be looked at at most 2 times, resulting in linear runtime. 

//My implementation considers numbers >= 10 seperately, and then deals will all remaining numbers, which are
//guaranteed to be less than 10. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        vector<int> b(n);
        int ans = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        for(int i = 0; i < n; i++){
            cin >> b[i];
        }
        //squash down big numbers
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        int pa = 0;
        int pb = 0;
        while(pa != n && pb != n){
            if(a[pa] == b[pb]){  //found matching big numbers
                if(a[pa] >= 10){
                    a[pa] = -1;
                    b[pb] = -1;
                }
                pa ++;
                pb ++;
            }
            else if(a[pa] > b[pb]){
                pb ++;
            }
            else if(a[pa] < b[pb]){
                pa ++;
            }
        }
        vector<int> ca(10, 0);
        vector<int> cb(10, 0);
        for(int i = 0; i < n; i++){
            if(a[i] == -1){
                continue;
            }
            if(a[i] >= 10){
                ca[to_string(a[i]).size()] ++;
                ans ++;
            }
            else{
                ca[a[i]] ++;
            }
        }
        for(int i = 0; i < n; i++){
            if(b[i] == -1){
                continue;
            }
            if(b[i] >= 10){
                cb[to_string(b[i]).size()] ++;
                ans ++;
            }
            else{
                cb[b[i]] ++;
            }
        }
        for(int i = 2; i < 10; i++){
            ans += abs(ca[i] - cb[i]);
        }
        cout << ans << "\n";
    }
    
    return 0;
}

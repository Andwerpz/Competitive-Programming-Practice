#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces 1771A

//since the difference between the two picked numbers has to be the maximum possible difference, 
//that means that the least and greatest values in the array must be picked. 

//to figure out how many pairs, we can just multiply the amount of min elements with the amount of 
//max elements, and then multiply that by 2, since one could pick low or high. 

//there is also a case where the min and max values are the same, in that case, we know that all the 
//values in the array are the same. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        int min = (int) 1e9;
        int max = -1;
        int minCnt = 0;
        int maxCnt = 0;
        vector<int> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            if(min > a[i]) {
                minCnt = 1;
                min = a[i];
            }
            else if(min == a[i]){
                minCnt ++;
            }
            if(max < a[i]) {
                maxCnt = 1;
                max = a[i];
            }
            else if(max == a[i]){
                maxCnt ++;
            }
        }
        ll ans = 0;
        if(min == max){
            ans = (ll) n * (ll) (n - 1) / 2;
            ans *= 2;
        }
        else {
            ans = (ll) minCnt * (ll) maxCnt * 2;
        }
        cout << ans << "\n";
    }
    
    return 0;
}

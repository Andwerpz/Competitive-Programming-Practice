#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces 1744F

//I know what the solution is, but i have no idea how this particular solution is working. 
//is it possible for a + b < 0?

//for each possible value of mex(a[l:r]), count how many segments there are where mex(a[l:r]) > med(a[l:r]).

//if the mex of a segment is equal to i, then the maximum size of the segment is 2 * i given that mex(a[l:r]) > med(a[l:r]) 
//is satisfied. 

//now we begin looking at mex values in ascending order starting from 1. 
//note that the only way to get mex = 1 is when i = j = a[i] = 0. 

//the starting segment for each mex value i is the segment that has mex value of i with minimal size; r - l + 1. 
//we can 'expand' the starting segment to create other segments of larger size with the same mex value, but any segment 
//that has equal mex to i must include the starting segment belonging to the ith mex value. 

//note that the starting segment of the i + 1th mex value includes the starting segment of the ith mex value. 

//if for each possible mex value, we take the sum of segments where the condition is satisfied, and sum them, then
//we will have computed the answer. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        vector<int> p(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
            p[a[i]] = i;
        }
        int l = p[0];
        int r = p[0];
        ll ans = 0;
        for(int i = 0; i < n; i++){
            if(p[i] > l && p[i] < r) {  //next number is already inside the current range. 
                //cout << "SKIP : " << i << "\n";
                continue;
            }
            l = min(l, p[i]);
            r = max(r, p[i]);
            while(i + 1 < n && p[i + 1] > l && p[i + 1] < r) {
                i ++;
                //cout << "SKIP : " << i << "\n";
            }
            int segSize = (i + 1) * 2 - (r - l + 1);    //since mex is i + 1, you can have maximum 2i segment size before median is greater than i + 1. 
            int a = l;
            int b = n - (r + 1);
            if(i != n - 1){
                if(p[i + 1] < l){
                    a = l - p[i + 1] - 1;
                }
                else if(p[i + 1] > r) {
                    b = p[i + 1] - r - 1;
                }
            }
            //cout << l << " " << r << " " << a << " " << b << " " << i + 1 << "\n";
            ll iter = min(a + b, segSize);
            if(iter < 0){
                continue;
            }
            ans += (iter + 1) * 1;
            ans += iter * (iter + 1) / 2;
            if(iter > a){
                ll temp = iter - a;
                ans -= temp * (temp + 1) / 2;
            }
            ans += iter * (iter + 1) / 2;
            if(iter > b) {
                ll temp = iter - b;
                ans -= temp * (temp + 1) / 2;
            }
            ans -= iter * (iter + 1) / 2;
            // for(int j = 0; j <= min(a + b, segSize); j++){
            //     cout << "ADD: " << min(j, a) + min(j, b) + 1 - j << "\n";
            //     ans += min(j, a) + min(j, b) + 1 - j;
            // }
        }
        cout << ans << "\n";
    }
    
    return 0;
}

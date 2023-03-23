#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 07 B

//to check whether a certain maximum length x is valid, you can use a greedy approach. 
//lets say that currently you are on car i; which means that cars 1 to i - 1 have already been taken. 

//if the next car which you need to take is within the x cars that you can take, then always take x cars. 
//else, just take all the cars until the next car you need to take. 

bool isValid(vector<int>& a, int val, int l, int n) {
    int ptr = 0;
    int cur = 1;
    for(int i = 0; i < l; i++){
        int cnt = 0;
        while(ptr < a.size() && a[ptr] - cur < val) {
            cnt ++;
            ptr ++;
        }
        if(cnt == 0){
            if(ptr == a.size()) {
                cur = 1e9 + 1;
            }
            else {
                cur = a[ptr];
            }
        }
        else{
            cur += val;
        }
    }
    return cur > n;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, w, l;
        cin >> n >> w >> l;
        vector<int> a(w, 0);
        for(int i = 0; i < w; i++){
            cin >> a[i];
        }
        int ans = 1e9;
        int low = 0;
        int high = 1e9;
        int mid = low + (high - low) / 2;
        while(low <= high) {
            if(isValid(a, mid, l, n)) {
                high = mid - 1;
                ans = min(ans, mid);
            }
            else {
                low = mid + 1;
            }
            mid = low + (high - low) / 2;
        }
        cout << ans << "\n";
    }
    
    return 0;
}

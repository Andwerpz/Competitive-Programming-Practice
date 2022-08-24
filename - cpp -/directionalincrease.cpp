#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1694C

//to check if a given sequence is valid, you can calculate the sum for every prefix. 

//if the sum is ever negative, or there are two positive numbers seperated by zeroes, or it 
//doesn't end on a zero, then it is invalid. 

//for a given i, r[i] represents the number of right moves taken when the pointer is at i, and l[i]
//is the number of left moves. 

//if we take the prefix of a at i, or pfx(a, i), then what we are really doing is pfx(r, i) - pfx(l, i). 

//obviously, if this value is negative, then the sequence is invalid, since we can't ever have more left
//moves than right moves in a given segment. 

//it should be easy to show the other properties as well. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        bool isValid = true;
        bool term = false;
        vector<ll> a(n);
        ll sum = 0;
        for(int i = 0; i < n; i++){
            cin >> a[i];
            sum += a[i];
            if(sum < 0){
                isValid = false;
            }
            if(sum == 0){
                term = true;
            }
            if(term && sum != 0){
                isValid = false;
            }
        }
        if(sum != 0){
            isValid = false;
        }
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}

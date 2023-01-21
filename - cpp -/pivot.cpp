#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 01 F

//in order for a number to be a valid pivot, it must be greater than all the numbers to it's
//left, and less than all the numbers to it's right. 

//to check each number in constant time, we can precompute prefix max and suffix min arrays. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<bool> v(n);
    int pfxMax = a[0];
    for(int i = 0; i < n; i++){
        pfxMax = max(pfxMax, a[i]);
        if(a[i] >= pfxMax){
            v[i] = true;
        }
    }
    int sfxMin = a[n - 1];
    int ans = 0;
    for(int i = n - 1; i >= 0; i--) {
        sfxMin = min(sfxMin, a[i]);
        if(v[i] && a[i] <= sfxMin) {
            ans ++;
        }
    }
    cout << ans << "\n";
    
    return 0;
}

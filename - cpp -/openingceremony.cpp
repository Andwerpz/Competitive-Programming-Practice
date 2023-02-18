#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 05 B

//note that if you shoot out all of the xth floors of all the buildings, all floors greater than x will fall down. 
//so if you use that firing mode, it is always optimal to target the first floor. 

//note that is is always optimal to use the horizontal firing mode before using the vertical one, because the vertical firing
//mode just lessens the effectiveness of the horizontal one. 

//a solution has to have the form of some number of horizontal shots, followed by some number of vertical shots. Given u horizontal shots, 
//we can determine exactly how many vertical shots it takes; it's simply just the number of remaining buildings

//to determine the amount of remaining buildings, we just see that any building less than u floors high is destroyed with the u horizontal shots. 
//so we can just sort the array in ascending order. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    int ans = n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    for(int i = 0; i < n; i++){
        int curAns = n - i - 1;
        curAns += a[i];
        ans = min(ans, curAns);
    }
    cout << ans << "\n";
    
    return 0;
}

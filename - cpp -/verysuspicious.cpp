#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1670D

//notice that two lines that are not parallel will always intersect. 

//we can position the lines such that an intersection will always form two triangles. So, now, given some number of 
//lines, we just need to count the number of intersections. 

//we can divide the lines into different types depending on their angle to the horizontal. You can see that the only lines relevant to 
//producing equilateral triangles are the lines that are 0, 60, and 120 deg to the horizontal. 

//from here, we can easily create a formula calculating the number of intersections given the amounts of each type of line. 
//we can notice that in order to minimize the amount of lines, we should keep the amounts between the types equal. 

//since the number of triangles requested can be pretty high, we should use binary search. 

ll calc(ll a, ll b, ll c){
    ll ans = a * (b + c) + b * (a + c) + c * (a + b);
    return ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        ll n;
        cin >> n;
        ll low = 1;
        ll high = 1e6;
        ll mid = low + (high - low);
        ll ptr = 1e6;
        while(low <= high) {
            if(calc(mid, mid, mid) >= n) {
                ptr = min(ptr, mid);
                high = mid - 1;
            }
            else {
                low = mid + 1;
            }
            mid = low + (high - low) / 2;
        }
        while(calc(ptr, ptr, ptr) < n) {
            ptr ++;
        }
        if(calc(ptr, ptr, ptr - 1) < n){
            cout << ptr * 3 << "\n";
            continue;
        }
        if(calc(ptr, ptr - 1, ptr - 1) < n){
            cout << ptr * 3 - 1 << "\n";
            continue;
        }
        cout << ptr * 3 - 2 << "\n";
    }
    
    return 0;
}

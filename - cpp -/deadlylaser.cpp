#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//ACPC 2022 Week 1 D

//notice that if there exists a path from start to end, then the minimum path length is always n + m - 2. 

//now, we just have to check if there exists a path from start to end. To do this, we can just do 4 checks, 
//each check determines if the laser touches a given side. There is a path if the laser doesn't 
//simultaneously touch the top and right or left and bottom sides. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, m, r, c, d;
        cin >> n >> m >> r >> c >> d;
        r --;
        c --;
        bool top = r <= d;
        bool bottom = n - r - 1 <= d;
        bool left = c <= d;
        bool right = m - c - 1 <= d;
        if((!top && !right) || (!left && !bottom)){
            cout << n + m - 2 << "\n";
        }
        else {
            cout << "-1\n";
        }
    }
    
    return 0;
}

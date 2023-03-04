#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 07 A

//if two ants collide, it's like they didn't, because one is still going to the left, and one is still going to the right. 

//so essentially, you can just say that ants don't collide. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n, l;
        cin >> l >> n;
        int minTime = -1;
        int maxTime = -1;
        for(int i = 0; i < n; i++){
            int a;
            cin >> a;
            minTime = max(minTime, min(a, l - a));
            maxTime = max(maxTime, max(a, l - a));
        }
        cout << minTime << " " << maxTime << "\n";
    }
    
    return 0;
}

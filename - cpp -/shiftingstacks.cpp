
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1486A

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> nums(n);
        for(int i = 0; i < n; i++){
            cin >> nums[i];
        }
        ll extra = 0;
        bool isValid = true;
        for(int i = 0; i < n; i++){
            int quota = i;
            int next = nums[i];
            int diff = next - quota;
            extra += (ll)diff;
            if(extra < 0){
                isValid = false;
            }
        }
        cout << (isValid? "YES\n" : "NO\n");
    }

    return 0;
}





#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces - 1588A

//all you have to do is sort arrays a and b, and check if you can make each value of a equal to b by adding 1 to it.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        vector<int> a(n);
        vector<int> b(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        for(int i = 0; i < n; i++){
            cin >> b[i];
        }
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        bool isValid = true;
        for(int i = 0; i < n; i++){
            if(b[i] > a[i] + 1 || b[i] < a[i]){
                isValid = false;
                break;
            }
        }
        cout << (isValid? "YES\n" : "NO\n");
    }

    return 0;
}

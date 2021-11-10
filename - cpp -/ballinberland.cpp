
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1475C

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int a, b, k;
        cin >> a >> b >> k;
        vector<pair<int, int>> couples(k);
        vector<int> boys(a);
        vector<int> girls(b);
        for(int i = 0; i < k; i++){
            int next;
            cin >> next;
            next --;
            couples[i].first = next;
        }
        for(int i = 0; i < k; i++){
            int next;
            cin >> next;
            next --;
            couples[i].second = next;
        }
        ll ans = 0;
        for(int i = 0; i < k; i++){
            int boy = couples[i].first;
            int girl = couples[i].second;
            ans += (ll) (i - boys[boy] - girls[girl]);
            boys[boy] ++;
            girls[girl] ++;
        }
        cout << ans << endl;
    }

    return 0;
}




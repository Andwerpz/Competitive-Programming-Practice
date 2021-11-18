
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//Codeforces - 1604A

//simple greedy problem. Just always put numbers at the back, pushing back existing numbers. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        int max = 0;
        for(int i = 0; i < n; i++){
            int next;
            cin >> next;
            max = std::max(max, next - (i + 1));
        }
        cout << max << endl;
    }

    return 0;
}




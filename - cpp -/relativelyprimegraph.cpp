
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1009D

//a straight up O(n^2) algorithm will work. 

//we know this because of eulers totient function. given n nodes, we can find the maximum amount of edges by computing t(1) + t(2) + ... + t(n). 
//after n gets to 600, the sum exceeds the maximum amount of edges, so that means that we only have to do 600^2 operations maximum.

//we also have to check that m >= n - 1 to make a fully connected graph.

using namespace std;

int gcd(int a, int b);

int gcd(int a, int b){
    if(b == 0){
        return a;
    }
    return gcd(b, a % b);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    bool isValid = true;
    vector<pair<int, int>> ans;
    if(m < n - 1){
        isValid = false;
    }
    int counter = 0;
    for(int i = 1; i <= n; i++){
        for(int j = i + 1; j <= n; j++){
            if(gcd(i, j) == 1){
                ans.push_back({i, j});
                counter ++;
                if(counter == m){
                    goto outer;
                }
            }
        }
    }
    outer:;
    if(counter != m){
        isValid = false;
    }
    if(isValid){
        cout << "Possible\n";
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i].first << " " << ans[i].second << endl;
        }
    }
    else{
        cout << "Impossible\n";
    }

    return 0;
}




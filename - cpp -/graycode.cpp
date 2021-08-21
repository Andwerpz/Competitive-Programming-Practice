
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long ll;

using namespace std;

//CSES - Gray Code

int main() {

    int n;
    cin >> n;
    vector<string> ans {"0", "1"};
    for(int i = 1; i < n; i++){
        int len = ans.size();
        for(int j = len - 1; j >= 0; j--){
            ans.push_back(ans[j]);   
        } 
        for(int j = 0; j < len; j++){
            ans[j] += "0";
        }
        for(int j = len; j < ans.size(); j++){
            ans[j] += "1";
        }
    }
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << "\n";
    }
    
    return 0;
}




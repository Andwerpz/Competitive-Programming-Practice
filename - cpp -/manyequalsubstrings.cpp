
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1029A

//sometimes being smart is dumb - Sun Tzu, Art of War

//just brute force the whole thing

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    cin >> n >> k;
    string t;
    cin >> t;
    for(int minLoop = 1; minLoop <= n; minLoop ++) {
        string loop = "";
        for(int i = n - minLoop; i < n; i++){
            loop += t[i];
        }
        string ans = "";
        for(int i = 0; i < k; i++){
            if(i == 0){
                ans += t;
            }
            else{
                ans += loop;
            }
        }
        int numOccurrences = 0;
        int pointer = 0;
        for(int i = 0; i < ans.length(); i++){
            for(int j = 0; j < n; j++){
                if(ans[i + j] != t[j]){
                    break;
                }
                if(j == n - 1){
                    numOccurrences ++;
                }
            }
        }
        if(numOccurrences == k){
            cout << ans << endl;
            break;
        }
    }
    

    return 0;
}




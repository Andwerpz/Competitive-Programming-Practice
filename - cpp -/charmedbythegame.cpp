
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1561B

//just do a brute force search across all situations. The input is small enough for you to do so.

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int a, b;
        cin >> a >> b;
        int amtPlayed = a + b;
        int aServe = amtPlayed / 2;
        int bServe = amtPlayed - aServe;
        int aWin = min(a, aServe);  //amount of times when a serves, a wins
        int bWin = max(0, a - aServe);  //amount of times when b serves, a wins
        set<int> k;
        while(true){
            int next = bWin + aServe - aWin;
            k.insert(next);
            if(aWin == 0){
                break;
            }
            bWin ++;
            aWin --;
            if(bWin > bServe || aWin < 0){
                break;
            }
        }
        bServe = amtPlayed / 2;
        aServe = amtPlayed - bServe;
        aWin = min(a, aServe);  //amount of times when a serves, a wins
        bWin = max(0, a - aServe);  //amount of times when b serves, a wins
        while(true){
            int next = bWin + aServe - aWin;
            k.insert(next);
            if(aWin == 0){
                break;
            }
            bWin ++;
            aWin --;
            if(bWin > bServe || aWin < 0){
                break;
            }
        }
        vector<int> ans(k.size());
        int pointer = 0;
        for(auto i : k){
            ans[pointer] = i;
            pointer ++;
        }
        sort(ans.begin(), ans.end());
        cout << ans.size() << endl;
        for(int i = 0; i < ans.size(); i++){
            cout << ans[i] << " ";
        }
        cout << endl;
    }

    return 0;
}




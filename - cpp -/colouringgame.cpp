#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1704F

//First of all, any pair of neighboring cells that are different colors, such as 'RB' and 'BR' will get removed 
//first. This is because each person wants to minimize the amount of cells the other person has to play on. 

//note that if the number of red cells is initially greater than the number of blue cells, or vice versa, that person 
//is guaranteed to win. This is because when removing 'RB' or 'BR' pairs, the relative difference of red and blue
//cells don't change, and after all those pairs are removed, each person will only remove one of their own colored
//cells per move. 

//Now, we only have to deal with the case where the number of red cells is equal to the number of blue cells. 
//in this case, the last person who removes a 'RB' or 'BR' pair will win. Now, this situation can be analyzed using
//grundy numbers. For each consecutive substring of alternating red and blue cells, we can assign a grundy
//number to it based off of how many possible pairs we can remove from it

//for example, 'RBRBR' has 4 possible moves, so it's grundy number will be g[4]. 
//naturally, g[0] = 0, and g[1] = 1. g[2] = 1 as well, since removing any pair will cause the other pair to disappear.
//from here, we can just brute force compute grundy numbers, and observe that it has a cycle length of 34 after the
//first few elements. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    vector<int> grundy(1000);
    grundy[0] = 0;
    grundy[1] = 1;
    grundy[2] = 1;
    for(int i = 3; i < grundy.size(); i++){
        vector<int> next(0);
        //take first one
        next.push_back(grundy[i - 2]);
        //all in the middle
        for(int j = 0; i - j - 3 >= 0; j++) {
            next.push_back(grundy[j] ^ grundy[i - j - 3]);
        }
        sort(next.begin(), next.end());
        int mex = 0;
        for(int i = 0; i < next.size(); i++){
            if(next[i] == mex){
                mex ++;
            }
        }
        grundy[i] = mex;
    }
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        int r_cnt = 0;
        for(int i = 0; i < s.size(); i++){
            r_cnt += s[i] == 'R';
        }
        if(r_cnt != s.size() - r_cnt) {
            if(r_cnt > s.size() - r_cnt) {
                cout << "Alice\n";
            }
            else {
                cout << "Bob\n";
            }
            continue;
        }
        int g_val = 0;
        for(int i = 0; i < n - 1;){
            int r = i;
            while(r != s.size() - 1 && s[r] != s[r + 1]) {
                r ++;
            }
            int amt = r - i;
            if(amt >= grundy.size()) {
                int diff = amt - grundy.size();
                diff = (diff - (diff % 34)) + 34;
                amt -= diff;
            }
            i = r + 1;
            g_val ^= grundy[amt];
        }
        cout << (g_val == 0? "Bob" : "Alice") << "\n";
    }
    
    return 0;
}
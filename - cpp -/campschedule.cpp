#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1137B

//a naive solution might be to just greedily create occurrences of t at the beginning of s, and once you run out 
//of stuff, just insert the remaning characters at the end. 

//the problem is that this is not always optimal. Consider t = '101' Instead of creating s like '101101...', it's far
//more efficient to create it like '101010...'.

//so, our goal now is to find the minimum prefix of t that can be tiled to describe the remainder of t. 

//the way i came up with checking if a certain prefix can describe t is with a 2 phase check. The first phase runs in 
//around O(log(n)) time on average, and the second phase runs in O(n) time. The testcases work out so that generally, 
//not many prefixes can pass the first phase. 

//in the first phase, I just make sure that the '0' and '1' character counts match up in each of the tiles. I can use
//prefix sums to check each tile in O(1) time. the second phase is just a linear scan. 

//The intended way to solve this problem is by using string hashing, but im dumb D:

//after you find the minimum prefix, just create that greedily.

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s, t;
    cin >> s >> t;
    //find shortest prefix of t that can fully describe t. 
    {   
        vector<int> zpfx(t.size() + 1, 0);
        vector<int> opfx(t.size() + 1, 0);
        for(int i = 1; i <= t.size(); i++){
            zpfx[i] = (t[i - 1] == '0') + zpfx[i - 1];
            opfx[i] = (t[i - 1] == '1') + opfx[i - 1];
        }
        for(int i = 1; i <= t.size(); i++){
            //prechecks 
            bool pre_valid = true;
            {
                int zcnt = zpfx[i];
                int ocnt = opfx[i];
                for(int j = i * 2; j < t.size(); j += i){
                    int l = j - i;
                    int r = j;
                    if(zpfx[r] - zpfx[l] != zcnt || opfx[r] - opfx[l] != ocnt) {
                        pre_valid = false;
                        break;
                    }
                }
            }
            if(t.size() % i != 0){
                //last section
                int len = t.size() % i;
                int l = (t.size() / i) * i;
                if(zpfx[len] != zpfx[t.size()] - zpfx[l] || opfx[len] != opfx[t.size()] - opfx[l]) {
                    pre_valid = false;
                }   
            }
            if(!pre_valid) {
                continue;
            }
            //ok, real check now
            bool is_valid = true;
            for(int j = 0; j < t.size(); j++){
                if(t[j] != t[j % i]) {
                    is_valid = false;
                    break;
                }
            }
            if(is_valid) {
                t = t.substr(0, i);
                break;
            }
        }   
    }
    //move stuff in s to create as many copies of the t section as possible
    int zcnt = 0;
    int ocnt = 0;
    for(int i = 0; i < s.size(); i++){
        zcnt += s[i] == '0';
        ocnt += s[i] == '1';
    }
    for(int i = 0; i < s.size(); i++){
        if(zcnt != 0 && ocnt != 0){
            if(t[i % t.size()] == '0'){
                s[i] = '0';
                zcnt --;
            }
            else {
                s[i] = '1';
                ocnt --;
            }
        }
        else {
            if(zcnt != 0){
                s[i] = '0';
                zcnt --;
            }
            else {
                s[i] = '1';
                ocnt --;
            }
        }
    }
    cout << s << "\n";
    
    return 0;
}
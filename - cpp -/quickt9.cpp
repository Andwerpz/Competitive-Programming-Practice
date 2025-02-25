#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl; 
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Topcoder - 11228

//we can probably do a dp solution. dp[i] = minimum number of keypresses required to type the first i characters. 
//transitions can be something like computing the cost to type the characters in range [l, r) and transitioning
//from dp[l] -> dp[r]

//since the bounds are really small, we can probably precompute the transition costs for every possible transition. 
//first, for each valid D, we can determine the lexicographic ordering of each string within the same D. So we can 
//determine the cost of writing some string directly.

//Then, to account for '*' moves, we'll also take into account one button press to decrease any writable string by
//one character. 

//This should run in O(n^3 + m^3) where n is the dictionary size and m is the size of the string. 

/*
2         a,b,c
3         d,e,f
4         g,h,i
5         j,k,l
6         m,n,o
7        p,q,r,s
8         t,u,v
9        w,x,y,z
*/
vector<char> dmp = {'2', '2', '2', '3', '3', '3', '4', '4', '4', '5', '5', '5', '6', '6', '6', '7', '7', '7', '7', '8', '8', '8', '9', '9', '9', '9'};
class QuickT9 {
public:
    int minimumPressings(vector<string> dict, string s) {
        {
            vector<string> tmp;
            for(string& x : dict) {
                int r = 0;
                while(r < x.size()) {
                    int l = r;
                    while(r != x.size() && x[r] != ' ') r ++;
                    tmp.push_back(x.substr(l, r - l));
                    r ++;
                }
            }
            dict = tmp;
        }
        int n = s.size();
        vi dp(n + 1, 1e9);
        dp[0] = 0;
        map<string, set<string>> mp; //map D to all possible U within dict
        for(string& x : dict) {
            string d = "";
            for(int i = 0; i < x.size(); i++){
                d.push_back(dmp[x[i] - 'a']);
                mp[d].insert(x.substr(0, i + 1));
            }
        }
        map<string, int> ordmp; //given some string, how many button presses does it take to get there?
        for(auto i = mp.begin(); i != mp.end(); i++){
            int ptr = 0;
            for(auto j = i->second.begin(); j != i->second.end(); j++){
                int base = j->size() + (ptr ++);
                for(int k = j->size(); k >= 1; k--){
                    string cur = j->substr(0, k);
                    if(!ordmp.count(cur)) ordmp[cur] = 1e9;
                    ordmp[cur] = min(ordmp[cur], base + max(0, (int) j->size() - k - 1));
                }
            }
        }
        for(int i = 0; i < n; i++) {
            string cur = "", d = "";
            for(int j = i + 1; j <= n; j++){
                cur.push_back(s[j - 1]);
                if(ordmp.count(cur)) dp[j] = min(dp[j], (int) (dp[i] + ordmp[cur] + 1));
                else break;
            }
        }
        return dp[n] == 1e9? -1 : dp[n];
    }
};

int main() {
    int n0; cin >> n0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<string> arg0(n0);
    for (int i=0;i<n0;++i) { getline(cin, arg0[i]); }
    string arg1;
    getline(cin, arg1);
    auto c = QuickT9();
    int ret = c.minimumPressings(arg0, arg1);
    cout << ret;
}
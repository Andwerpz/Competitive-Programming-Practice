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

//Topcoder - 11033

//just try everything lmao

class TheBoardingDivTwo {
public:
    int find(vector<int> pattern, int boardingTime) {
        int n = pattern.size();
        for(int i = 0; i < n; i++){
            if(pattern[i] != -1) pattern[i] --;
        }
        int ans = 0;
        vi p(n);
        for(int i = 0; i < n; i++) p[i] = i;
        while(true) {
            bool valid = true;
            for(int i = 0; i < n; i++){
                if(pattern[i] != -1 && pattern[i] != p[i]) valid = false;
            }
            if(valid) {
                //calc boarding time
                vi c(2 * n, -1), stime(2 * n, -1);
                for(int i = 0; i < n; i++) c[i] = p[i];
                int time = 0;
                while(true) {
                    bool done = true;
                    for(int i = c.size() - 1; i >= 1; i--){
                        if(c[i] == -1 && c[i - 1] == -1) continue;
                        done = false;
                        if(c[i] != -1) {    //see if we can take a seat
                            if(c[i] == i - n) c[i] = -1, stime[i] = time + 74;
                        }
                        else if(c[i - 1] != -1){    //see if person behind wants to move forwards
                            if(time >= stime[i] && c[i - 1] != (i - 1) - n) c[i] = c[i - 1], c[i - 1] = -1;
                        }
                    }
                    if(done) break;
                    time ++;
                }
                int ctime = -1;
                for(int i = 0; i < stime.size(); i++) ctime = max(ctime, stime[i]);
                ans += ctime <= boardingTime;
            }
            if(!next_permutation(p.begin(), p.end())) break;
        }
        return ans;
    }
};

int main() {
    int n0; cin >> n0;
    vector<int> arg0(n0);
    for (int i=0;i<n0;++i) { cin >> arg0[i]; }
    int arg1;
    cin >> arg1;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    auto c = TheBoardingDivTwo();
    int ret = c.find(arg0, arg1);
    cout << ret;
}
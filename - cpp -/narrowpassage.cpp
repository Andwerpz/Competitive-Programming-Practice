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

//Topcoder - 13184

//for each wolf, determine the final relative positioning it wants to be in. This will be the wolf 'permutation',
//p[i] = the relative position that wolf i wants to end up in. 

//the intuition here is that we can sort any prefix or suffix of the permutation at some cost. First, observe
//that we never want to sort the prefix or suffix twice in a row, as this can effectively be turned into one sort.

//So, after sorting one side, we always want to go to the other side. How many times do we need to do this? Observe
//that when we sort for the third time, the third sort must always be 'touching' the elements affected by the
//second sort, otherwise it's not going to do anything. 

//From here, I guess that if we iterate over all possible first and second sorts, then sort the remaining elements
//with the third sort, we can generate the optimal solution. 

class NarrowPassage {
public:
    ll solve(ll L, vector<ll> a, vector<ll> b) {
        int n = a.size();
        //find permutation from b -> a
        vector<array<ll, 3>> ord(n);  //{i, a[i], b[i]}
        for(int i = 0; i < n; i++){
            ord[i] = {-1, a[i], b[i]};
        }
        sort(ord.begin(), ord.end(), [](array<ll, 3>& a, array<ll, 3>& b) -> bool {
            return a[2] < b[2];
        });
        vl tgt(n);
        for(int i = 0; i < n; i++){
            ord[i][0] = i;
            tgt[i] = ord[i][2];
        }
        sort(ord.begin(), ord.end(), [](array<ll, 3>& a, array<ll, 3>& b) -> bool {
            return a[1] < b[1];
        });
        vi p(n);
        for(int i = 0; i < n; i++){
            p[i] = ord[i][0];
        }
        ll ans = 1e18;
        for(int i = 0; i <= n; i++){
            for(int k = 0; k <= n; k++){
                ll cans = 0;
                vector<pii> cpos(n);    //{target ind, cur pos}
                for(int j = 0; j < n; j++){
                    cpos[j] = {ord[j][0], ord[j][1]};
                }
                bool need_sort = false;
                for(int j = 0; j < i; j++){
                    if(cpos[j].first != j) need_sort = true;
                }
                if(need_sort){
                    for(int j = 0; j < i; j++){
                        cans += cpos[j].second;
                        cpos[j].second = 0;
                    }
                    sort(cpos.begin(), cpos.begin() + i);
                }
                need_sort = false;
                for(int j = n - 1; j >= k; j--){
                    if(cpos[j].first != j) need_sort = true;
                }
                if(need_sort) {
                    for(int j = n - 1; j >= k; j--){
                        cans += L - cpos[j].second;
                        cpos[j].second = L;
                    }
                    sort(cpos.begin() + k, cpos.end());
                }
                int sort_ind = 0;
                for(int j = 0; j < n; j++){
                    if(cpos[j].first != j) sort_ind = j + 1;
                }
                for(int j = 0; j < sort_ind; j++){
                    cans += cpos[j].second;
                    cpos[j].second = 0;
                }
                sort(cpos.begin(), cpos.begin() + sort_ind);
                for(int j = 0; j < n; j++){
                    cans += abs(tgt[j] - cpos[j].second);
                }
                ans = min(ans, cans);
            }
        }
        return ans;
    }

    int minDist(ll L, vector<ll> a, vector<ll> b) {
        ll ans = solve(L, a, b);
        for(int i = 0; i < a.size(); i++){
            a[i] = L - a[i], b[i] = L - b[i];
        }
        ans = min(ans, solve(L, a, b));
        return (int) ans;
    }
};

int main() {
    int arg0;
    cin >> arg0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int n1; cin >> n1;
    vector<ll> arg1(n1);
    for (int i=0;i<n1;++i) { cin >> arg1[i]; }
    int n2; cin >> n2;
    vector<ll> arg2(n2);
    for (int i=0;i<n2;++i) { cin >> arg2[i]; }
    auto c = NarrowPassage();
    int ret = c.minDist(arg0, arg1, arg2);
    cout << ret;
}
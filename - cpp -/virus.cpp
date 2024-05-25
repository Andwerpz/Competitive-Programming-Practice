#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//Codeforces - 1704C

//first, notice that we can completely disregard the circular aspect of the problem, and instead focus on the gaps
//between the infected houses. 

//for each second that passes, each segment will shrink by 2 houses, (or 1 house if the segment is just 1 house), 
//and our goal should be to stop this loss as soon as possible. 

//one idea is to preserve as many segments as possible by stopping the smaller segments first, then moving onto 
//the larger ones, but this fails to acknowledge the problem's goal, which is to minimize the number of infected
//houses, which is equivalent to maximizing the number of uninfected houses; the number of segments that 
//remain uninfected is irrelevant. 

//Instead, if we start by stopping the largest segments, the smaller segments will 'stop themselves' by getting
//fully infected, therefore stopping the spread of the infection more quickly (in a rather morbid way). 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n, m;
        cin >> n >> m;
        vector<int> a(m);
        for(int i = 0; i < m; i++){
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        vector<int> gaps(0);
        for(int i = 0; i < m; i++){
            int l = a[i];
            int r = a[(i + 1) % m];
            if(i == m - 1){
                r += n;
            }
            // cout << "G : " << l << " " << r << "\n";
            gaps.push_back(r - l - 1);
        }
        sort(gaps.begin(), gaps.end());
        reverse(gaps.begin(), gaps.end());
        int ans = 0;    //keep track of nr uninfected houses
        int t = 0;
        for(int i = 0; i < gaps.size(); i++){
            int g = gaps[i];
            // cout << "GAP : " << g << endl;
            if(t * 2 >= g){
                break;
            }
            g -= t * 2;
            if(g <= 2) {
                ans ++;
                t ++;
                continue;
            }
            ans += g - 1;
            t += 2;
        }
        ans = n - ans;
        cout << ans << "\n";
    }
    
    return 0;
}
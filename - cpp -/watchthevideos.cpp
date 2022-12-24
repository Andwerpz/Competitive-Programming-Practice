#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1765D

//lets say that you try to watch the videos in a certain order. If at any point, there are two adjacent videos
//with size that sums up to higher than m, then we add 1 to cnt. The total time taken is simply the sum of size
//for all videos plus cnt. 

//To minimize the answer, the only thing we can do is minimizing the occurrences of two adjacent videos adding up to
//greater than m. We can do so greedily; go in ascending order, and try to pair the lowest size video to the highest
//size video where adding them is <= m. The number of videos that don't have a pair is cnt. 

//note that cnt should start at 1, since you always have to spend 1 extra minute after downloading the last video

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    ll m;
    cin >> n >> m;
    vector<ll> a(n);
    ll ans = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        ans += a[i];
    }
    sort(a.begin(), a.end());
    ans ++;
    int r = n - 1;
    for(int i = 0; i < n; i++){
        while(r > i && a[r] + a[i] > m) { 
            //cout << i << " " << r << "\n";
            r --;
            ans ++;
        }
        if(r == i){
            break;
        }
        r--;
    }
    cout << ans << "\n";
    
    return 0;
}

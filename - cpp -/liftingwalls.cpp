#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 06 F

//instead of looking through all combinations of cranes, you can notice that multiple cranes reach the same set of walls. 

//how many sets of these walls are there?, well there are only 2^4, or 16 sets. We can look through all combinations
//of these 16 sets. 

ld dist(ld x1, ld y1, ld x2, ld y2){
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    ld l, w, r;
    int n;
    cin >> l >> w >> n >> r;
    r += 0.00000001;
    set<int> s;
    for(int i = 0; i < n; i++){
        ld x, y;
        cin >> x >> y;
        int val = 0;
        if(dist(x, y, 0, -w / 2) <= r){
            val |= (1 << 0);
        }
        if(dist(x, y, 0, w / 2) <= r){
            val |= (1 << 1);
        }
        if(dist(x, y, -l / 2, 0) <= r){
            val |= (1 << 2);
        }
        if(dist(x, y, l / 2, 0) <= r){
            val |= (1 << 3);
        }
        s.insert(val);
    }
    vector<int> a(0);
    for(auto i = s.begin(); i != s.end(); i++){
        a.push_back(*i);
    }
    int ans = 100;
    for(int i = 0; i < (1 << a.size()); i++){
        int val = 0;
        int ccnt = 0;
        for(int j = 0; j < a.size(); j++){
            if((i >> j) & 1 != 0){
                ccnt ++;
                val |= a[j];
            }
        }
        int cnt = 0;
        for(int j = 0; j < 4; j++){
            if((val >> j) & 1 != 0){
                cnt ++;
            }
        }
        if(cnt == 4){
            ans = min(ans, ccnt);
        }
    }
    if(ans == 100){
        cout << "Impossible\n";
    }
    else {
        cout << ans << "\n";
    }
    
    return 0;
}

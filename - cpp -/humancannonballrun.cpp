#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 10 C

//just do dijkstra's, or you can just do bellman ford since n is so small. 

ld cdist(pair<ld, ld> a, pair<ld, ld> b) {
    return sqrt(pow(a.first - b.first, 2) + pow(a.second - b.second, 2));
}

void setLen(pair<ld, ld>& v, ld len) {
    ld ilen = cdist({0, 0}, v);
    v.first *= len / ilen;
    v.second *= len / ilen;
}

pair<ld, ld> sub(pair<ld, ld> a, pair<ld, ld> b) {
    return {a.first - b.first, a.second - b.second};
}

pair<ld, ld> add(pair<ld, ld> a, pair<ld, ld> b){ 
    return {a.first + b.first, a.second + b.second};
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    vector<pair<ld, ld>> a(0);
    ld x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    a.push_back({x1, y1});
    a.push_back({x2, y2});
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        ld x, y;
        cin >> x >> y;
        a.push_back({x, y});
    }
    n += 2;
    vector<ld> d(n, INT32_MAX);
    d[0] = 0;
    stack<int> s;
    s.push(0);
    while(s.size() != 0){
        int cur = s.top();
        ld dist = d[cur];
        s.pop();
        //cout << "CUR : " << cur << " " << dist << endl;
        if(cur > 1) {
            //do the cannon
            for(int i = 0; i < n; i++){
                if(i == cur){
                    continue;
                }
                pair<ld, ld> dest = {a[i].first, a[i].second};
                pair<ld, ld> lPos = {a[cur].first, a[cur].second};
                pair<ld, ld> lVec = sub(a[i], a[cur]);
                setLen(lVec, 50);
                lPos = add(lPos, lVec);
                ld nextDist = dist + cdist(dest, lPos) / 5.0 + 2;
                //cout << lVec.first << " " << lVec.second << "\n";
                //cout << i << " " << d[i] << " " << nextDist << "NEW CAN" << endl;
                if(nextDist >= d[i] - 0.00000001) {
                    continue;
                }
                d[i] = nextDist;
                s.push(i);
            }
        }
        //run directly
        for(int i = 0; i < n; i++){
            if(i == cur){
                continue;
            }
            pair<ld, ld> dest = {a[i].first, a[i].second};
            pair<ld, ld> lPos = {a[cur].first, a[cur].second};
            ld nextDist = dist + cdist(dest, lPos) / 5.0;
            if(nextDist >= d[i] - 0.00000001) {
                continue;
            }
            //cout << i << " " << d[i] << " " << nextDist << "NEW " << endl;
            d[i] = nextDist;
            s.push(i);
        }
    }
    cout << fixed << setprecision(10) << d[1] << "\n";
    
    return 0;
}

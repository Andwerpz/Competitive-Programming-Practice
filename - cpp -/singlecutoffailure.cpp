#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2018 H
    
//didn't have the right idea for this one. 

vector<ld> solve(int n, int w, int h, vector<int> a) {
    vector<tuple<ld, int, int, int>> ang(0);
    for(int i = 0; i < n; i++){
        int x1, y1, x2, y2;
        x1 = a[i * 4 + 0];
        y1 = a[i * 4 + 1];
        x2 = a[i * 4 + 2];
        y2 = a[i * 4 + 3];
        //compute angle from origin for both 
        ld ra = atan2((ld) y1 - (ld) h / 2.0, (ld) x1 - (ld) w / 2.0);
        ld rb = atan2((ld) y2 - (ld) h / 2.0, (ld) x2 - (ld) w / 2.0);
        //cout << ra << " " << x1 << " " << y1 << endl;
        //cout << rb << " " << x2 << " " << y2 << endl;
        ang.push_back({ra, i, x1, y1});
        ang.push_back({rb, i, x2, y2});
    }
    //sort all of the angles. 
    sort(ang.begin(), ang.end(), [](tuple<ld, int, int, int>& a, tuple<ld, int, int, int>& b) -> bool{
        return get<0>(a) < get<0>(b);
    });
    bool isValid = false;
    int p1 = 0;
    int p2 = 0;
    set<int> s;
    int x1, y1, x2, y2;
    bool rp1 = false;
    bool rp2 = false;
    while(p2 != ang.size() + 10) {
        //increment p1 until there is a wire that is contained between p1 and p2
        while(true){
            //check if we can increment p1
            if(s.find(get<1>(ang[(p1 + 1) % ang.size()])) != s.end()) {
                break;
            }
            s.insert(get<1>(ang[(p1 + 1) % ang.size()]));
            p1 ++;
        }
        //check if we can make the cut here
        {
            bool sameWall = false;
            rp1 = false;
            rp2 = false;
            x1 = get<2>(ang[p1 % ang.size()]);
            y1 = get<3>(ang[p1 % ang.size()]);
            x2 = get<2>(ang[p2 % ang.size()]);
            y2 = get<3>(ang[p2 % ang.size()]);
            if((x1 == 0 && x2 == 0) || (x1 == w && x2 == w) || (y1 == 0 && y2 == 0) || (y1 == h && y2 == h)) {
                sameWall = true;
            }
            if(s.size() == n && !sameWall){
                isValid = true;
                break;
            }
        }
        {
            bool sameWall = false;
            rp1 = true;
            rp2 = false;
            x1 = get<2>(ang[(p1 + 1) % ang.size()]);
            y1 = get<3>(ang[(p1 + 1) % ang.size()]);
            x2 = get<2>(ang[p2 % ang.size()]);
            y2 = get<3>(ang[p2 % ang.size()]);
            if((x1 == 0 && x2 == 0) || (x1 == w && x2 == w) || (y1 == 0 && y2 == 0) || (y1 == h && y2 == h)) {
                sameWall = true;
            }
            if(s.size() == n && !sameWall){
                isValid = true;
                break;
            }
        }
        {
            bool sameWall = false;
            rp1 = false;
            rp2 = true;
            x1 = get<2>(ang[p1 % ang.size()]);
            y1 = get<3>(ang[p1 % ang.size()]);
            x2 = get<2>(ang[(p2 + 1) % ang.size()]);
            y2 = get<3>(ang[(p2 + 1) % ang.size()]);
            if((x1 == 0 && x2 == 0) || (x1 == w && x2 == w) || (y1 == 0 && y2 == 0) || (y1 == h && y2 == h)) {
                sameWall = true;
            }
            if(s.size() == n && !sameWall){
                isValid = true;
                break;
            }
        }
        {
            bool sameWall = false;
            rp1 = true;
            rp2 = true;
            x1 = get<2>(ang[(p1 + 1) % ang.size()]);
            y1 = get<3>(ang[(p1 + 1) % ang.size()]);
            x2 = get<2>(ang[(p2 + 1) % ang.size()]);
            y2 = get<3>(ang[(p2 + 1) % ang.size()]);
            if((x1 == 0 && x2 == 0) || (x1 == w && x2 == w) || (y1 == 0 && y2 == 0) || (y1 == h && y2 == h)) {
                sameWall = true;
            }
            if(s.size() == n && !sameWall){
                isValid = true;
                break;
            }
        }
        //increment p2
        s.erase(get<1>(ang[(p2 + 1) % ang.size()]));
        p2 ++;
    }
    if(!isValid) {
        return {0, 0.01, (ld) w, h - 0.01, 0, h - 0.01, (ld) w, 0.01};
    }
    ld dx1 = x1;
    ld dy1 = y1;
    ld dx2 = x2;
    ld dy2 = y2;
    if(x1 == 0){
        dy1 -= 0.01 * (rp1? -1 : 1);
    }
    else if(x1 == w){
        dy1 += 0.01 * (rp1? -1 : 1);
    }
    else if(y1 == 0){
        dx1 += 0.01 * (rp1? -1 : 1);
    }
    else if(y1 == h){
        dx1 -= 0.01 * (rp1? -1 : 1);
    }
    if(x2 == 0){
        dy2 -= 0.01 * (rp2? -1 : 1);
    }
    else if(x2 == w){
        dy2 += 0.01 * (rp2? -1 : 1);
    }
    else if(y2 == 0){
        dx2 += 0.01 * (rp2? -1 : 1);
    }
    else if(y2 == h){
        dx2 -= 0.01 * (rp2? -1 : 1);
    }
    return {dx1, dy1, dx2, dy2};
}

bool check(int n, int w, int h, vector<int> a, vector<ld> ans) {
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, w, h;
    cin >> n >> w >> h;
    vector<int> a(n * 4);
    for(int i = 0; i < a.size(); i++){
        cin >> a[i];
    }
    vector<ld> ans = solve(n, w, h, a);
    cout << ans.size() / 4 << "\n";
    for(int i = 0; i < ans.size(); i++){
        cout << ans[i] << " ";
        if((i + 1) % 4 == 0){
            cout << "\n";
        }
    }
    
    return 0;
}

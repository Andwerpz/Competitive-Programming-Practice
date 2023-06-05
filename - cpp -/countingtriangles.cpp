#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 14 A

//to see if 3 line segments form a triangle, we can just see if they all intersect with each other. 

//since 50 choose 3 is around 20k, you can just brute force. 

struct vec {
    ld x, y;
};

vec add(vec a, vec b){
    vec ret;
    ret.x = a.x + b.x;
    ret.y = a.y + b.y;
    return ret;
}

vec sub(vec a, vec b) {
    vec ret;
    ret.x = a.x - b.x;
    ret.y = a.y - b.y;
    return ret;
}

ld cross(vec a, vec b) {
    return a.x * b.y - a.y * b.x;
}

ld dot(vec a, vec b) {
    return a.x * b.x + a.y * b.y;
}

ld length(vec a) {
    return sqrt(a.x * a.x + a.y * a.y);
}

vec normalize(vec a){
    ld len = length(a);
    vec ret;
    ret.x = a.x / len;
    ret.y = a.y / len;
    return ret;
}

//returns the coefficients s and t, where p1 + v1 * s = p2 + v2 * t
vector<ld> calcLineIntersect(vec p1, vec v1, vec p2, vec v2) {
    if(cross(v1, v2) == 0){
        return {};
    }
    ld s = cross(sub(p2, p1), v2) / cross(v1, v2);
    ld t = cross(sub(p1, p2), v1) / cross(v2, v1);
    return {s, t};
}

bool solve(pair<vec, vec> a, pair<vec, vec> b) {
    vector<ld> st = calcLineIntersect(a.first, a.second, b.first, b.second);
    if(st.size() == 0){
        return false;
    }
    if(st[0] < 0 || st[0] > 1 || st[1] < 0 || st[1] > 1){
        return false;
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    while(n != 0){
        vector<pair<vec, vec>> a(0);
        for(int i = 0; i < n; i++){
            vec u, v;
            cin >> u.x >> u.y >> v.x >> v.y;
            v = sub(v, u);
            a.push_back({u, v});
        }
        int ans = 0;
        for(int i = 0; i < a.size(); i++){
            for(int j = i + 1; j < a.size(); j++){
                for(int k = j + 1; k < a.size(); k++){
                    if(solve(a[i], a[j]) && solve(a[j], a[k]) && solve(a[k], a[i])) {
                        ans ++;
                    }
                }
            }
        }
        cout << ans << "\n";
        cin >> n;
    }
    
    return 0;
}

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

//3rd Universal Cup, Stage 27: London - D

//just use gradient descent lol

struct vec3 {
    ld x, y, z;
    vec3() {x = 0, y = 0, z = 0;}
    vec3(ld _x, ld _y, ld _z) {x = _x, y = _y, z = _z;}
    vec3(const vec3& other) {x = other.x, y = other.y, z = other.z;}
    vec3(const vec3& a, const vec3& b) {x = b.x - a.x, y = b.y - a.y, z = b.z - a.z;}
    vec3& operator+=(const vec3& other) {x += other.x, y += other.y, z += other.z; return *this;}
    vec3& operator-=(const vec3& other) {x -= other.x, y -= other.y, z -= other.z; return *this;}
    vec3 operator+(const vec3& other) {return vec3(*this) += other;}
    vec3 operator-(const vec3& other) {return vec3(*this) -= other;}

    vec3& operator*=(const ld s) {x *= s, y *= s, z *= s; return *this;}
    vec3 operator*(const ld s) {return vec3(*this) *= s;}

    ld lengthSq() {return x * x + y * y + z * z;}
    ld length() {return sqrt(lengthSq());}
    ld dist(const vec3& other) {return vec3(*this, other).length();}
};

ld randf() {
    return (ld) (rand() % (1 << 16)) / (ld) (1 << 16);
}

vvd gen_d(int n) {
    vector<vec3> pt(n);
    for(int i = 0; i < n; i++) pt[i] = {randf(), randf(), randf()};
    vvd d(n, vd(n, 0));
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            ld dev = (randf() * 0.2) - 0.1;
            d[i][j] = pt[i].dist(pt[j]);
            d[j][i] = pt[i].dist(pt[j]);
            d[i][j] += dev, d[j][i] += dev;
        }
    }
    return d;
}

void solve() {
    int n;
    cin >> n;
    // n = 10;
    vvd d(n, vd(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++) cin >> d[i][j];
    }
    // d = gen_d(n);
    // cout << "D : " << "\n";
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++){
    //         cout << d[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    vector<vec3> pt(n);
    for(int i = 0; i < n; i++) {
        pt[i] = {randf(), randf(), randf()};
        // cout << pt[i].x << " " << pt[i].y << " " << pt[i].z << endl;
    }
    ld rate = 1;
    ld mult = 0.9999;
    int step = 0, retry = 0;
    while(true) {
        step ++;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(j == i) continue;
                // cout << pt[i].x << " " << pt[i].y << " " << pt[i].z << endl;
                ld dev = pt[i].dist(pt[j]) - d[i][j];
                // vec3 inc = (pt[j] - pt[i])
                ld sign = dev < 0? -1 : 1;
                dev = abs(dev);
                vec3 dir = pt[j] - pt[i];
                if(dir.length() != 0){
                    dir *= 1.0 / dir.length();
                    pt[i] += dir * max((ld) -0.01, min((ld) 0.01, dev * dev * sign));
                }
                // cout << "DEV : " << dev << endl;
                // cout << pt[i].x << " " << pt[i].y << " " << pt[i].z << endl;
            }
        }
        bool is_valid = true;
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                if(abs(pt[i].dist(pt[j]) - d[i][j]) > 0.1) is_valid = false;
            }
        }
        if(is_valid) break;
        rate *= mult;
        // cout << fixed << setprecision(10);
        // for(int i = 0; i < n; i++){
        //     cout << pt[i].x << " " << pt[i].y << " " << pt[i].z << "\n";
        // }
        // cout << endl;
        if(step > 100) {
            step = 0, retry ++;
            for(int i = 0; i < n; i++) {
                pt[i] = {randf(), randf(), randf()};
                // cout << pt[i].x << " " << pt[i].y << " " << pt[i].z << endl;
            }
        }
    }
    // cout << "RETRY : " << retry << "\n";
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            ld dev = abs(pt[i].dist(pt[j]) - d[i][j]);
            assert(dev <= 0.1);
            // cout << "DEV : " << i << " " << j << " " << dev << "\n";
        }
    }
    // cout << "ANSWER : " << endl;
    cout << fixed << setprecision(10);
    for(int i = 0; i < n; i++){
        cout << pt[i].x << " " << pt[i].y << " " << pt[i].z << "\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    srand(time(0));
    solve();
    // int cnt = 0;
    // while(true) {
    //     cout << "SOLVE : " << cnt << endl;
    //     solve();
    //     cnt ++;
    // }
    
    return 0;
}
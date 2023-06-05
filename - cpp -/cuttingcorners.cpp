#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 14 B

//You can just brute force the process. 

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

void solve2(vector<vec>& arr, ld& minAng, int& minInd) {
    minInd = -1;
    minAng = 1e9;
    for(int i = 1; i < arr.size() + 1; i++){
        vec a = arr[i % arr.size()];
        vec b = arr[(i + 1) % arr.size()];
        vec c = arr[(i + 2) % arr.size()];
        vec ab = normalize(sub(b, a));
        vec bc = normalize(sub(c, b));
        ld theta = 3.1415926 - acos(dot(ab, bc));
        if(theta < minAng) {
            minAng = theta;
            minInd = (i + 1) % arr.size();
        }
    }
}

//removes the smallest
vector<vec> solve(vector<vec>& arr) {
    int minInd = -1;
    ld minAng = 1e9;
    solve2(arr, minAng, minInd);
    vector<vec> ret(0);
    for(int i = 0; i < arr.size(); i++){
        if(i == minInd) {
            continue;
        }
        ret.push_back(arr[i]);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    while(n != 0){
        vector<vec> a(n);
        for(int i = 0; i < n; i++){
            cin >> a[i].x >> a[i].y;
        }
        while(a.size() > 3){
            ld curMin = 1e9;
            int curInd = -1;
            solve2(a, curMin, curInd);
            vector<vec> next = solve(a);
            ld nextMin = 1e9;
            int nextInd = -1;
            solve2(next, nextMin, nextInd);
            //cout << curMin << " " << nextMin << "\n";
            if(curMin > nextMin){
                break;
            }
            a = next;
        }
        cout << a.size() << " ";
        for(int i = 0; i < a.size(); i++){
            cout << (int) a[i].x << " " << (int) a[i].y << " ";
        }
        cout << "\n";
        cin >> n;
    }
    
    return 0;
}

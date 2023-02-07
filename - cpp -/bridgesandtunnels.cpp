#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 03 B

//classic dsu problem

const int N = 1e6;
vector<int> dsu(N, 0);
vector<int> amt(N, 1);

int find(int a) {
    if(dsu[a] == a){
        return a;
    }
    return dsu[a] = find(dsu[a]);
}

void unify(int a, int b) {
    int aRoot = find(a);
    int bRoot = find(b);
    if(aRoot != bRoot) {
        dsu[aRoot] = bRoot;
        amt[bRoot] += amt[aRoot];
    }
}

int getSize(int a){
    return amt[find(a)];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    for(int i = 0; i < N; i++){
        dsu[i] = i;
    }
    int n;
    cin >> n;
    map<string, int> m;
    for(int i = 0; i < n; i++){
        string sa, sb;
        cin >> sa >> sb;
        int a, b;
        if(m.find(sa) == m.end()) {
            m.insert({sa, m.size()});
        }
        if(m.find(sb) == m.end()) {
            m.insert({sb, m.size()});
        }
        a = m.find(sa) -> second;
        b = m.find(sb) -> second;
        unify(a, b);
        //cout << a << " " << b << "\n";
        cout << getSize(a) << "\n";
    }
    
    return 0;
}

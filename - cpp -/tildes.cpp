#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 05 F

//classic dsu

const int N = 2e6;
vector<int> dsu(N, 0);
vector<int> amt(N, 0);

int find(int a) {
    if(dsu[a] == a) {
        return a;
    }
    return dsu[a] = find(dsu[a]);
}

bool unify(int a, int b) {
    int ra = find(a);
    int rb = find(b);
    if(ra == rb) {
        return false;
    }
    dsu[rb] = ra;
    amt[ra] += amt[rb];
    return true;
}

int getAmt(int a){
    return amt[find(a)];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    for(int i = 0; i < n; i++){
        amt[i] = 1;
        dsu[i] = i;
    }
    for(int i = 0; i < q; i++){
        string type;
        cin >> type;
        if(type == "t"){
            int a, b;
            cin >> a >> b;
            a --;
            b --;
            unify(a, b);
        }
        else {
            int a;
            cin >> a;
            a --;
            cout << getAmt(a) << "\n";
        }
    }
    
    return 0;
}

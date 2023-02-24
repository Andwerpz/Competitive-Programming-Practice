#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 06 H

//classic dsu

vector<int> dsu;

int find(int a){
    if(dsu[a] == a){
        return a;
    }
    return dsu[a] = find(dsu[a]);
}

void unify(int a, int b){
    int ra = find(a);
    int rb = find(b);
    if(ra == rb){
        return;
    }
    dsu[rb] = ra;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    dsu = vector<int>(n, 0);
    for(int i = 0; i < n; i++){
        dsu[i] = i;
    }
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        a --;
        b --;
        unify(a, b);
    }
    bool found = false;
    for(int i = 0; i < n; i++){
        if(find(i) != find(0)){
            cout << i + 1 << "\n";
            found = true;
        }
    }
    if(!found){
        cout << "Connected\n";
    }
    
    return 0;
}

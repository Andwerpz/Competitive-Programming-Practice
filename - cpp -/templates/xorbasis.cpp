#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool insertBasis(vector<int>& basis, int x){
    for(int i = 0; i < basis.size(); i++){
        if((x & 1 << i) == 0) continue;
        if(!basis[i]) {basis[i] = x; return true;}
        x ^= basis[i];
    }
    return false;
}

bool inBasis(vector<int>& basis, int x){
    for(int i = 0; i < basis.size(); i++)
        if(x & 1 << i) x ^= basis[i];
    return x == 0;
}
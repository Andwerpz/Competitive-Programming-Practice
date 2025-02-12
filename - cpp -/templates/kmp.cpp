#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//creates kmp array for s. 
vector<int> kmp(vector<int> s) {
    int n = s.size();
    vector<int> b(n+1,-1);
    int i = 0, j = -1;
    while(i != n) {
        while(j != -1 && s[i] != s[j]) {
            j = b[j];
        }
        i++;
        j++;
        b[i] = j;
    }
    return b;
}

//finds all occurences of m in n with kmp array of m, a. 
vector<int> find_matches(vector<int> &n, vector<int> &m, vector<int> &a) {
    vector<int> matches;
    int i = 0;
    int j = 0;
    while(i < n.size()) {
        while(j == m.size() || (j != -1 && n[i] != m[j])) {
            j = a[j];
        }
        i++;
        j++;
        if(j == m.size()) {
            matches.push_back(i - m.size() + 1);
        }
    }
    return matches;
}

vector<int> find_matches(vector<int>& n, vector<int>& m){
    vector<int> k = kmp(m);
    return find_matches(n, m, k);
}
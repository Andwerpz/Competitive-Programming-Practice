#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1203F1

//We can split the projects into two groups, projects with a non-negative rating change, and projects with a negative
//rating change. 

//denote these two groups pos and neg repsectively. 

//we can first do the projects in the pos group first. Order them in ascending a_i, and do them in that order. 
//next, we do the neg projects. We order these in descending order of a_i. 

//if at any point you can't do a project, or r becomes negative, then the input is invalid. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, r;
    cin >> n >> r;
    vector<pair<int, int>> pos(0);
    vector<pair<int, int>> neg(0);
    for(int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        if(b >= 0){
            pos.push_back({a, b});
        }
        else{
            neg.push_back({a, b});
        }
    }
    sort(pos.begin(), pos.end(), [] (pair<int, int>& a, pair<int, int>& b) {return a.first < b.first;});
    sort(neg.begin(), neg.end(), [] (pair<int, int>& a, pair<int, int>& b) {return (b.first + b.second) < (a.first + a.second);});
    bool isValid = true;
    for(int i = 0; i < pos.size(); i++){
        if(r < pos[i].first){
            isValid = false;
            break;
        }
        r += pos[i].second;
    }
    for(int i = 0; i < neg.size(); i++){
        if(r < neg[i].first){
            isValid = false;
            break;
        }
        r += neg[i].second;
    }
    if(r < 0){
        isValid = false;
    }
    cout << (isValid? "YES\n" : "NO\n");
    
    return 0;
}

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2019 A

//

void insert(map<int, set<int>>& m, int val, int ind) {
    if(m.find(val) == m.end()){
        m.insert({val, set<int>()});
    }
    m.find(val) -> second.insert(ind);
}

int erase(map<int, set<int>>& m, int val) {
    int ret = *(m.find(val) -> second.begin());
    m.find(val) -> second.erase(ret);
    if(m.find(val) -> second.size() == 0){
        m.erase(val);
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<vector<int>> a(n, vector<int>(3, 0));    //back row; price, height, original ind
    vector<vector<int>> b(n, vector<int>(3, 0));    //front row; price, height, original ind
    for(int i = 0; i < n; i++){
        cin >> a[i][0];
    }
    for(int i = 0; i < n; i++){
        cin >> a[i][1];
        a[i][2] = i + 1;
    }
    for(int i = 0; i < n; i++){
        cin >> b[i][0];
    }
    for(int i = 0; i < n; i++){
        cin >> b[i][1];
        b[i][2] = i + 1;
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    map<int, set<int>> ma;
    map<int, set<int>> mb;
    int pa = 0;
    int pb = 0;
    bool isValid = true;
    vector<int> ans_a(0);
    vector<int> ans_b(0);
    while(pa != n || pb != n) {
        //cout << pa << " " << pb << endl;
        if(ma.size() == 0){
            int price = a[pa][0];
            while(pa != n && a[pa][0] == price) {
                insert(ma, a[pa][1], a[pa][2]);
                pa ++;
            }
        }
        if(mb.size() == 0){
            int price = b[pb][0];
            while(pb != n && b[pb][0] == price) {
                insert(mb, b[pb][1], b[pb][2]);
                pb ++;
            }
        }
        //cout << "MID : " << pa << " " << pb << endl;
        while(ma.size() != 0 && mb.size() != 0){
            int va = -1;
            int vb = -1;
            if(pa < pb){
                //cout << "F SHORT : " << endl;
                va = ma.begin() -> first;
                if(mb.begin() -> first >= va) {
                    isValid = false;
                    break;
                }
                auto i = mb.lower_bound(va);
                i --;
                vb = i -> first;
            }
            else {
                vb = mb.begin() -> first;
                if(ma.rbegin() -> first <= vb) {
                    isValid = false;
                    break;
                }
                //cout << "THERE IS A VAL " << endl;
                //cout << ma.rbegin() -> first << " " << vb << endl;
                auto i = ma.upper_bound(vb);
                va = i -> first;
            }
            ans_a.push_back(erase(ma, va));
            ans_b.push_back(erase(mb, vb));
        }
        if(!isValid){
            break;
        }
    }
    if(!isValid) {
        cout << "impossible\n";
        return 0;
    }
    for(int i = 0; i < n; i++){
        cout << ans_a[i] << " \n"[i == n - 1];
    }
    for(int i = 0; i < n; i++){
        cout << ans_b[i] << " \n"[i == n - 1];
    }
    
    return 0;
}

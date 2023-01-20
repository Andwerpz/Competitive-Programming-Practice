#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 01 A

//the problem says that you can't put a dash between two adjacent bus stops. 
//other than that, it's pretty simple

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int l = a[0];
    int r = a[0];
    for(int i = 1; i < n; i++){
        if(a[i] - r > 1) {
            if(l == r){
                cout << l << " ";
            }
            else if(l == r - 1){
                cout << l << " " << r << " ";
            }
            else {
                cout << l << "-" << r << " ";
            }
            l = a[i];
            r = a[i];
        }
        else {
            r = a[i];
        }
    }
    if(l == r){
        cout << l << " ";
    }
    else if(l == r - 1){
        cout << l << " " << r << " ";
    }
    else {
        cout << l << "-" << r << " ";
    }
    cout << "\n";
    
    return 0;
}

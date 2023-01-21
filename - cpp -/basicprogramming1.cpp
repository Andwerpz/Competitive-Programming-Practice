#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 01 A

//annoying implementation >:(

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, t;
    cin >> n >> t;
    vector<ll> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    if(t == 1) {
        cout << "7\n";
    }
    else if(t == 2){
        if(a[0] > a[1]){
            cout << "Bigger\n";
        }
        else if(a[0] == a[1]) {
            cout << "Equal\n";
        }
        else {
            cout << "Smaller\n";
        }
    }
    else if(t == 3) {
        vector<int> tmp(3);
        tmp[0] = a[0];
        tmp[1] = a[1];
        tmp[2] = a[2];
        sort(tmp.begin(), tmp.end());
        cout << tmp[1] << "\n";
    }
    else if(t == 4) {
        ll sum = 0;
        for(ll i : a) {
            sum += i;
        }
        cout << sum << "\n";
    }
    else if(t == 5) {
        ll sum = 0;
        for(ll i : a){
            sum += (i % 2 == 0? i : 0);
        }
        cout << sum << "\n";
    }
    else if(t == 6) {
        for(int i : a){
            cout << (char) ((i % 26) + 'a');
        }
        cout << "\n";
    }
    else if(t == 7) {
        int i = 0;
        vector<bool> v(n);
        while(true) {
            i = a[i];
            if(i < 0 || i >= n) {
                cout << "Out\n";
                break;
            }
            if(i == n - 1){
                cout << "Done\n";
                break;
            }
            if(v[i]){
                cout << "Cyclic\n";
                break;
            }
            v[i] = true;
        }
    }
    
    return 0;
}

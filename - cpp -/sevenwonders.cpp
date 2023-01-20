#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 01 G

//simple maths. 
//quick maths

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string st;
    cin >> st;
    int t = 0;
    int c = 0;
    int g = 0;
    for(int i = 0; i < st.size(); i++){
        t += st[i] == 'T'? 1 : 0;
        c += st[i] == 'C'? 1 : 0;
        g += st[i] == 'G'? 1 : 0;
    }
    cout << (t * t + g * g + c * c + min(t, min(g, c)) * 7) << "\n";
    
    return 0;
}

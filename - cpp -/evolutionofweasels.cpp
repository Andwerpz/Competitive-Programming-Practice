#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//SWERC 2021-2022 D

//since the mutations are completely reversible, if we can convert both strings into a common form using the
//mutations, then it should be possible to convert between the two. 

//first, notice that we can use AA, BB, and ABAB mutations in conjunction to swap any occurrence of AB or BA
//between each other: BA -> AABABB -> AB

//note that the same can be done with BB, CC, and BCBC. This means that any 'B' character is free to move
//as it likes within the string, so the first thing we can do is remove all 'B' characters from both strings. 
//Note that if the parity of Bs in the strings are different, then it's impossible to convert from one string
//to another. 

//now, the two strings should entirely consist of As and Cs. Since we can't swap these around, we simply have
//to try to remove as many of them as we can. If at the end they are the same, then it's possible to convert 
//between the two. 

bool reduce(string& a) {
    bool ans = false;
    string tmp = "";
    for(int i = 0; i < a.size();){
        int r = i;
        while(r != a.size() && a[r] == a[i]) {
            r ++;
        }
        int amt = r - i;
        if(amt % 2 == 1){
            if(amt > 1){
                ans = true;
            }
            tmp.push_back(a[i]);
        }
        else {
            ans = true;
        }
        i = r;
    }
    a = tmp;
    return ans;
}

void rm_b(string& a){
    string tmp = "";
    for(int i = 0; i < a.size(); i++){
        if(a[i] == 'B') {
            continue;
        }
        tmp.push_back(a[i]);
    }
    a = tmp;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        string a, b;
        cin >> a >> b;
        int a_bcnt = 0;
        int b_bcnt = 0;
        for(int i = 0; i < a.size(); i++){
            if(a[i] == 'B') {
                a_bcnt ++;
            }
        }
        for(int i = 0; i < b.size(); i++){
            if(b[i] == 'B') {
                b_bcnt ++;
            }
        }
        if(a_bcnt % 2 != b_bcnt % 2){
            cout << "NO\n";
            continue;
        }
        rm_b(a);
        rm_b(b);
        while(true) {
            if(!(reduce(a) | reduce(b))) {
                break;
            }
        }
        cout << (a == b? "YES" : "NO") << "\n";
    }
    
    return 0;
}

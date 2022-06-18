#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1697C

//we can move b to the left when surrounded by a, and to the right when surrounded by c. 

//you can't have an a or c in the same position. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        string a, b;
        cin >> a >> b;
        int pa = 0;
        int pb = 0;
        bool isValid = true;
        while(pa < n){
            while(a[pa] == 'b'){
                pa ++;
            }
            while(b[pb] == 'b'){
                pb ++;
            }
            if(a[pa] != b[pb]){
                isValid = false;
                break;
            }
            pa ++;
            pb ++;
        }
        vector<int> ca(3);
        vector<int> cb(3);
        bool sa = false;
        for(int i = 0; i < n; i++){
            if((a[i] == 'a' && b[i] == 'c') || (a[i] == 'c' && b[i] == 'a')){
                isValid = false;
                break;
            }
            bool change = false;
            if(sa && (a[i] == 'c' || b[i] == 'c')){
                change = true;
            }
            else if(!sa && (a[i] == 'a' || b[i] == 'a')){
                change = true;
            }
            if(change){
                sa = !sa;
                if(ca[0] != cb[0] || ca[1] != cb[1] || ca[2] != cb[2]){
                    isValid = false;
                    break;
                }
            }
            ca[a[i] == 'a'? 0 : (a[i] == 'b'? 1 : 2)] ++;
            cb[b[i] == 'a'? 0 : (b[i] == 'b'? 1 : 2)] ++;
            if(sa){
                if(cb[1] < ca[1]){
                    isValid = false;
                    break;
                }
            }
            else{
                if(cb[1] > ca[1]){
                    isValid = false;
                    break;
                }
            }
        }
        if(ca[0] != cb[0] || ca[1] != cb[1] || ca[2] != cb[2]){
            isValid = false;
        }
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}

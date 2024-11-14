#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//Codeforces - 2022 D1 D2

//querying a b is equivalent to seeing if a thinks that b is the same type as them. For example, a 
//knight would say 0 or no to a knave, but 1 or yes to the impostor. 

//we can check if a person is the impostor using 4 queries. If we have 3 people, a, b, c, and we want
//to check if a is the impostor, we just have to make sure that q(a, b) != q(b, a) && q(a, c) != q(c, a).

//first thing to do is put all elements into two categories, by comparing adjacent elements. However,
//when we get to the impostor, our categories will become flipped. 

//we can search for when the categories become flipped using binary search. First we must make sure that
//the first element isn't the impostor, so we can use the method mentioned above. 

//however, to solve the hard version, we can't rely on binary search. For n >= 4, we can solve the
//problem in at most n queries. Go read the editorial D:

bool is_impostor(int i, int j) {
    int tmp1, tmp2;
    cout << "? " << i + 1 << " " << j + 1 << endl;
    cin >> tmp1;
    cout << "? " << j + 1 << " " << i + 1 << endl;
    cin >> tmp2;
    return tmp1 != tmp2;
}

int query(int i, int j){
    int tmp;
    cout << "? " << i + 1 << " " << j + 1 << endl;
    cin >> tmp;
    return tmp;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int ans = n - 1;
        if(n == 3) {
            bool a = is_impostor(0, 1);
            bool b = is_impostor(1, 2);
            if(a && b){
                ans = 1;
            }
            else if(a){
                ans = 0;
            }
            else {
                ans = 2;
            }
        }
        else if(n == 4){
            bool a = is_impostor(0, 1);
            bool b = is_impostor(1, 2);
            if(a && b){
                ans = 1;
            }
            else if(!a && !b){
                ans = 3;
            }
            else if(a){
                ans = 0;
            }
            else {
                ans = 2;
            }
        }
        else {
            if(n % 2 == 0){
                //leave out one pair
                bool found_impostor = false;
                for(int i = 0; i + 2 <= n - 1; i += 2) {
                    if(is_impostor(i, i + 1)) {
                        int other = i == 0? n - 1 : 0;
                        if(is_impostor(i, other)) {
                            ans = i;
                        }
                        else {
                            ans = i + 1;
                        }
                        found_impostor = true;
                        break;
                    }
                }
                if(!found_impostor){
                    //could be second to last, or last. 
                    if(is_impostor(n - 3, n - 2)) {
                        //is second to last
                        ans = n - 2;
                    }
                }
            }
            else {
                //solve the last 2 until we get to the last 5, then solve with 5 operations
                bool found = false;
                for(int i = n - 1; i - 1 >= 5; i -= 2){
                    if(is_impostor(i, i - 1)) {
                        if(is_impostor(i, 0)) {
                            ans = i;
                        }
                        else {
                            ans = i - 1;
                        }
                        found = true;
                        break;
                    }
                }
                if(!found){
                    int a = 1 - query(0, 1);
                    int b = 1 - query(1, 2);
                    int c = 1 - query(2, 0);
                    if((a + b + c) % 2 != 0){
                        //one of 0, 1, 2 has to be impostor
                        int d = 1 - query(1, 0);
                        int e = 1 - query(2, 1);
                        bool _a = a != d;
                        bool _b = b != e;
                        if(_a && _b) {
                            ans = 1;
                        }
                        else if(_a){
                            ans = 0;
                        }
                        else {
                            ans = 2;
                        }
                    }
                    else {
                        //one of 3, 4, has to be impostor
                        if(is_impostor(0, 3)) {
                            ans = 3;
                        }
                        else {
                            ans = 4;
                        }
                    }
                }
            }
        }
        cout << "! " << ans + 1 << endl;
    }

    /* easy version
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vb c(n);
        for(int i = 1; i < n; i++){
            cout << "? " << i + 1 << " " << i << endl;
            int tmp;
            cin >> tmp;
            tmp ^= 1;
            c[i] = c[i - 1] ^ tmp;
        }
        //check if impostor is first
        if(is_impostor(0, 1) && is_impostor(0, 2)) {
            cout << "! 1" << endl;
            continue;
        }
        //otherwise, can binary search
        int low = 1;
        int high = n - 1;
        int ans = 1;
        while(low <= high){
            int mid = low + (high - low) / 2;
            //is this guy consistent with the first one?
            cout << "? " << mid + 1 << " " << 1 << endl;
            int tmp;
            cin >> tmp;
            tmp ^= 1;
            if(tmp == (c[0] ^ c[mid])) {
                // cout << "CONSISTENT" << endl;
                ans = mid;
                low = mid + 1;
            }
            else {
                // cout << "NOT CONSISTENT" << endl;
                high = mid - 1;
            }
        }
        cout << "! " << ans + 1 << endl;
    }
    */
    
    return 0;
}
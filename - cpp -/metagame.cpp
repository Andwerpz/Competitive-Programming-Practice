#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Meta Hacker Cup 2023 Round 2 B

//failed attempt lol. 

bool is_ind_valid(vector<int>& a, vector<int>& b, int ind) {
    int n = a.size();
    bool is_valid = true;
    for(int i = 0; i < n / 2; i++){
        int l = (ind + i) % n;
        int r = (n - 1 - i + ind) % n;
        if(a[l] >= b[l]) {
            is_valid = false;
        }
        if(a[r] <= b[r]) {
            is_valid = false;
        }
    }
    for(int i = 0; i < n; i++){
        int l = (ind + i) % n;
        int r = (n - 1 - i + ind) % n;
        if(a[l] != b[r]) {
            is_valid = false;
        }
    }
    return is_valid;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    std::ifstream in("test.in");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    std::ofstream out("test.out");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    
    int t;
    cin >> t;
    int caseno = 0;
    while(t--) {
        caseno ++;
        cout << "Case #" << caseno << ": ";
        int n;
        cin >> n;
        vector<int> a(n);
        vector<int> b(n);
        for(int i = 0; i < n; i++){
            cin >> a[i];
        }
        for(int i = 0; i < n; i++){
            cin >> b[i];
        }
        int ans = -1;
        //check if 0 seconds is correct. 
        if(is_ind_valid(a, b, 0)) {
            cout << "0\n";
            continue;
        }
        //look for the first time something changes, and try that.  
        int ind = -1;
        for(int i = 1; i < n; i++){
            if(a[0] >= b[0]) {
                if(a[i] < b[i]) {
                    ind = i;
                    break;
                }
            }
            else if(a[0] <= b[0]) {
                if(a[i] > b[i] &&) {

                }
            }
        }
        bool is_valid = true;
        for(int i = 0; i < n / 2; i++){
            int l = (ind + i) % n;
            int r = (n - 1 - i + ind) % n;
            if(a[l] >= b[l]) {
                is_valid = false;
            }
            if(a[r] <= b[r]) {
                is_valid = false;
            }
        }
        for(int i = 0; i < n; i++){
            int l = (ind + i) % n;
            int r = (n - 1 - i + ind) % n;
            if(a[l] != b[r]) {
                is_valid = false;
            }
        }
        cout << (is_valid? ind : -1) << "\n";
    }
    
    return 0;
}

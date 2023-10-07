#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Meta Hacker Cup 2023 C2

//we can first solve the problem for the initial state, and keep track of what buttons we press to make everything black. 
//then, when the brother comes and presses buttons, we can see if we pressed that button in our initial solution. 

//if we did press that button, then we can just not press the button, and it's as if the brother pressed the button to make everything black.
//But if we did not press the button, then we have to press the button now to correct it. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    std::ifstream in("back_in_black_chapter_2_input.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    std::ofstream out("val_out.txt");
    std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
    std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
    
    int t;
    cin >> t;
    int caseno = 0;
    while(t--){
        caseno ++;
        cout << "Case #" << caseno << ": ";
        int n;
        cin >> n;
        vector<bool> b(n, false);
        string line;
        cin >> line;
        for(int i = 0; i < line.size(); i++){
            b[i] = line[i] == '1';
        }
        set<int> press; 
        for(int i = 0; i < n; i++){
            if(b[i]) {
                int inc = i + 1;
                for(int j = i; j < n; j += inc) {
                    b[j] = !b[j];
                }
                press.insert(i);
            }
        }
        int q;
        cin >> q;
        ll ans = 0;
        for(int i = 0; i < q; i++){
            int ind;
            cin >> ind;
            ind --;
            if(press.find(ind) != press.end()) {
                press.erase(ind);
            }
            else {
                press.insert(ind);
            }
            ans += press.size();
        }
        cout << ans << endl;
    }
    
    return 0;
}

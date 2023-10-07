#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Meta Hacker Cup 2023 C1

//if you press a button twice, it's just like you didn't press it at all, so when finding the state of the buttons
//after your brother has pressed them, just count how many times he pressed each index, then mod by 2. 

//To find the minimum number of pressed required to turn everything off, you can first note that if button 1 is on, you must press
//it, because no other button will toggle button 1.

//this logic continues to all the other buttons; traverse from button 1 to button n, and if you see a button that is on, just press it. 
//since the number of buttons affected by each button press is the inverse of the button index, it will take around n * log(n) time.

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    std::ifstream in("back_in_black_chapter_1_input.txt");
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
        int q;
        cin >> q;
        set<int> press;
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
        }
        for(auto i = press.begin(); i != press.end(); i++){
            int inc = *i + 1;
            for(int j = *i; j < n; j += inc) {
                b[j] = !b[j];
            }
        }
        int ans = 0;
        for(int i = 0; i < n; i++){
            if(b[i]) {
                int inc = i + 1;
                for(int j = i; j < n; j += inc) {
                    b[j] = !b[j];
                }
                ans ++;
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}

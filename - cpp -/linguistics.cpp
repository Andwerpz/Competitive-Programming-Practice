#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1686D

//first check is to make sure that the number of 'A' and 'B' characters match up with a b c d values. 

//the number of 'A' characters should equal a + c + d and 
//the number of 'B' characters should equal b + c + d. 

//notice that the words 'A' and 'B' can be put in anywhere, it's the 'AB' and 'BA' words
//that are tricky to place. 

//the key is to notice that this becomes a 2ptr optimization problem. The more 'AB' words you have, 
//the fewer 'BA' words you can have. If you can make sure that there are enough 'AB' and 'BA'
//words in the string, then you can create it with the a b c d values. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        string s;
        cin >> s;
        int ab = c;
        int ba = d;
        vector<pair<int, int>> arr(0);  //type: A-B; X-X; B-A, amt of BA able to create
        int aSum = 0;
        int p = -1;
        int cnt = 0;
        for(int i = 0; i < s.length(); i++){
            if(s[i] == 'A'){
                aSum ++;
            }
            cnt += (i != s.length() - 1 && s[i] == 'A' && s[i + 1] == 'B')? 1 : 0;
            if(i != s.length() - 1 && i > p && s[i] != s[i + 1]) {
                int r = i + 1;
                //cout << s[i] << s[i + 1];
                while(r != s.length() - 1 && s[r] != s[r + 1]) {
                    r ++;
                    //cout << s[r];
                }
                //cout << "\n";
                int diff = r - i + 1;
                if(diff == 2){
                    if(s[i] == 'A'){
                        ab --;
                    }
                    else{
                        ba --;
                    }
                    continue;
                }
                int type = s[i] == s[r]? 1 : (s[i] == 'A'? 0 : 2);
                int amt = 0;
                if(type == 1){
                    amt = (diff - 1) / 2;
                }
                else if(type == 0){
                    amt = diff / 2 - 1;
                }
                else{
                    amt = diff / 2;
                }
                arr.push_back({type, amt});
                ba -= amt;
                //cout << amt << " " << type << "\n";
                p = r;
            }
        }
        //cout << "AB : BA " << ab << " " << ba << "\n";
        //cout << "CNT: " << cnt << "\n";
        sort(arr.begin(), arr.end(), [](pair<int, int> &a, pair<int, int> &b) {
            if(a.first != b.first){
                return a.first < b.first;
            }
            if(a.first == 0){
                return a.second < b.second; //ascending
            }
            else if(a.first == 1){
                return a.second < b.second; //this doesn't really matter
            }
            else{
                return a.second > b.second; //descending
            }
        });
        if(a + c + d != aSum || b + c + d != (s.length() - aSum)) { //sums of letters don't match up
            cout << "NO\n";
            continue;
        }
        bool isValid = ab <= 0 && ba <= 0;
        for(int i = 0; i < arr.size(); i++){
            int type = arr[i].first;
            int amt = arr[i].second;
            //cout << "TYPE : " << type << "\n";
            while(amt != 0){
                amt --;
                ab --;
                ba ++;
                if(type == 0){
                    if(amt == 0){
                        ab --;
                    }
                }
                else if(type == 1){
                }
                else{
                    if(amt == arr[i].second - 1) {
                        amt --;
                        ba ++;
                    }  
                }
                isValid |= ab <= 0 && ba <= 0;
                //cout << ab << " " << ba << "\n";
            }
        }
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}

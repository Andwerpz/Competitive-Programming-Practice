#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1673B

//Notice that in order to make the string perfectly balanced, you can't have a substring
//where one character appears twice, while another one appears 0 times. 

//in order for this to be true, you need to make sure the string is of structure abcd... abcd... abcd...
//where all letters appear, and then they reappear in the same order. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        string s;
        cin >> s;
        int numUnique = 0;
        map<char, int> cset;
        for(int i = 0; i < s.size(); i++){
            if(cset.find(s[i]) == cset.end()){
                cset.insert({s[i], numUnique});
                numUnique ++;
            }
        }
        int expected = 0;
        bool isValid = true;
        for(int i = 0; i < s.size(); i++){
            int next = cset.find(s[i]) -> second;
            if(next != expected){
                isValid = false;
                break;
            }
            expected = (expected + 1) % numUnique;
        }
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}

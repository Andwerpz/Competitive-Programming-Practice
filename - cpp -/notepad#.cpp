#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1766B

//make sure to read carefully, it says return 'YES' if you can write the word in under n steps, not
//'count the minimum amount of steps required to write the word'. 

//notice that we can always write the word in at most n steps just by writing it out letter by letter. 
//so all we need to do is to check whether or not we can save a step by using the copy operation. 

//in order to save a step, the copy operation has to copy over at least 2 letters. Notice that if the copy
//operation can copy more than 2 letters, then it can copy 2 letters as well, so we just need to check if
//at any point we can copy 2 letters. 

//this can be done with a linear search with set to save what 2 letter groups we've already seen. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        string st;
        cin >> st;
        set<string> s;
        bool isValid = false;
        for(int i = 3; i < n; i++){
            string add = st.substr(i - 3, 2);
            s.insert(add);
            string check = st.substr(i - 1, 2);
            if(s.find(check) != s.end()){
                isValid = true;
                break;
            }
        }
        cout << (isValid? "YES" : "NO") << "\n";
    }
    
    return 0;
}

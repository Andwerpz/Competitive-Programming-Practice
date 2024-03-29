#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//Codeforces - 1796A

//typical interview problem lol

//it's just the normal fizz buzz problem, but instead of generating the fizz-buzz output, you are deciding whether
//or not a given output can be generated by the fizz buzz algorithm. 

//notice that fizz buzz repeats every 15 numbers, or the lcm of 3 and 5. So you just have to generate 
//output to around 60, and check if the given string is a substring of the generated string. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    vector<char> a(0, 0);
    for(int i = 1; i <= 60; i++){
        if(i % 3 == 0){
            a.push_back('F');
        }
        if(i % 5 == 0){
            a.push_back('B');
        }
    }
    while(t-- > 0){
        int n;
        cin >> n;
        string s;
        cin >> s;
        bool isValid = false;
        for(int i = 0; i < a.size() - n; i++){
            bool cur = true;
            for(int j = 0; j < n; j++){
                if(s[j] != a[i + j]) {
                    cur = false;
                }
            }
            if(cur) {
                isValid = true;
                break;
            }
        }
        cout << (isValid? "YES\n" : "NO\n");
    }
    
    return 0;
}

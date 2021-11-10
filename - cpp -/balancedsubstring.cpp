
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//Codeforces - 1569A

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while(t-- > 0){
        int n;
        cin >> n;
        string s;
        cin >> s;
        for(int i = 0; i < n; i++){
            int numA = 0;
            int numB = 0;
            if(s[i] == 'a'){
                numA ++;
            }
            else{
                numB ++;
            }
            for(int j = i + 1; j < n; j++){
                if(s[j] == 'a'){
                    numA ++;
                }
                else{
                    numB ++;
                }
                if(numA == numB){
                    cout << (i + 1) << " " << (j + 1) << endl;
                    goto end;
                }
            }
        }
        cout << "-1 -1\n";
        end :;
    }

    return 0;
}




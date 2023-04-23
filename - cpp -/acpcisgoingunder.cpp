#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//TAMU Spring 2023 Programming Contest A

//implementation

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string line;
    getline(cin, line);
    string first;
    string second;
    for(int i = 0; i < line.size(); i++){
        if(line[i] == '@'){
            first = line.substr(0, i);
            second = line.substr(i + 1);
        }
    }
    cout << second << ": " << first << "\n";
    
    return 0;
}

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//CSCE 430 Spring 2023 - Lab 11 B

//implementation

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    set<string> s;
    string nextLine;
    getline(cin, nextLine);
    while(!cin.eof()) {
        int prev = 0;
        nextLine += " ";
        vector<string> a(0);
        for(int i = 0; i < nextLine.size(); i++){
            if(nextLine[i] == ' '){
                int len = i - prev;
                if(len >= 1){
                    a.push_back(nextLine.substr(prev, len));
                }
                prev = i + 1;
            }
        }
        for(int i = 0; i < a.size(); i++){
            string lower = a[i];
            transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
            if(s.find(lower) == s.end()) {
                cout << a[i] << " ";
                s.insert(lower);
            }
            else {
                cout << ". ";
            }
        }
        cout << "\n";
        getline(cin, nextLine);
    }
    
    return 0;
}

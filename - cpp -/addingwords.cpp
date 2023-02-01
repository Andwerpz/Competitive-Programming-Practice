#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Problem Set 02 A

//my god, this took way too long. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    map<string, int> m;
    map<int, string> rm;
    while(!cin.eof()) {
        string next;
        cin >> next;
        if(next == "def") {
            string var;
            cin >> var;
            int val;
            cin >> val;
            if(m.find(var) != m.end()){
                rm.erase(m.find(var) -> second);
                m.erase(var);
            }
            m.insert({var, val});
            rm.insert({val, var});
        }
        else if(next == "calc") {
            int sum = 0;
            bool isValid = true;
            string sign = "F";
            string var;
            cin >> var;
            if(var == "-") {
                sign = var;
                cin >> var;
            }
            while(true){
                int val = 0;
                if(m.find(var) == m.end()) {
                    isValid = false;
                }
                else {
                    val = m.find(var) -> second;
                }
                if(sign == "-") {
                    val *= -1;
                }
                sum += val;
                if(sign == "F"){
                    cout << var << " ";
                }
                else {
                    cout << sign << " " << var << " ";
                }
                cin >> sign;
                if(sign == "=") {
                    break;
                }
                cin >> var;
            }
            if(rm.find(sum) == rm.end()) {
                isValid = false;
            }
            cout << "= " << (isValid? rm.find(sum) -> second : "unknown") << "\n";
        }
        else if(next == "clear") {
            rm.clear();
            m.clear();
        }
    }
    
    return 0;
}
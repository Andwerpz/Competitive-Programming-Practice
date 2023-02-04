#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//CSCE 430 Spring 2023 - Lab 03 C

//the only hard part about this problem is reading in the input. 

//to make this problem easier, you should just translate all given times to a floating point number of
//hours. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    //get input and convert to hours
    double dist = 0;
    double speed = 0;
    double prevTime = 0;
    vector<string> a(0);
    while(!cin.eof()) {
        string s = "";
        cin >> s;
        if(cin.eof()) {
            break;
        }
        // if(s.length() == 1){
        //     break;
        // }
        a.push_back(s);
    }
    for(int i = 0; i < a.size(); i++) {
        string s = a[i];
        if(s.length() == 8) {
            //time
            double hr = (s[0] - '0') * 10 + (s[1] - '0');
            double min = (s[3] - '0') * 10 + (s[4] - '0');
            double sec = (s[6] - '0') * 10 + (s[7] - '0');
            double curTime = hr + min / 60.0 + sec / 3600.0;
            dist += (curTime - prevTime) * speed;
            prevTime = curTime;
            //cout << hr << " " << min << " " << sec << " " << dist << "\n";
            if(i == a.size() - 1 || a[i + 1].length() == 8) {
                cout << s << " ";
                cout << fixed << setprecision(2) << dist << " km\n";
            }
        }
        else {
            speed = 0;
            for(int j = 0; j < s.length(); j++){
                speed *= 10;
                speed += (s[j] - '0');
            }
        }
    }
    
    return 0;
}

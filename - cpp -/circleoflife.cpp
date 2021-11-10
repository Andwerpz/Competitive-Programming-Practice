
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

//DMOJ - ccc16s5

//7/15, TLE

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, t;
    cin >> n >> t;
    string s;
    cin >> s;
    vector<int> cells(n);
    vector<int> original(n);
    for(int i = 0; i < n; i++){
        cells[i] = s[i] - '0';
        original[i] = cells[i];
    }
    map<string, ll> dict;
    dict.insert({s, 0});
    ll counter = 0;
    ll cycleLength = 0;
    string cycleStart = "";
    bool foundAns = false;
    while(true){
        counter ++;
        vector<int> next(n);
        for(int i = n; i < n * 2; i++){
            //cout << (bool)((cells[(i - 1) % n] == 1) xor (cells[(i + 1) % n] == 1)) << endl;
            if((cells[(i - 1) % n] == 1) xor (cells[(i + 1) % n] == 1)){
                next[i % n] = 1;
            }
            else{
                next[i % n] = 0;
            }
        }
        if(counter == t){
            foundAns = true;
            for(int i = 0; i < n; i++){
                cout << next[i];
            }
            cout << endl;
            break;
        }
        string cur;
        for(int i = 0; i < n; i++){
            cells[i] = next[i];
            cur.append(to_string(next[i]));
            //cout << cells[i] << next[i] << " ";
        }
        if(dict.find(cur) != dict.end()){
            cycleLength = counter - dict.at(cur);
            cycleStart = cur;
            break;
        }
        else{
            dict.insert({cur, counter});
        }
        //cout << endl;
    }
    if(!foundAns){
        //cout << cycleStart << endl;
        t -= counter;
        ll remainder = t % cycleLength;
        //cout << remainder << endl;
        string next;
        for(int i = 0; i < n; i++){
            next.append("0");
        }
        //cout << next << endl;
        for(int i = 0; i < remainder; i++){
            for(int j = 0; j < n; j++){
                next[j] = '0';
                if(j == 0){
                    if((cycleStart[n - 1] == '1') xor (cycleStart[1] == '1')){
                        next[j] = '1';
                    }
                }
                else if(j == n - 1){
                    if((cycleStart[0] == '1') xor (cycleStart[j - 1] == '1')){
                        next[j] = '1';
                    }
                }
                else{
                    if((cycleStart[j - 1] == '1') xor (cycleStart[j + 1] == '1')){
                        next[j] = '1';
                    }
                }
            }
            //cout << next << endl;
            for(int j = 0; j < n; j++){
                cycleStart[j] = next[j];
            }
        }
        cout << next << endl;
    }

    return 0;
}




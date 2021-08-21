
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

typedef long long ll;

using namespace std;

//CSES - Creating Strings

std::set<string> recurse(set<string> cur, vector<int> chars);
std::set<string> getAns(vector<int> chars);

set<string> getAns(vector<int> chars) {
    set<string> ans;
    for(int i = 0; i < chars.size(); i++){
        if(chars[i] != 0){
            vector<int> nextChars(26);
            for(int j = 0; j < chars.size(); j++){
                nextChars[j] = chars[j];
            }
            nextChars[i] --;
            set<string> cur {{((char) (i + 'a'))}};
            //cout << " INPUT" << endl;
            set<string> next = recurse(cur, nextChars);
            for(string s : next){
                //cout << s << " ";
                ans.insert(s);
            }
            //cout << endl;
        }   
    }
    return ans;
}

set<string> recurse(set<string> cur, vector<int> chars) {
    set<string> ans;
    for(int i = 0; i < chars.size(); i++){
        if(chars[i] != 0){
            vector<int> nextChars(26);
            for(int j = 0; j < chars.size(); j++){
                nextChars[j] = chars[j];
            }
            nextChars[i] --;
            set<string> recurseCur;
            for(string s : cur){
                recurseCur.insert(s + ((char) (i + 'a')));
            }
            set<string> next = recurse(recurseCur, nextChars);
            for(string s : next){
                ans.insert(s);
            }
        }   
    }
    if(ans.size() == 0){
        //cout << "RETURN\n";
        return cur;
    }
    return ans;
}

int main() {

    string s;
    cin >> s;
    vector<int> chars(26);
    for(int i = 0; i < s.length(); i++){
        chars[s[i] - 'a'] ++;
    }
    set<string> strings = getAns(chars);
    vector<string> sorted(strings.size());
    int pointer = 0;
    for(string s : strings){
        sorted[pointer] = s;
        pointer ++;
    }
    sort(sorted.begin(), sorted.end());
    cout << sorted.size() << endl;

    for(int i = 0; i < sorted.size(); i++){
        cout << sorted[i] << "\n";
    }

    return 0;
}




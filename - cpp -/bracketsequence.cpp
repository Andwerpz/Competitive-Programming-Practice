#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 224C

//iterate through the brackets, saving the brackets and their indexes in a stack. 

//also save an array of valid segments. 

//every time you complete a segment, greedily combine it with the other segments. 
//as the segments are saved in ascending order, and they should never intersect, 
//you can combine the segments starting from the end of the array, going forwards. 

//come to think of it, it's probably better to save the segments in a stack as well. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;
    cin >> s;
    stack<int> sId;
    stack<char> sC;
    vector<vector<int>> seg(0);
    for(int i = 0; i < s.size(); i++){
        //cout << s[i] << endl;
        char next = s[i]; 
        char top = sC.size() != 0? sC.top() : '#';
        //cout << "TOP : " << top << endl;
        if(next == '(' || next == '['){
            sId.push(i);
            sC.push(next);
        }
        else if(next == ')' && top == '(' || next == ']' && top == '['){
            int l = sId.top();
            int r = i;
            int openS = next == ']'? 1 : 0;
            sC.pop();
            sId.pop();
            //cout << "CUR SEG: " << l << " " << r << endl;
            if(seg.size() != 0 && l <= seg[seg.size() - 1][1] + 1){
                seg[seg.size() - 1][0] = min(seg[seg.size() - 1][0], l);
                seg[seg.size() - 1][1] = max(seg[seg.size() - 1][1], r);
                seg[seg.size() - 1][2] += openS;
                while(seg.size() >= 2 && seg[seg.size() - 1][0] <= seg[seg.size() - 2][1] + 1){
                    //cout << "COMBINE" << endl;
                    seg[seg.size() - 2][0] = min(seg[seg.size() - 2][0], seg[seg.size() - 1][0]);
                    seg[seg.size() - 2][1] = max(seg[seg.size() - 2][1], seg[seg.size() - 1][1]);
                    seg[seg.size() - 2][2] += seg[seg.size() - 1][2];
                    seg.pop_back();
                }
            }
            else{
                seg.push_back({l, r, openS});
            }
            
        }
        else{
            sId = stack<int>();
            sC = stack<char>();
        }
    }
    if(seg.size() == 0){
        cout << "0\n\n";
    }
    else{
        int id = -1;
        int max = -1;
        for(int i = 0; i < seg.size(); i++){
            if(max < seg[i][2]){
                id = i;
                max = seg[i][2];
            }
        }
        int l = seg[id][0];
        int r = seg[id][1];
        cout << (seg[id][2]) << endl;
        for(int i = l; i <= r; i++){
            cout << s[i];
        }
        cout << endl;
    }
    
    return 0;
}

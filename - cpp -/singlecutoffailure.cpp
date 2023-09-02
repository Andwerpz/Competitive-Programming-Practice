#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2018 H

//didn't have the right idea for this one. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, w, h;
    cin >> n >> w >> h;
    //cout << "CREATING ARRAY" << endl;
    vector<vector<int>> wires(n, vector<int>(4));
    for(int i = 0; i < n; i++){
        //cout << "READING STUFF" << endl;
        cin >> wires[i][0] >> wires[i][1] >> wires[i][2] >> wires[i][3];
    }
    //vertical single wire
    bool verticalValid = true;
    {
        int minTop = 0;
        int maxTop = w;
        int minBot = 0;
        int maxBot = w;
        map<int, vector<int>> topm;
        map<int, vector<int>> botm;
        for(int i = 0; i < n; i++){
            int x1 = wires[i][0];
            int y1 = wires[i][1];
            int x2 = wires[i][2];
            int y2 = wires[i][3];
            if(y1 < y2) {
                swap(x1, x2);
                swap(y1, y2);
            }
            //y1 is top
            if(topm.find(x1) == topm.end()) {
                topm.insert({x1, vector<int>(0)});
            }
            topm[x1].push_back(i);
            if(botm.find(x2) == botm.end()) {
                botm.insert({x2, vector<int>(0)});
            }
            botm[x2].push_back(i);
        }
        while(true){
            bool shrunk = false;
            //top left
            while(topm.size() != 0 && topm.begin() -> first <= minTop) {
                vector<int> wireInd = topm.begin() -> second;
                topm.erase(topm.begin());
                for(int i = 0; i < wireInd.size(); i++){
                    int x1 = wires[wireInd[i]][0];
                    int y1 = wires[wireInd[i]][1];
                    int x2 = wires[wireInd[i]][2];
                    int y2 = wires[wireInd[i]][3];
                    if(y1 < y2) {
                        swap(x1, x2);
                        swap(y1, y2);
                    }
                    //y1 is top
                    if((x1 <= minTop && x2 <= minBot) || (x1 >= maxTop && x2 >= maxBot)) {
                        verticalValid = false;
                        continue;
                    }
                    if((x1 <= minTop && x2 >= maxBot) || (x1 >= maxTop && x2 <= minBot)) {
                        continue;
                    }
                    //otherwise, we have to shrink the size
                    maxBot = min(maxBot, x2);
                    shrunk = true;
                }
            }
            //top right
            while(topm.size() != 0 && topm.rbegin() -> first >= maxTop) {
                vector<int> wireInd = topm.rbegin() -> second;
                topm.erase(--topm.end());
                for(int i = 0; i < wireInd.size(); i++){
                    int x1 = wires[wireInd[i]][0];
                    int y1 = wires[wireInd[i]][1];
                    int x2 = wires[wireInd[i]][2];
                    int y2 = wires[wireInd[i]][3];
                    if(y1 < y2) {
                        swap(x1, x2);
                        swap(y1, y2);
                    }
                    //y1 is top
                    if((x1 <= minTop && x2 <= minBot) || (x1 >= maxTop && x2 >= maxBot)) {
                        verticalValid = false;
                        continue;
                    }
                    if((x1 <= minTop && x2 >= maxBot) || (x1 >= maxTop && x2 <= minBot)) {
                        continue;
                    }
                    //otherwise, we have to shrink the size
                    minBot = max(minBot, x2);
                    shrunk = true;
                }
            }
            //bottom left
            while(botm.size() != 0 && botm.begin() -> first <= minBot) {
                vector<int> wireInd = botm.begin() -> second;
                botm.erase(botm.begin());
                for(int i = 0; i < wireInd.size(); i++){
                    int x1 = wires[wireInd[i]][0];
                    int y1 = wires[wireInd[i]][1];
                    int x2 = wires[wireInd[i]][2];
                    int y2 = wires[wireInd[i]][3];
                    if(y1 < y2) {
                        swap(x1, x2);
                        swap(y1, y2);
                    }
                    //y1 is top
                    if((x1 <= minTop && x2 <= minBot) || (x1 >= maxTop && x2 >= maxBot)) {
                        verticalValid = false;
                        continue;
                    }
                    if((x1 <= minTop && x2 >= maxBot) || (x1 >= maxTop && x2 <= minBot)) {
                        continue;
                    }
                    //otherwise, we have to shrink the size
                    maxTop = min(maxTop, x1);
                    shrunk = true;
                }
            }
            //bottom right
            while(botm.size() != 0 && botm.rbegin() -> first >= maxBot) {
                vector<int> wireInd = botm.rbegin() -> second;
                botm.erase(--botm.end());
                for(int i = 0; i < wireInd.size(); i++){
                    int x1 = wires[wireInd[i]][0];
                    int y1 = wires[wireInd[i]][1];
                    int x2 = wires[wireInd[i]][2];
                    int y2 = wires[wireInd[i]][3];
                    if(y1 < y2) {
                        swap(x1, x2);
                        swap(y1, y2);
                    }
                    //y1 is top
                    if((x1 <= minTop && x2 <= minBot) || (x1 >= maxTop && x2 >= maxBot)) {
                        verticalValid = false;
                        continue;
                    }
                    if((x1 <= minTop && x2 >= maxBot) || (x1 >= maxTop && x2 <= minBot)) {
                        continue;
                    }
                    //otherwise, we have to shrink the size
                    minTop = max(minTop, x1);
                    shrunk = true;
                }
            }
            if(!shrunk) {
                break;
            }
        }
        if(verticalValid) {
            cout << "1\n";
            cout << ((ld) maxTop - 0.01) << " " << ((ld) h) << " " << ((ld) minBot + 0.01) << " " << 0 << "\n";
            return 0;
        }
    }
    for(int i = 0; i < n; i++){
        swap(wires[i][0], wires[i][1]);
        swap(wires[i][2], wires[i][3]);
    }
    swap(w, h);
    verticalValid = true;
    {
        int minTop = 0;
        int maxTop = w;
        int minBot = 0;
        int maxBot = w;
        map<int, vector<int>> topm;
        map<int, vector<int>> botm;
        for(int i = 0; i < n; i++){
            int x1 = wires[i][0];
            int y1 = wires[i][1];
            int x2 = wires[i][2];
            int y2 = wires[i][3];
            if(y1 < y2) {
                swap(x1, x2);
                swap(y1, y2);
            }
            //y1 is top
            if(topm.find(x1) == topm.end()) {
                topm.insert({x1, vector<int>(0)});
            }
            topm[x1].push_back(i);
            if(botm.find(x2) == botm.end()) {
                botm.insert({x2, vector<int>(0)});
            }
            botm[x2].push_back(i);
        }
        while(true){
            bool shrunk = false;
            //top left
            while(topm.size() != 0 && topm.begin() -> first <= minTop) {
                vector<int> wireInd = topm.begin() -> second;
                topm.erase(topm.begin());
                for(int i = 0; i < wireInd.size(); i++){
                    int x1 = wires[wireInd[i]][0];
                    int y1 = wires[wireInd[i]][1];
                    int x2 = wires[wireInd[i]][2];
                    int y2 = wires[wireInd[i]][3];
                    if(y1 < y2) {
                        swap(x1, x2);
                        swap(y1, y2);
                    }
                    //y1 is top
                    if((x1 <= minTop && x2 <= minBot) || (x1 >= maxTop && x2 >= maxBot)) {
                        verticalValid = false;
                        continue;
                    }
                    if((x1 <= minTop && x2 >= maxBot) || (x1 >= maxTop && x2 <= minBot)) {
                        continue;
                    }
                    //otherwise, we have to shrink the size
                    maxBot = min(maxBot, x2);
                    shrunk = true;
                }
            }
            //top right
            while(topm.size() != 0 && topm.rbegin() -> first >= maxTop) {
                vector<int> wireInd = topm.rbegin() -> second;
                topm.erase(--topm.end());
                for(int i = 0; i < wireInd.size(); i++){
                    int x1 = wires[wireInd[i]][0];
                    int y1 = wires[wireInd[i]][1];
                    int x2 = wires[wireInd[i]][2];
                    int y2 = wires[wireInd[i]][3];
                    if(y1 < y2) {
                        swap(x1, x2);
                        swap(y1, y2);
                    }
                    //y1 is top
                    if((x1 <= minTop && x2 <= minBot) || (x1 >= maxTop && x2 >= maxBot)) {
                        verticalValid = false;
                        continue;
                    }
                    if((x1 <= minTop && x2 >= maxBot) || (x1 >= maxTop && x2 <= minBot)) {
                        continue;
                    }
                    //otherwise, we have to shrink the size
                    minBot = max(minBot, x2);
                    shrunk = true;
                }
            }
            //bottom left
            while(botm.size() != 0 && botm.begin() -> first <= minBot) {
                vector<int> wireInd = botm.begin() -> second;
                botm.erase(botm.begin());
                for(int i = 0; i < wireInd.size(); i++){
                    int x1 = wires[wireInd[i]][0];
                    int y1 = wires[wireInd[i]][1];
                    int x2 = wires[wireInd[i]][2];
                    int y2 = wires[wireInd[i]][3];
                    if(y1 < y2) {
                        swap(x1, x2);
                        swap(y1, y2);
                    }
                    //y1 is top
                    if((x1 <= minTop && x2 <= minBot) || (x1 >= maxTop && x2 >= maxBot)) {
                        verticalValid = false;
                        continue;
                    }
                    if((x1 <= minTop && x2 >= maxBot) || (x1 >= maxTop && x2 <= minBot)) {
                        continue;
                    }
                    //otherwise, we have to shrink the size
                    maxTop = min(maxTop, x1);
                    shrunk = true;
                }
            }
            //bottom right
            while(botm.size() != 0 && botm.rbegin() -> first >= maxBot) {
                vector<int> wireInd = botm.rbegin() -> second;
                botm.erase(--botm.end());
                for(int i = 0; i < wireInd.size(); i++){
                    int x1 = wires[wireInd[i]][0];
                    int y1 = wires[wireInd[i]][1];
                    int x2 = wires[wireInd[i]][2];
                    int y2 = wires[wireInd[i]][3];
                    if(y1 < y2) {
                        swap(x1, x2);
                        swap(y1, y2);
                    }
                    //y1 is top
                    if((x1 <= minTop && x2 <= minBot) || (x1 >= maxTop && x2 >= maxBot)) {
                        verticalValid = false;
                        continue;
                    }
                    if((x1 <= minTop && x2 >= maxBot) || (x1 >= maxTop && x2 <= minBot)) {
                        continue;
                    }
                    //otherwise, we have to shrink the size
                    minTop = max(minTop, x1);
                    shrunk = true;
                }
            }
            if(!shrunk) {
                break;
            }
        }
        if(verticalValid) {
            ld x1 = maxTop - 0.01;
            ld y1 = h;
            ld x2 = minBot + 0.01;
            ld y2 = 0;
            swap(x1, y1);
            swap(x2, y2);
            cout << "1\n";
            cout << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
            return 0;
        }
    }
    swap(w, h);
    cout << "2\n";
    cout << "0 0.01 " << w << " " << ((ld) h - 0.01) << "\n";
    cout << "0 " << ((ld) h - 0.01) << " " << w << " 0.01\n";
    
    return 0;
}

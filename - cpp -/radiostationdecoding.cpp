#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//OA from unknown company

struct DSU {
    map<int, int> dsu;  //node to parent map
    map<int, char> cmap;
    map<int, int> size;

    DSU() {
        this->dsu = map<int, int>();
        this->cmap = map<int, char>();
        this->size = map<int, int>();
    }

    void add(int seqID, char c) {
        dsu.insert({seqID, seqID});
        cmap.insert({seqID, c});
        size.insert({seqID, 1});
    }

    //finds root of a
    int find(int a) {
        int parent = dsu[a];
        if(parent == a){
            return a;
        }
        int root = find(parent);
        dsu[a] = root;
        return root;
    }

    int getSize(int a) {
        int root = find(a);
        return size.find(a) -> second;
    }

    char getChar(int a) {
        return cmap.find(a) -> second;
    }

    //ret true if updated something
    bool unify(int a, int b) {
        if(dsu.find(a) == dsu.end() || dsu.find(b) == dsu.end()) {
            return false;
        }   

        int ra = find(a);
        int rb = find(b);
        if(ra == rb) {
            return false;
        }
        //dsu[rb] == rb
        dsu[rb] = ra;
        size[ra] += size[rb];
        
        return true;
    }
};

string getMsg(int seqID, int& maxSentID, set<int>& dashes, DSU& dsu) {
    if(dashes.find(seqID) != dashes.end()){
        return string(1, '-');
    }
    if(dashes.size() == 0){
        return string(1, '-');
    }

    int minD = *dashes.begin();
    int maxD = *dashes.rbegin();

    if(minD < seqID && seqID < maxD) {
        auto ptr = dashes.lower_bound(seqID);
        int r = *ptr;
        ptr--;
        int l = *ptr;

        int camt = dsu.getSize(seqID);
        int diff = r - l - 1;
        if(camt == diff && maxSentID < r) {
            //print the message
            string msg(diff, '0');
            for(int i = 0; i < diff; i++){
                msg[i] = dsu.getChar(l + i + 1);
            }
            maxSentID = r;
            return msg;
        }
    }
    
    return string(1, '-');
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    DSU dsu = DSU();
    set<int> dashes;
    int maxSentID = -1;
    while(true) {
        int seqID;
        char c;
        cin >> seqID >> c;
        if(seqID == -1){
            break;
        }
        if(c == '-'){
            dashes.insert(seqID);
        }
        else {
            dsu.add(seqID, c);
            dsu.unify(seqID, seqID - 1);
            dsu.unify(seqID, seqID + 1);
        }

        string msg = getMsg(seqID + 1, maxSentID, dashes, dsu);
        if(msg != "-"){
            cout << "Message Decoded : " << msg << endl;
        }
        msg = getMsg(seqID, maxSentID, dashes, dsu);
        if(msg != "-"){
            cout << "Message Decoded : " << msg << endl;
        }
        msg = getMsg(seqID - 1, maxSentID, dashes, dsu);
        if(msg != "-"){
            cout << "Message Decoded : " << msg << endl;
        }
    }
    
    return 0;
}

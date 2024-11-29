#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream in("--in--.txt");
    streambuf *cinbuf = cin.rdbuf(); //save old buf
    cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!
    
    ofstream out("--out--.txt");
    streambuf *coutbuf = cout.rdbuf(); //save old buf
    cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!

    //seems like usaco likes this one
    freopen("--in--.txt", "r", stdin);
    freopen("--out--.txt", "w", stdout);
}
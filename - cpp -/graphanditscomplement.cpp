#include <iostream>
#include <vector>
using namespace std;

//Codeforces - 990D

//main observation is that for n > 3, min(a, b) has to be 1. The idea is that if the graph is disconnected
//then the complement must be fully connected. 

//we can just construct the disconnected graph, and then take the complement. Hardcode answers for n <= 3. 

int main() {
    int n, a, b;
    cin >> n >> a >> b;

    if (min(a, b) > 1) {
        cout << "NO" << endl;
        return 0;
    }

    if (a == 1 && b == 1) {
        if (n == 2 || n == 3) {
            cout << "NO" << endl;
            return 0;
        }
        cout << "YES" << endl;
        vector<vector<int>> adj(n, vector<int>(n, 0));
        for (int i = 0; i < n - 1; ++i) {
            adj[i][i + 1] = adj[i + 1][i] = 1;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << adj[i][j];
            }
            cout << endl;
        }
        return 0;
    }

    cout << "YES" << endl;
    vector<vector<int>> adj(n, vector<int>(n, 0));
    if (a == 1) {
        for(int i = 0; i < n - b; i++){
            adj[i][i + 1] = 1;
            adj[i + 1][i] = 1;
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(i == j) continue;
                adj[i][j] ^= 1;
            }
        }
    } else {
        for(int i = 0; i < n - a; i++){
            adj[i][i + 1] = 1;
            adj[i + 1][i] = 1;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << adj[i][j];
        }
        cout << endl;
    }

    return 0;
}
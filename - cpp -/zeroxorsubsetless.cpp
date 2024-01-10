#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
using namespace std;

//Codeforces - 1101G

//first, the only case where a partition is impossible is when the entire array xor sums to 0. 
//otherwise it's always possible. 

//if we have a set of xor vectors S, then it's only when all the vectors in S are independent that there 
//doesn't exist a subset of S that xors to 0. 

//next, let's assume that we have a valid partition of a of k segments; A_1, A_2, ..., A_k. If all the vectors
//in our partiton are independent, then they can all be viewed as basis vectors. Then, let's denote P_i as 
//A_1 ^ A_2 ^ ... ^ A_i. The set of vectors P_0, P_1, ..., P_k also have to be independent. 

//then, notice that if we define P_i as the prefix xor sum of the array, then the amount of basis vectors of 
//the set P_1, P_2, ..., P_n, have to be equal to the amount of segments in the optimal partition. 

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    int p = 0;
    int b_cnt = 0;
    vector<int> b(30, -1);
    for(int i = 0; i < n; i++){
        p ^= a[i];
        int tmp = p;
        for(int j = 0; j < 30; j++){
            if((tmp & 1 << j) == 0){
                continue;
            }
            if(b[j] == -1){
                b_cnt ++;
                b[j] = tmp;
                break;
            }
            tmp ^= b[j];
        }
    }
    cout << (p == 0? -1 : b_cnt) << "\n";
    
    return 0;
}

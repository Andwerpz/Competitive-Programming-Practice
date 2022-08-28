#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Meta Hacker Cup 2022 A

//you just have to make sure that the total amount of second hands
//is less than k * 2, and there are no more than 2 of the same style second hand

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ifstream fin("second_hands_input.txt");
    ofstream fout("second_hands_output.txt");
    
    int t;
    fin >> t;
    int caseNum = 1;
    while(t-- > 0){
        int n, k;
        fin >> n >> k;
        vector<int> a(n);
        vector<int> cnt(101);
        for(int i = 0; i < n; i++){
            fin >> a[i];
            cnt[a[i]] ++;
        }
        bool isValid = true;
        if(n > k * 2){
            isValid = false;
        }
        for(int i : cnt){
            if(i > 2){
                isValid = false;
            }
        }
        fout << "Case #" << caseNum << (isValid? ": YES\n" : ": NO\n");
        caseNum ++;
    }
    
    return 0;
}

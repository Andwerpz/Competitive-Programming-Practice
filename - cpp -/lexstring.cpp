#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

//Codeforces - 1689A

//since you want to minimize the lexographic value of c, you can use a greedy strategy. 

//the problem is easy since the same character can't appear in both strings. It removes the case 
//where you need to alternate placing the same character from a and b. 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    cin >> t;
    while(t-- > 0) {
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> a(26);
        vector<int> b(26);
        string next;
        cin >> next;
        int pa = 26;
        int pb = 26;
        for(char c : next){
            a[c - 'a'] ++;
            pa = min(pa, c - 'a');
        }
        cin >> next;
        for(char c : next){
            b[c - 'a'] ++;
            pb = min(pb, c - 'a');
        }
        int count = 0;
        bool placedA = false;
        while(pa != 26 && pb != 26){
            //cout << pa << " " << pb << " ";
            if((pa <= pb && ((placedA && count < k) || !placedA)) || (!placedA && count == k)){
                //cout << "A\n";
                if(!placedA){
                    count = 0;
                    placedA = true;
                }
                count ++;
                a[pa] --;
                cout << (char) (pa + 'a');
                while(a[pa] == 0 && pa < 26){
                    pa ++;
                }
            }
            else{
                //cout << "B\n";
                if(placedA){
                    count = 0;
                    placedA = false;
                }
                count ++;
                b[pb] --;
                cout << (char) (pb + 'a');
                while(b[pb] == 0 && pb < 26){
                    pb ++;
                }
            }
        }
        cout << "\n";
    }
    
    return 0;
}

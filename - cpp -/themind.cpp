#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

//ICPC World Finals 2020 Online M

//interesting constructive probability problem. 

//we only care about the minimum card in a hand. If the minimum card is above 30, then we just don't play it, 
//otherwise, we'll choose to play it on a specific turn based on how low the minimum is; if it is lower, then we'll
//play it earlier. 

ld gen_float() {
    return (rand() % 10000) / 10000.0;
}

vector<ld> gen_prob(int min) {
    vector<ld> prob(5, 0);
    if(min > 30) {
        return prob;
    }
    if(min <= 4) {
        prob[0] = 1;
        return prob;
    }
    if(min <= 9) {
        prob[1] = 1;
        return prob;
    }
    if(min <= 15) {
        prob[2] = 1;
        return prob;
    }
    if(min <= 22) {
        prob[3] = 1;
        return prob;
    }
    if(min <= 30) {
        prob[4] = 1;
        return prob;
    }
    return prob;
}

pair<int, int> gen_hands() {
    vector<int> a(5);
    vector<int> b(5);
    while(true) {
        for(int i = 0; i < 5; i++){
            a[i] = rand() % 100 + 1;
            b[i] = rand() % 100 + 1;
        }
        bool is_valid = true;
        set<int> s;
        for(int i = 0; i < 5; i++){
            if(s.count(a[i])) {
                is_valid = false;
            }
            s.insert(a[i]);
            if(s.count(b[i])) {
                is_valid = false;
            }
            s.insert(b[i]);
        }
        if(is_valid) {
            break;
        }
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return {a[0], b[0]};
}

bool play() {
    pair<int, int> mins = gen_hands();
    int a = mins.first;
    int b = mins.second;
    vector<ld> p_a = gen_prob(a);
    vector<ld> p_b = gen_prob(b);
    for(int i = 0; i < 5; i++){
        bool a_play = false;
        bool b_play = false;
        if(gen_float() < p_a[i]) {
            a_play = true;
        }
        if(gen_float() < p_b[i]) {
            b_play = true;
        }
        if(a_play && b_play) {
            return false;
        }
        if(a_play || b_play) {
            if(a_play && a > b) {
                return false;
            }
            if(b_play && b > a) {
                return false;
            }
            return true;
        }
    }
    return false;
}

void run_tests() {
    srand(chrono::steady_clock::now().time_since_epoch().count());
    int tot = 100000;
    int wins = 0;
    for(int i = 0; i < tot; i++){
        wins += play();
    }
    cout << wins << "/" << tot << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        vector<int> a(5);
        for(int j = 0; j < 5; j++){
            cin >> a[j];
        }
        vector<ld> prob = gen_prob(a[0]);
        for(int j = 0; j < 5; j++){
            cout << prob[j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}

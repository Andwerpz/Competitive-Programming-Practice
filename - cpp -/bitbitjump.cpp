#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<bool> vb;
typedef vector<ld> vd;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvl;
typedef vector<vector<bool>> vvb;
typedef vector<vector<ld>> vvd;
// typedef __int128 lll;
// typedef __float128 lld;

//2024-2025 ICPC NERC - B

//implementation practice lol

//we can implement an if statement based off of bit value by using the a -> b copy and setting the 
//target of the copy to a bit in the c address

//idea is to do a bunch of branching if statements, one branch for each bit in x. 
//terminate as soon as you find a wrong bit. 

vi a((1 << 12), 0);

void set_bit(int bit_ptr, bool val) {
    int byte_ind = bit_ptr / 16;
    int bit_ind = bit_ptr % 16;
    if(a[byte_ind] & (1 << bit_ind)) a[byte_ind] ^= (1 << bit_ind);
    if(val) a[byte_ind] ^= (1 << bit_ind);
}

void set_byte(int byte_ptr, int val) {
    a[byte_ptr] = val;
}

string byte_to_hex(int byte) {
    string ret(4, ' ');
    for(int i = 0; i < 4; i++){
        int rem = (byte >> (12 - i * 4)) % 16;
        if(rem < 10) ret[i] = '0' + rem;
        else ret[i] = 'a' + (rem - 10);
    }
    return ret;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int x;
    cin >> x;
    int IO_BIT = (1 << 16) - 16;
    int TERMINATE_IP = (1 << 12);
    int ON_BIT = (1 << 16) - 32;
    int OFF_BIT = (1 << 16) - 31;
    set_bit(ON_BIT, true);
    vvi cmd_ip(17, vi(2)); //{continue, terminate}
    for(int i = 0; i <= 16; i++){
        cmd_ip[i][0] = (i * 8) + 0;
        cmd_ip[i][1] = (i * 8) + 4;
        if(i != 0 && x & (1 << (i - 1))) swap(cmd_ip[i][0], cmd_ip[i][1]);
    }
    for(int i = 0; i < 16; i++){
        int continue_loc = cmd_ip[i][0];
        int terminate_loc = cmd_ip[i][1];
        set_byte(continue_loc + 0, IO_BIT + i);
        set_byte(continue_loc + 1, (continue_loc + 2) * 16 + 2);
        set_byte(continue_loc + 2, cmd_ip[i + 1][0]);
        set_byte(terminate_loc + 0, OFF_BIT);
        set_byte(terminate_loc + 1, IO_BIT);
        set_byte(terminate_loc + 2, TERMINATE_IP);
    }
    set_byte(cmd_ip[16][0] + 0, ON_BIT);
    set_byte(cmd_ip[16][0] + 1, IO_BIT);
    set_byte(cmd_ip[16][0] + 2, TERMINATE_IP);
    set_byte(cmd_ip[16][1] + 0, OFF_BIT);
    set_byte(cmd_ip[16][1] + 1, IO_BIT);
    set_byte(cmd_ip[16][1] + 2, TERMINATE_IP);
    for(int i = 0; i < a.size() - 1; i++){
        cout << byte_to_hex(a[i]);
        cout << ((i + 1) % 8 == 0? "\n" : " ");
    }
    cout << "\n";
    
    return 0;
}
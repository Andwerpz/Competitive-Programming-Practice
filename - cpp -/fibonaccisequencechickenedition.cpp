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

//17th Zhejiang University Programming Contest - E
//ZOJ 3592

//open ended constructive problem. I'll discuss my strat

//my initial idea was to write a loop that would first check if the counter is 0, before incrementing the stored fibonacci
//value. We can derive some simple operations like rm (remove top element from stack), copy(a, b) (copy element at stack[a] 
//to stack[b]), and jmp(a) (jump to position a in the pogram). The issue is that each iteration of the loop required 
//around 50 operations, so that would go over the limit. 

//my fix was to just have special cases for n <= 14, hardcoding the results. Since the limit on the number of 'c's was 
//pretty generous, we could trade 'c's for saved operations, and then run the remaining 15 iterations when n > 14.

//looking at the editorial, probably a much easier solution is to copy paste code for computing the next fibonacci value 
//30 times, and then reading in n and using it to index into the stack. This way we don't have to keep track of any 
//loop variable, and can probably make the initial computation phase 25ish operations per iteration. 


//1 : cntr
//2 : f(n)
//3 : f(n + 1)

//1 : f(n)
//2 : f(n + 1)
//3 : cntr

/*
rm:
push 1
add
push 0
compare
add

copy(a, b):
push a
push b
copy

jmp(a):
push 1
push a
jump

check0:
push 0
copy(1, 4)
push 0
compare
push (rm addr)
jump


incf:
push 0
copy(2, 4)
push 0
copy(3, 5)
add
copy(3, 2)
copy(4, 3)
rm

load
push 0
push 1
check0
incf
jmp(4)
rm

check0 = 8
incf = 13

load
push 0
push 1
# check0 start
push 0
# copy(1, 4) start
push 1
push 4
copy
push 0
compare
push (rm addr)
jump
# incf start
push 0
# copy(2, 4) start
push 2
push 4
copy
push 0
# copy(3, 5) start
push 3
push 5
copy
add
# copy(3, 2) start
push 3
push 2
copy
# copy(4, 3) start
push 4
push 3
copy
# rm start
push 1
add
push 0
compare
add
# jmp(4) start
push 1
push 4
jump
# rm start
push 1
add
push 0
compare
add
*/

void emit_add() {
    cout << "c\n";
}

void emit_sub() {
    cout << "cc\n";
}

void emit_compare() {
    cout << "ccc\n";
}

void emit_load() {
    cout << "cccc\n";
}

void emit_copy() {
    cout << "ccccc\n";
}

void emit_jump() {
    cout << "cccccc\n";
}

void emit_push(int x) {
    cout << "ccccccc";
    for(int i = 0; i < x; i++) cout << "c";
    cout << "\n";
}

void emit_push_comment(int x) {
    cout << "ccccccc";
    for(int i = 0; i < x; i++) cout << "c";
    cout << " # push " << x << "\n";
}

void emit_rm() {
    emit_push(1);
    emit_add();
    emit_push(0);
    emit_compare();
    emit_add();
}

void emit_copy_ab(int a, int b) {
    emit_push(a);
    emit_push(b);
    emit_copy();
}

void emit_jump_a(int a) {
    emit_push(1);
    emit_push(a);
    emit_jump();
}

void emit_check_low(int low) {
    emit_push(0);
    emit_copy_ab(1, 4);
    emit_push(low);
    emit_compare();
    emit_push(4);
    emit_jump();
    emit_push(1);
    emit_push(0);
    emit_copy_ab(1, 5);
    emit_sub();
    emit_copy_ab(4, 1);
    emit_rm();
}

void emit_je(int val, int addr) {
    emit_push(val);
    emit_compare();
    emit_push(addr);
    emit_jump();
}

void emit_jne_ctr(int val, int addr) {
    // emit_push_comment(val);
    emit_push(val);
    emit_push(0);
    emit_copy_ab(1, 3);
    emit_sub();
    emit_push(addr);
    emit_jump();
}

void emit_incf() {
    emit_push(0);
    emit_copy_ab(2, 4);
    emit_push(0);
    emit_copy_ab(3, 5);
    emit_add();
    emit_copy_ab(3, 2);
    emit_copy_ab(4, 3);
    emit_rm();
}

void emit_program() {
    //jump to load
    emit_push(1);
    emit_push(7);
    emit_jump();

    //exits the program
    emit_push(1);
    emit_push(1000);
    emit_jump();

    //true program start
    emit_load();

    //low fib shortcuts
    int low = 14;
    vl f(low + 3);
    f[1] = 1, f[2] = 1;
    for(int i = 3; i <= low + 2; i++){
        f[i] = f[i - 1] + f[i - 2];
    }
    for(int i = 1; i <= low; i++){
        emit_jne_ctr(i, 8 + 12 * i);
        emit_push(f[i]);
        emit_jump_a(4);
    }

    //rest of fib
    // emit_push_comment(f[low - 1]);
    emit_push(f[low - 1]);
    emit_push(f[low]);
    emit_check_low(low);
    emit_incf();
    emit_jump_a(8 + 12 * low + 2);
    emit_rm();
}

void checker() {
    vl program;
    int psum = 0;
    program.push_back(-1);
    while(true) {
        string line;
        cin >> line;
        if(line == "done") break;
        program.push_back(line.size());
        psum += line.size();
    }
    cout << "PSUM : " << psum << "\n";
    int pc = 1;
    int cntr = 0;
    vl s(1, -1);
    while(true) {
        cntr ++;
        if(cntr > 1000) {
            cout << "Program exceeded 1000 operations\n";
            break;
        }
        if(pc >= program.size()) {
            if(s.size() <= 1) {
                cout << "Program ended but stack empty\n";
            }
            else {
                cout << "Program ended : " << *(s.rbegin()) << "\n";
                cout << "CNT : " << cntr << "\n";
            }
            break;
        }
        int opcode = program[pc];
        cout << "PC : " << pc << endl;
        if(opcode == 1){
            if(s.size() <= 2) {
                cout << "ADD : empty stack\n";
                break;
            }
            ll x = *(s.rbegin());
            s.pop_back();
            ll y = *(s.rbegin());
            s.pop_back();
            s.push_back(x + y);
            cout << "ADD : " << x << " " << y << "\n";
            pc ++;
        }
        else if(opcode == 2){
            if(s.size() <= 2) {
                cout << "SUB : empty stack\n";
                break;
            }
            ll x = *(s.rbegin());
            s.pop_back();
            ll y = *(s.rbegin());
            s.pop_back();
            s.push_back(x - y);
            cout << "SUB : " << x << " " << y << "\n";
            pc ++;
        }
        else if(opcode == 3){
            if(s.size() <= 2) {
                cout << "CMP : empty stack\n";
                break;
            }
            ll x = *(s.rbegin());
            s.pop_back();
            ll y = *(s.rbegin());
            s.pop_back();
            s.push_back(x == y);
            cout << "CMP : " << x << " " << y << "\n";
            pc ++;
        }
        else if(opcode == 4){
            ll x;
            cin >> x;
            s.push_back(x);
            cout << "LOAD : " << x << "\n";
            pc ++;
        }
        else if(opcode == 5){
            if(s.size() <= 2) {
                cout << "COPY : empty stack\n";
                break;
            }
            ll x = *(s.rbegin());
            s.pop_back();
            ll y = *(s.rbegin());
            s.pop_back();
            if(x < 1 || x >= s.size()) {
                cout << "COPY : x out of range (" << x << ")\n";
                break;
            }
            if(y < 1 || y >= s.size()) {
                cout << "COPY : y out of range (" << y << ")\n";
                break;
            }
            cout << "COPY : " << y << " " << x << " " << s[y] << " " << s[x] << "\n";
            s[x] = s[y];
            pc ++;
        }   
        else if(opcode == 6){
            if(s.size() <= 2) {
                cout << "JUMP : empty stack\n";
                break;
            }
            ll x = *(s.rbegin());
            s.pop_back();
            ll y = *(s.rbegin());
            s.pop_back();
            if(x <= 0) {
                cout << "JUMP : x is not positive integer\n";
                break;
            }
            if(y != 0) {
                cout << "JUMP TO : " << x << "\n";
                pc = x;
            }
            else {
                pc ++;
            }
        }
        else if(opcode >= 7) {
            ll x = opcode - 7;
            s.push_back(x);
            cout << "PUSH BACK : " << x << "\n";
            pc ++;
        }
        else {
            cout << "Undefined opcode : " << opcode << "\n";
            break;
        }
        for(int i = 1; i < s.size(); i++) cout << s[i] << " ";
        cout << "\n";
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    emit_program();
    // checker();
    
    return 0;
}
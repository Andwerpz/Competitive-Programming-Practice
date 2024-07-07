#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
// typedef __int128 lll;
// typedef __float128 lld;
using namespace std;

//it works, but it's very memory intensive. Would not recommend using.

template <typename T>
struct SegtreeSparse {
    struct TreeNode {
        bool is_empty = true;
        int sz;
        SegtreeSparse* segt;
        T val;
        TreeNode* c[2];

        TreeNode() {};
        TreeNode(int _sz, SegtreeSparse* _segt) {
            sz = _sz;
            segt = _segt;
            val = segt->uneut;
            c[0] = nullptr;
            c[1] = nullptr;
        }

        void modify(int ind, T val) {
            if(sz == 1){
                this->val = segt->fmodify(this->val, val);
                is_empty = false;
                return;
            }
            if(is_empty) {
                c[0] = new TreeNode(sz / 2, segt);
                c[1] = new TreeNode(sz / 2, segt);
                is_empty = false;
            }
            int cind = ind >= sz / 2;
            c[cind]->modify(ind % (sz / 2), val);
            this->val = segt->fcombine(c[0]->val, c[1]->val);
        }

        T query(int l, int r) {
            if(r <= l) {
                return segt->qneut;
            }
            if((l == 0 && r == sz) || is_empty) {
                return val;
            }
            int csize = sz / 2;
            T ans = segt->fcombine(c[0]->query(l, min(csize, r)), c[1]->query(max(0, l - csize), r - csize));
            return ans;
        }
    };

    int n;
    function<T(T, T)> fmodify, fcombine;
    T uneut, qneut;
    TreeNode root;

    SegtreeSparse() {}
    SegtreeSparse(int _n, T updateNeutral, T queryNeutral, function<T(T, T)> fmodify, function<T(T, T)> fcombine) {
        n = __builtin_popcount(_n) == 1? _n : (1 << (32 - __builtin_clz(_n)));
        uneut = updateNeutral;
        qneut = queryNeutral;
        this->fmodify = fmodify;
        this->fcombine = fcombine;
        root = TreeNode(n, this);
    }

    void modify(int ind, T val) {
        root.modify(ind, val);
    }

    T query(int l, int r) {
        return root.query(l, r);
    }

    T query(int ind) {
        return query(ind, ind + 1);
    }

};

template <typename T>
struct SegtreeSparse2D {
    struct TreeNode {
        bool is_empty = true;
        int sz; //size along the y dimension
        SegtreeSparse2D* segt;
        SegtreeSparse<T>* val;
        TreeNode* c[2];

        TreeNode() {}
        TreeNode(int _sz, SegtreeSparse2D* _segt) {
            sz = _sz;
            segt = _segt;
            //if this isn't the base data, we want to use assignment modify. 
            function<T(T, T)> fassign = [](const T src, const T val) -> T{return val;};
            val = new SegtreeSparse<T>(segt->n, segt->uneut, segt->qneut, sz == 1? segt->fmodify : fassign, segt->fcombine);
            c[0] = nullptr;
            c[1] = nullptr;
        }

        void modify(int x, int y, T val) {
            if(sz == 1){
                this->val->modify(x, val);
                is_empty = false;
                return;
            }
            if(is_empty) {
                c[0] = new TreeNode(sz / 2, segt);
                c[1] = new TreeNode(sz / 2, segt);
                is_empty = false;
            }
            int cind = y >= sz / 2;
            c[cind]->modify(x, y % (sz / 2), val);
            this->val->modify(x, segt->fcombine(c[0]->val->query(x), c[1]->val->query(x)));
        }

        T query(int x0, int x1, int y0, int y1) {
            if(y1 <= y0) {
                return segt->qneut;
            }
            if(is_empty) {
                return segt->uneut;
            }
            if(y0 == 0 && y1 == sz) {
                return val->query(x0, x1);
            }
            int csize = sz / 2;
            T ans = segt->fcombine(c[0]->query(x0, x1, y0, min(csize, y1)), c[1]->query(x0, x1, max(y0 - csize, 0), y1 - csize));
            return ans;
        }   
    };

    int n;
    function<T(T, T)> fmodify, fcombine;
    T uneut, qneut;
    TreeNode root;

    SegtreeSparse2D(int _n, T updateNeutral, T queryNeutral, function<T(T, T)> fmodify, function<T(T, T)> fcombine) {
        n = __builtin_popcount(_n) == 1? _n : (1 << (32 - __builtin_clz(_n)));
        uneut = updateNeutral;
        qneut = queryNeutral;
        this->fmodify = fmodify;
        this->fcombine = fcombine;
        root = TreeNode(n, this);
    }

    void modify(int x, int y, T val) {
        return root.modify(x, y, val);
    }

    T query(int x0, int x1, int y0, int y1) {
        return root.query(x0, x1, y0, y1);
    }

    T query(int x, int y) {
        return query(x, x + 1, y, y + 1);
    }
};
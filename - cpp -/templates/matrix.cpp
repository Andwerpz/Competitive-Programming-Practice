#include <bits/stdc++.h>
using namespace std;

//VERY WIP, don't use without some testing. 

template <typename T>
struct matrix {
    int n, m;
    vector<vector<T>> mat;
    matrix(int _n, int _m) {n = _n, m = _m; mat = vector(n, vector<T>(m, 0));}
    matrix(const matrix& other) {n = other.n, m = other.m, mat = other.mat;}
    vector<T>& operator [](size_t i) {return mat[i];};
    bool operator ==(const matrix& other) const {
        if(n != other.n || m != other.m) return false;
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) if(*this[i][j] != other[i][j]) return false;
        return true;
    }
    matrix<T>& operator +=(const matrix& other) {
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) *this[i][j] += other[i][j];
        return *this;
    }
    matrix<T> operator +(const matrix& other) const {matrix<T> ret(*this); ret += other; return ret;}
    matrix<T>& operator -=(const matrix& other) {
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) *this[i][j] -= other[i][j];
        return *this;
    }
    matrix<T> operator -(const matrix& other) const {matrix<T> ret(*this); ret -= other; return ret;}
    matrix<T>& operator *=(const T& other) {
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) *this[i][j] *= other;
        return *this;
    }
    matrix<T> operator *(const T& other) const {matrix<T> ret(*this); ret *= other; return ret;}
    matrix<T>& operator /=(const T& other) {
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) *this[i][j] /= other;
        return *this;
    }
    matrix<T> operator /(const T& other) const {matrix<T> ret(*this); ret /= other; return ret;}

    bool to_upper_triangular() {
        for(int i = 0; i < n; ++i) {
            // Pivot element (ensure it's non-zero)
            if(mat[i][i] == 0) {
                bool pivot_found = false;
                for(int k = i + 1; k < n; ++k) {
                    if(mat[k][i] != 0) {
                        swap(mat[i], mat[k]);
                        pivot_found = true;
                        break;
                    }
                }
                if(!pivot_found) return false;
            }
            // Eliminate all elements below the pivot
            for (int j = i + 1; j < n; ++j) {
                T factor = mat[j][i] / mat[i][i];
                for (int k = i; k < m; ++k) {
                    mat[j][k] -= factor * mat[i][k];
                }
            }
        }
        return true;
    }

    T determinant() {
        assert(n == m);
        matrix tmp(*this);
        if(!tmp.to_upper_triangular()) return 0;
        T ans = 1;
        for(int i = 0; i < n; i++) ans *= tmp[i][i];
        return ans;
    }
};
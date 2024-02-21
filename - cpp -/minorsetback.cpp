#include <bits/stdc++.h>
typedef long long ll;
typedef __int128 lll;
typedef long double ld;
typedef __float128 lld;
using namespace std;

//2018 South Central USA Regional - B

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n; cin >>  n;

    vector<long double> a(n);
    for (auto& x : a) cin >> x;

    ld twelve = pow(2, 1 / (ld)12);

    // cerr << "twelve : " << twelve << endl;

    long double freq = 440;

    vector<ld> freqs;

    map<ld, int> f2idx;

    while (freq >= 20) {
        ld cp = freq;
        for (int i = 0; i < 12; ++i) {
            // cerr << "cp : " << cp << endl;
            freqs.push_back(cp);
            f2idx[cp] = i;
            cp *= twelve;
            
        }
        freq /= 2;
        // cerr << "freq : " << freq << endl;
    }

    // cerr << "hey" << endl;

    freq = 440;
    while (freq <= 4000) {
        ld cp = freq;
        for (int i = 0; i < 12; ++i) {
            freqs.push_back(cp);
            f2idx[cp] = i;
            cp *= twelve;
            
        }
        freq *= 2;
    }

    sort(begin(freqs), end(freqs));

    // for (auto x : freqs) cerr << x << " ";
    // cerr << endl;

    vector<string> major_keys = {"G major", "C major", "Eb major", "F# minor", "G minor"};

    map<string, set<int>> mjkeys2idxs;
    map<pair<string, int>, string> keyidx2note;
    mjkeys2idxs["G major"].insert(10);
    mjkeys2idxs["G major"].insert(0);
    mjkeys2idxs["G major"].insert(2);
    mjkeys2idxs["G major"].insert(3);
    mjkeys2idxs["G major"].insert(5);
    mjkeys2idxs["G major"].insert(7);
    mjkeys2idxs["G major"].insert(9);

    keyidx2note[make_pair("G major", 10)] = "G";
    keyidx2note[make_pair("G major", 0)] = "A";
    keyidx2note[make_pair("G major", 2)] = "B";
    keyidx2note[make_pair("G major", 3)] = "C";
    keyidx2note[make_pair("G major", 5)] = "D";
    keyidx2note[make_pair("G major", 7)] = "E";
    keyidx2note[make_pair("G major", 9)] = "F#";



    mjkeys2idxs["C major"].insert(3);
    mjkeys2idxs["C major"].insert(5);
    mjkeys2idxs["C major"].insert(7);
    mjkeys2idxs["C major"].insert(8);
    mjkeys2idxs["C major"].insert(10);
    mjkeys2idxs["C major"].insert(0);
    mjkeys2idxs["C major"].insert(2);

    keyidx2note[make_pair("C major", 3)] = "C";
    keyidx2note[make_pair("C major", 5)] = "D";
    keyidx2note[make_pair("C major", 7)] = "E";
    keyidx2note[make_pair("C major", 8)] = "F";
    keyidx2note[make_pair("C major", 10)] = "G";
    keyidx2note[make_pair("C major", 0)] = "A";
    keyidx2note[make_pair("C major", 2)] = "B";

    
    mjkeys2idxs["Eb major"].insert(6);
    mjkeys2idxs["Eb major"].insert(8);
    mjkeys2idxs["Eb major"].insert(10);
    mjkeys2idxs["Eb major"].insert(11);
    mjkeys2idxs["Eb major"].insert(1);
    mjkeys2idxs["Eb major"].insert(3);
    mjkeys2idxs["Eb major"].insert(5);

    keyidx2note[make_pair("Eb major", 6)] = "Eb";
    keyidx2note[make_pair("Eb major", 8)] = "F";
    keyidx2note[make_pair("Eb major", 10)] = "G";
    keyidx2note[make_pair("Eb major", 11)] = "Ab";
    keyidx2note[make_pair("Eb major", 1)] = "Bb";
    keyidx2note[make_pair("Eb major", 3)] = "C";
    keyidx2note[make_pair("Eb major", 5)] = "D";
    
    mjkeys2idxs["F# minor"].insert(9);
    mjkeys2idxs["F# minor"].insert(11);
    mjkeys2idxs["F# minor"].insert(0);
    mjkeys2idxs["F# minor"].insert(2);
    mjkeys2idxs["F# minor"].insert(4);
    mjkeys2idxs["F# minor"].insert(5);
    mjkeys2idxs["F# minor"].insert(7);

    keyidx2note[make_pair("F# minor", 9)] = "F#";
    keyidx2note[make_pair("F# minor", 11)] = "G#";
    keyidx2note[make_pair("F# minor", 0)] = "A";
    keyidx2note[make_pair("F# minor", 2)] = "B";
    keyidx2note[make_pair("F# minor", 4)] = "C#";
    keyidx2note[make_pair("F# minor", 5)] = "D";
    keyidx2note[make_pair("F# minor", 7)] = "E";
    
    mjkeys2idxs["G minor"].insert(10);
    mjkeys2idxs["G minor"].insert(0);
    mjkeys2idxs["G minor"].insert(1);
    mjkeys2idxs["G minor"].insert(3);
    mjkeys2idxs["G minor"].insert(5);
    mjkeys2idxs["G minor"].insert(6);
    mjkeys2idxs["G minor"].insert(8);

    keyidx2note[make_pair("G minor", 10)] = "G";
    keyidx2note[make_pair("G minor", 0)] = "A";
    keyidx2note[make_pair("G minor", 1)] = "Bb";
    keyidx2note[make_pair("G minor", 3)] = "C";
    keyidx2note[make_pair("G minor", 5)] = "D";
    keyidx2note[make_pair("G minor", 6)] = "Eb";
    keyidx2note[make_pair("G minor", 8)] = "F";


    // cerr << freqs.size() << endl;
    bool works = true;
    string major_key = "";
    vector<string> ans;
    vector<int> freq_idxs;
    for (int i = 0; i < n; ++i) {
        // find index of freq
        int idx = -1;
        for (auto f : freqs) {
            if (abs(f - a[i]) < 1e-4) {
                idx = f2idx[f];
                break;
            }
        }
        if (idx == -1) {
            works = false;
            break;
        }
        freq_idxs.push_back(idx);
    }

    // for (auto ff : freq_idxs) {
    //     cerr << "f : " << ff << endl;
    // }
    // cerr << endl;

    
    int fit = 0;
    for (auto key : major_keys) {
        bool local_works = true;
        for (auto ff : freq_idxs) {
            if (!mjkeys2idxs[key].count(ff)) {
                local_works = false;
            }
        }
        if (local_works) {
            fit++;
            major_key = key;
        }
    }

    if (fit != 1) works = false;

    if (works) {
        cout << major_key << endl;
        for (auto ff : freq_idxs) {
            ans.push_back(keyidx2note[make_pair(major_key, ff)]);
        }
        for (auto s : ans) {
            cout << s << "\n";
        }
        cout << endl;
    } else {
        cout << "cannot determine key" << endl;
    }
    
    return 0;
}

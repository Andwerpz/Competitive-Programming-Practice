#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

void solve()
{
    int numPrizes;
    int totalStickers;
    cin >> numPrizes >> totalStickers;

    unordered_map<int, vector<int>> prizes;
    for (int i = 0; i < numPrizes; i++)
    {
        int numStickers;
        cin >> numStickers;
        vector<int> currStickers;
        for (int j = 0; j < numStickers; j++)
        {
            int sticker;
            cin >> sticker;
            currStickers.push_back(sticker);
        }
        int prize;
        cin >> prize;
        prizes[prize] = currStickers;
    }

    vector<int> stickers(totalStickers);
    for (int i = 0; i < totalStickers; i++)
    {
        int currStickers;
        cin >> currStickers;
        stickers[i] = currStickers;
    }

    int total = 0;
    for (auto &[prize, stickerList] : prizes)
    {
        int low = *max_element(stickers.begin(), stickers.end());
        for (int sticker : stickerList){
            if (stickers[sticker-1] < low){
                low = stickers[sticker - 1];
            }
        }
        cout << "LOW : " << low << "\n";
        total += low * prize;
    }
    cout << total << endl;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int casi;
    cin >> casi;
    while (casi-- > 0)
        solve();

    return 0;
}
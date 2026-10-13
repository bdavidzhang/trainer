#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const ull MOD = (1ULL << 61) - 1;
static ull mulmod(ull a, ull b) {
    __uint128_t t = (__uint128_t)a * b;
    ull r = (ull)(t & MOD) + (ull)(t >> 61);
    return r >= MOD ? r - MOD : r;
}
static char buf[100005];
int n;
string s;
vector<ull> H, PW;
ull BASE;
static ull getH(int l, int len) { // hash of s[l, l+len)
    ull r = H[l + len] + MOD - mulmod(H[l], PW[len]);
    return r >= MOD ? r - MOD : r;
}
// is suffix at i greater than suffix at j
static bool greaterSuf(int i, int j) {
    if (i == j) return false;
    int mx = n - max(i, j), lo = 0, hi = mx;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (getH(i, mid) == getH(j, mid)) lo = mid; else hi = mid - 1;
    }
    if (lo == mx) return i < j; // longer one is greater
    return s[i + lo] > s[j + lo];
}
int main() {
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    BASE = rng() % (MOD - 1000) + 500;
    int T;
    scanf("%d", &T);
    string out;
    while (T--) {
        int k;
        scanf("%d %s", &k, buf);
        s = buf; n = s.size();
        int pos = 0;
        while (pos < n) {
            if (k == 0) { out.append(s, pos, string::npos); break; }
            char z = *max_element(s.begin() + pos, s.end());
            vector<pair<int,int>> runs; // start, len
            int total = 0;
            for (int i = pos; i < n;) {
                if (s[i] != z) { i++; continue; }
                int j = i;
                while (j < n && s[j] == z) j++;
                runs.push_back({i, j - i}); total += j - i;
                i = j;
            }
            int fr = runs[0].first == pos ? 1 : 0;
            int cost = (int)runs.size() - fr;
            if (cost <= k) {
                out.append(total, z);
                k -= cost;
                pos = runs.back().first + runs.back().second;
                continue;
            }
            // choose k of runs[fr..], maximise total length, then the suffix after the last chosen run
            int cnt = fr ? runs[0].second : 0;
            vector<int> lens;
            for (size_t i = fr; i < runs.size(); i++) lens.push_back(runs[i].second);
            sort(lens.begin(), lens.end(), greater<int>());
            int L = lens[k - 1], F = 0;
            for (int i = 0; i < k; i++) cnt += lens[i];
            for (int x : lens) if (x > L) F++;
            int q = k - F; // number of runs of length exactly L to take, q >= 1
            int lastForced = -1;
            for (size_t i = fr; i < runs.size(); i++) if (runs[i].second > L) lastForced = i;
            vector<int> cand;
            int tiedBefore = 0;
            for (size_t i = fr; i < runs.size(); i++) {
                if ((int)i == lastForced) { if (tiedBefore >= q) cand.push_back(runs[i].first + runs[i].second); }
                else if (runs[i].second == L) {
                    if ((int)i > lastForced && tiedBefore >= q - 1) cand.push_back(runs[i].first + runs[i].second);
                    tiedBefore++;
                }
            }
            int best = cand[0];
            if (cand.size() > 1) {
                H.assign(n + 1, 0); PW.assign(n + 1, 1);
                for (int i = 0; i < n; i++) {
                    H[i + 1] = mulmod(H[i], BASE) + (ull)(s[i] - 'a' + 1);
                    if (H[i + 1] >= MOD) H[i + 1] -= MOD;
                    PW[i + 1] = mulmod(PW[i], BASE);
                }
                for (size_t i = 1; i < cand.size(); i++) if (greaterSuf(cand[i], best)) best = cand[i];
            }
            out.append(cnt, z);
            out.append(s, best, string::npos);
            break;
        }
        out += '\n';
    }
    fputs(out.c_str(), stdout);
}

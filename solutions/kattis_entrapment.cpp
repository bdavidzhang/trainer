#include <bits/stdc++.h>
using namespace std;
// The Runner may cheat, so the game is played on knowledge states:
// (available mask A, set S of squares the Runner could be in, rounds left r).
// A query splits S into T and S\T (the Runner picks a non-empty side), the Trapper
// removes a square, then S becomes the available neighbours of the chosen side.
// 3^9 (A,S) pairs x 9 rounds: solve exhaustively with memoisation, then play it out.
int nbm[9];
static signed char memo[512][512][10];
int NB(int X) { int r = 0; for (int i = 0; i < 9; i++) if (X >> i & 1) r |= nbm[i]; return r; }
bool TW(int A, int S, int r);
// returns square i with which the Trapper wins after the Runner committed to X, or -1
int killSq(int A, int X, int r) {
    int nb = NB(X);
    for (int i = 0; i < 9; i++) if (A >> i & 1) {
        int A2 = A ^ (1 << i), S2 = nb & A2;
        if (S2 == 0) return i;
    }
    for (int i = 0; i < 9; i++) if (A >> i & 1) {
        int A2 = A ^ (1 << i), S2 = nb & A2;
        if (TW(A2, S2, r - 1)) return i;
    }
    return -1;
}
// query subset T of S that wins for the Trapper, or -1
int winQuery(int A, int S, int r) {
    for (int T = S;; T = (T - 1) & S) {
        int X1 = T, X2 = S ^ T;
        bool ok = true;
        if (X1 && killSq(A, X1, r) < 0) ok = false;
        if (ok && X2 && killSq(A, X2, r) < 0) ok = false;
        if (ok) return T;
        if (T == 0) break;
    }
    return -1;
}
bool TW(int A, int S, int r) {
    if (S == 0) return true;
    if (r == 0) return false;
    signed char &m = memo[A][S][r];
    if (m != -1) return m;
    m = winQuery(A, S, r) >= 0;
    return m;
}
int main() {
    memset(memo, -1, sizeof memo);
    for (int i = 0; i < 9; i++) {
        int r = i / 3, c = i % 3;
        if (r > 0) nbm[i] |= 1 << (i - 3);
        if (r < 2) nbm[i] |= 1 << (i + 3);
        if (c > 0) nbm[i] |= 1 << (i - 1);
        if (c < 2) nbm[i] |= 1 << (i + 1);
    }
    int R, U;
    if (scanf("%d %d", &R, &U) != 2) return 0;
    int A = 511;
    for (int i = 0; i < U; i++) { int s; scanf("%d", &s); A &= ~(1 << (s - 1)); }
    int S = A;
    if (TW(A, S, R)) {
        printf("Trapper\n"); fflush(stdout);
        for (int r = R; r >= 1; r--) {
            int T = winQuery(A, S, r);
            if (T < 0) T = 0;
            printf("%d\n", __builtin_popcount(T));
            if (T) {
                bool f = true;
                for (int i = 0; i < 9; i++) if (T >> i & 1) { printf(f ? "%d" : " %d", i + 1); f = false; }
                printf("\n");
            }
            fflush(stdout);
            char buf[32];
            if (scanf("%31s", buf) != 1 || buf[0] == '-') return 0;
            int X = buf[0] == 'Y' ? T : (S ^ T);
            int i = X ? killSq(A, X, r) : -1;
            if (i < 0) { for (int k = 0; k < 9; k++) if (A >> k & 1) { i = k; break; } }
            printf("%d\n", i + 1); fflush(stdout);
            if (scanf("%31s", buf) != 1 || buf[0] == '-') return 0;
            if (buf[0] == 'T') return 0;
            A ^= 1 << i;
            S = NB(X) & A;
        }
    } else {
        printf("Runner\n"); fflush(stdout);
        vector<int> Xs;
        for (int r = R; r >= 1; r--) {
            int n;
            if (scanf("%d", &n) != 1 || n < 0) return 0;
            int Q = 0;
            for (int i = 0; i < n; i++) { int s; if (scanf("%d", &s) != 1 || s < 0) return 0; Q |= 1 << (s - 1); }
            int X1 = S & Q, X2 = S & ~Q, X;
            bool yes;
            if (X1 && killSq(A, X1, r) < 0) { X = X1; yes = true; }
            else if (X2 && killSq(A, X2, r) < 0) { X = X2; yes = false; }
            else if (X1) { X = X1; yes = true; }
            else { X = X2; yes = false; }
            printf(yes ? "Yes\n" : "No\n"); fflush(stdout);
            int i;
            if (scanf("%d", &i) != 1 || i < 0) return 0;
            A &= ~(1 << (i - 1));
            S = NB(X) & A;
            Xs.push_back(X);
            if (S == 0) { printf("Trapped\n"); fflush(stdout); return 0; }
            printf("Free\n"); fflush(stdout);
        }
        vector<int> path(R + 1);
        int p = __builtin_ctz(S);
        path[R] = p;
        for (int t = R - 1; t >= 0; t--) {
            int c = Xs[t] & nbm[p];
            p = __builtin_ctz(c);
            path[t] = p;
        }
        for (int t = 0; t <= R; t++) printf(t ? " %d" : "%d", path[t] + 1);
        printf("\n"); fflush(stdout);
    }
    return 0;
}

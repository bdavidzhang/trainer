// Elapid Errands: route on a coarse grid of 9x9 blocks (targets are >=20 apart, so every block
// holds at most one target), using Dijkstra with a "keep away from the old path" penalty so that
// corridors stay open, then expand each coarse step to 9 fine steps through block centres.
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

static int S, C, G, OFFB;          // block size, centre offset, coarse grid side, margin in blocks
static int N;
static vector<ll> px, py;          // points, index 0 = origin
static vector<int> pb;             // block id of each point
static vector<char> used_;         // coarse cells already on the path
static vector<int> tgt;            // tgt[cell] = index of the point in this block, or -1
static const int DX[4] = {1, -1, 0, 0}, DY[4] = {0, 0, 1, -1};

static inline int cid(int x, int y) { return y * G + x; }

// multi-source BFS distance to the used cells (and optionally the border), capped at cap
static void distField(vector<int>& d, int cap, bool border) {
    d.assign((size_t)G * G, cap);
    vector<int> q; q.reserve((size_t)G * G / 4);
    for (int c = 0; c < G * G; c++) {
        int x = c % G, y = c / G;
        if (used_[c] || (border && (x == 0 || y == 0 || x == G - 1 || y == G - 1))) { d[c] = 0; q.push_back(c); }
    }
    for (size_t h = 0; h < q.size(); h++) {
        int c = q[h]; if (d[c] + 1 >= cap) continue;
        int x = c % G, y = c / G;
        for (int k = 0; k < 4; k++) {
            int nx = x + DX[k], ny = y + DY[k];
            if (nx < 0 || ny < 0 || nx >= G || ny >= G) continue;
            int nc = cid(nx, ny);
            if (d[nc] > d[c] + 1) { d[nc] = d[c] + 1; q.push_back(nc); }
        }
    }
}

static vector<int> rep_;   // repulsion field around targets that are still to come (rebuilt per leg)

// Dijkstra from s to t over states (cell, phase); cells of points with index > cur are blocked.
// Phase 0: still walking along the walls contiguously from the head, on track off+1 (leaving `off`
// free tracks next to the wall).  Phase 1: the path has left the wall and from now on is strongly
// repelled by every wall, so that it touches the old path along one contiguous stretch only and
// therefore cannot cut the free region in two.  Returns the path (s..t) or empty.
static vector<ll> dist_; static vector<signed char> par_;
static vector<int> route(int s, int t, int cur, int off, const vector<int>& d) {
    const int REP_D = 12;
    dist_.assign((size_t)G * G * 2, LLONG_MAX);
    par_.assign((size_t)G * G * 2, -1);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    dist_[2 * s] = 0; pq.push({0, 2 * s});
    const ll SC = 256;
    int sx = s % G, sy = s / G, tx = t % G, ty = t / G;
    double ux = tx - sx, uy = ty - sy, ul = max(1.0, sqrt(ux * ux + uy * uy));
    int endState = -1;
    while (!pq.empty()) {
        auto [dd, st] = pq.top(); pq.pop();
        if (dd > dist_[st]) continue;
        int c = st >> 1, ph = st & 1;
        if (c == t) { endState = st; break; }
        int x = c % G, y = c / G;
        for (int k = 0; k < 4; k++) {
            int nx = x + DX[k], ny = y + DY[k];
            if (nx < 0 || ny < 0 || nx >= G || ny >= G) continue;
            int nc = cid(nx, ny);
            if (used_[nc]) continue;
            if (tgt[nc] > cur && nc != t) continue;
            ll base = SC;
            if (nc != t) base += SC * rep_[nc];
            double dev = fabs((nx - sx) * uy - (ny - sy) * ux) / ul;
            base += (ll)min(dev, 48.0);
            int dc = d[nc];
            for (int np = ph; np < 2; np++) {
                ll w = base;
                if (np == 0) {
                    if (dc > off + 1) continue;
                    if (dc <= off) w += SC * 6 * (off + 1 - dc);
                } else {
                    if (dc < REP_D && nc != t) w += SC * 2 * (REP_D - dc);
                }
                int ns = 2 * nc + np;
                if (dd + w < dist_[ns]) { dist_[ns] = dd + w; par_[ns] = (signed char)(k * 2 + ph); pq.push({dist_[ns], ns}); }
            }
        }
    }
    vector<int> path;
    if (endState < 0) return path;
    int st = endState;
    while (st != 2 * s) {
        int c = st >> 1;
        path.push_back(c);
        int k = par_[st] >> 1, pp = par_[st] & 1;
        st = 2 * cid(c % G - DX[k], c / G - DY[k]) + pp;
    }
    path.push_back(s);
    reverse(path.begin(), path.end());
    return path;
}

// Head is at block h after reaching point cur. Can every later target still be reached through a
// corridor of clearance w (all cells at distance >= w from the path and the border)? Near the head
// and near each target a ball of radius w+2 (walking through free cells) is exempt from the clearance.
static vector<int> mark_; static int stamp_ = 0;
static bool thickOK(int h, int cur, int w, const vector<int>& e) {
    if (mark_.size() != (size_t)G * G) { mark_.assign((size_t)G * G, 0); stamp_ = 0; }
    int rho = w + 2;
    int sa = ++stamp_;                       // thick-reached set
    vector<int> q, dep;
    q.push_back(h); dep.push_back(0); mark_[h] = sa;
    for (size_t i = 0; i < q.size(); i++) {
        int c = q[i]; if (dep[i] >= rho) continue;
        int x = c % G, y = c / G;
        for (int k = 0; k < 4; k++) {
            int nx = x + DX[k], ny = y + DY[k];
            if (nx < 0 || ny < 0 || nx >= G || ny >= G) continue;
            int nc = cid(nx, ny);
            if (mark_[nc] == sa || used_[nc] || tgt[nc] > cur) continue;
            mark_[nc] = sa; q.push_back(nc); dep.push_back(dep[i] + 1);
        }
    }
    for (size_t i = 0; i < q.size(); i++) {
        int c = q[i]; int x = c % G, y = c / G;
        for (int k = 0; k < 4; k++) {
            int nx = x + DX[k], ny = y + DY[k];
            if (nx < 0 || ny < 0 || nx >= G || ny >= G) continue;
            int nc = cid(nx, ny);
            if (mark_[nc] == sa || used_[nc] || tgt[nc] > cur || e[nc] < w) continue;
            mark_[nc] = sa; q.push_back(nc);
        }
    }
    for (int j = cur + 1; j <= N; j++) {
        int sb = ++stamp_; bool ok = false;
        vector<int> q2, dep2; q2.push_back(pb[j]); dep2.push_back(0);
        for (size_t i = 0; i < q2.size() && !ok; i++) {
            int c = q2[i]; if (dep2[i] >= rho) continue;
            int x = c % G, y = c / G;
            for (int k = 0; k < 4; k++) {
                int nx = x + DX[k], ny = y + DY[k];
                if (nx < 0 || ny < 0 || nx >= G || ny >= G) continue;
                int nc = cid(nx, ny);
                if (mark_[nc] == sa) { ok = true; break; }
                if (mark_[nc] == sb || used_[nc] || tgt[nc] > cur) continue;
                mark_[nc] = sb; q2.push_back(nc); dep2.push_back(dep2[i] + 1);
            }
        }
        if (!ok) {
#ifdef DBG
            if (w == 1) fprintf(stderr, "      w=1: target %d cut off\n", j);
#endif
            return false;
        }
    }
    return true;
}

// largest w in [0, wneed] such that thickOK holds (0 = some target is cut off completely)
static int clearanceScore(int h, int cur, int wneed) {
    vector<int> e; distField(e, wneed + 1, true);
    if (thickOK(h, cur, wneed, e)) return wneed;
    int lo = 0, hi = wneed - 1;
    while (lo < hi) { int mid = (lo + hi + 1) / 2; if (thickOK(h, cur, mid, e)) lo = mid; else hi = mid - 1; }
    return lo;
}

// simple path inside an S x S block from a to b avoiding `blocked`; perm = neighbour order
static bool localBfs(pair<int,int> a, pair<int,int> b, const vector<char>& blocked, const int* perm,
                     vector<pair<int,int>>& out) {
    vector<int> par(S * S, -2);
    vector<int> q; int sa = a.second * S + a.first, sb = b.second * S + b.first;
    par[sa] = -1; q.push_back(sa);
    for (size_t i = 0; i < q.size() && par[sb] == -2; i++) {
        int c = q[i]; int x = c % S, y = c / S;
        for (int kk = 0; kk < 4; kk++) {
            int k = perm[kk];
            int nx = x + DX[k], ny = y + DY[k];
            if (nx < 0 || ny < 0 || nx >= S || ny >= S) continue;
            int nc = ny * S + nx;
            if (par[nc] != -2 || blocked[nc]) continue;
            par[nc] = c; q.push_back(nc);
        }
    }
    if (par[sb] == -2) return false;
    out.clear();
    for (int c = sb; c != -1; c = par[c]) out.push_back({c % S, c / S});
    reverse(out.begin(), out.end());
    return true;
}

// local cells for a target block: entry e (or none) -> p -> exit f (or none)
static vector<pair<int,int>> localRoute(bool hasE, pair<int,int> e, pair<int,int> p, bool hasF, pair<int,int> f) {
    int perm[4] = {0, 1, 2, 3};
    do {
        for (int order = 0; order < 2; order++) {
            vector<pair<int,int>> A{p}, B{p};
            vector<char> bl(S * S, 0);
            bool ok = true;
            if (order == 0) {
                if (hasE) {
                    if (hasF && f != p) bl[f.second * S + f.first] = 1;
                    if (hasF && f == e && e != p) ok = false;
                    else ok = localBfs(e, p, bl, perm, A);
                }
                if (ok && hasF) {
                    fill(bl.begin(), bl.end(), 0);
                    for (auto& c : A) if (c != p) bl[c.second * S + c.first] = 1;
                    ok = localBfs(p, f, bl, perm, B);
                }
            } else {
                if (hasF) {
                    if (hasE && e != p) bl[e.second * S + e.first] = 1;
                    ok = localBfs(p, f, bl, perm, B);
                }
                if (ok && hasE) {
                    fill(bl.begin(), bl.end(), 0);
                    for (auto& c : B) if (c != p) bl[c.second * S + c.first] = 1;
                    ok = localBfs(e, p, bl, perm, A);
                }
            }
            if (!ok) continue;
            vector<pair<int,int>> res;
            if (hasE) res = A; else res.push_back(p);
            if (hasF) for (size_t i = 1; i < B.size(); i++) res.push_back(B[i]);
            return res;
        }
    } while (next_permutation(perm, perm + 4));
    return {};
}

static bool solveWith(int s, string& ans) {
    S = s; C = S / 2;
    ll mx = 0;
    for (int i = 0; i <= N; i++) mx = max(mx, max(px[i], py[i]));
    OFFB = (S == 1 ? 30 : 70);
    ll side = mx / S + 1 + 2 * OFFB;
    if (side > 1500) return false;
    G = (int)side;
    used_.assign((size_t)G * G, 0);
    tgt.assign((size_t)G * G, -1);
    pb.assign(N + 1, 0);
    for (int i = 0; i <= N; i++) {
        int bx = (int)(px[i] / S) + OFFB, by = (int)(py[i] / S) + OFFB;
        pb[i] = cid(bx, by);
        if (tgt[pb[i]] != -1) return false;     // two points in one block
        tgt[pb[i]] = i;
    }
    vector<int> cp;            // coarse path
    cp.push_back(pb[0]); used_[pb[0]] = 1;
    static const int KS[] = {0, 1, 2, 3, 5, 8, 12};
    const int NK = 7;
    vector<int> d;
    for (int i = 1; i <= N; i++) {
        distField(d, 24, false);
        int wneed = (N - i) / 2 + 1;
        // repulsion around targets that come later
        rep_.assign((size_t)G * G, 0);
        if (S > 1) for (int j = i + 1; j <= N; j++) {
            int jx = pb[j] % G, jy = pb[j] / G, R = wneed + 2;
            for (int y = max(0, jy - R); y <= min(G - 1, jy + R); y++)
                for (int x = max(0, jx - R); x <= min(G - 1, jx + R); x++)
                    rep_[cid(x, y)] = max(rep_[cid(x, y)], 2 * (R + 1 - max(abs(x - jx), abs(y - jy))));
        }
        vector<int> best; int bestScore = -1;
        for (int a = 0; a < NK; a++) {
            vector<int> path = route(pb[i - 1], pb[i], i, KS[a], d);
            if (path.empty()) break;
            if (i == N) { best = path; bestScore = 1; break; }
            for (size_t j = 1; j < path.size(); j++) used_[path[j]] = 1;
            int sc = clearanceScore(pb[i], i, wneed);
            for (size_t j = 1; j < path.size(); j++) used_[path[j]] = 0;
            if (sc > bestScore) { bestScore = sc; best = path; }
#ifdef DBG
            fprintf(stderr, "   leg %d k=%d score %d len %zu\n", i, KS[a], sc, path.size());
#endif
            if (sc >= wneed) break;
        }
#ifdef DBG
        fprintf(stderr, "leg %d: need %d score %d len %zu\n", i, wneed, bestScore, best.size());
#endif
        if (bestScore < 1) {
#ifdef DBG
            vector<int> path = route(pb[i - 1], pb[i], i, 0, d);
            FILE* f = fopen("dump.txt", "w"); fprintf(f, "%d %d\n", G, i);
            for (int c = 0; c < G * G; c++) if (used_[c]) fprintf(f, "u %d %d\n", c % G, c / G);
            for (int c : path) fprintf(f, "p %d %d\n", c % G, c / G);
            for (int j = 0; j <= N; j++) fprintf(f, "t %d %d %d\n", pb[j] % G, pb[j] / G, j);
            fclose(f);
#endif
            return false;
        }
        for (size_t j = 1; j < best.size(); j++) { used_[best[j]] = 1; cp.push_back(best[j]); }
    }
    // expand to fine cells
    vector<pair<ll, ll>> cells;
    int L = (int)cp.size();
    for (int t = 0; t < L; t++) {
        int c = cp[t]; int bx = c % G, by = c / G;
        ll ox = (ll)(bx - OFFB) * S, oy = (ll)(by - OFFB) * S;
        bool hasE = t > 0, hasF = t + 1 < L;
        pair<int,int> e{C, C}, f{C, C};
        if (hasE) { int p = cp[t - 1]; int dx = bx - p % G, dy = by - p / G; e = {C - C * dx, C - C * dy}; }
        if (hasF) { int n = cp[t + 1]; int dx = n % G - bx, dy = n / G - by; f = {C + C * dx, C + C * dy}; }
        if (tgt[c] >= 0) {
            int i = tgt[c];
            pair<int,int> p{(int)(px[i] - ox), (int)(py[i] - oy)};
            auto lr = localRoute(hasE, e, p, hasF, f);
            if (lr.empty()) return false;
            for (auto& q : lr) cells.push_back({ox + q.first, oy + q.second});
        } else {
            pair<int,int> cur = e; cells.push_back({ox + cur.first, oy + cur.second});
            auto walk = [&](pair<int,int> to) {
                while (cur != to) {
                    if (cur.first < to.first) cur.first++; else if (cur.first > to.first) cur.first--;
                    else if (cur.second < to.second) cur.second++; else cur.second--;
                    cells.push_back({ox + cur.first, oy + cur.second});
                }
            };
            walk({C, C}); walk(f);
        }
    }
    ans.clear();
    for (size_t i = 1; i < cells.size(); i++) {
        ll dx = cells[i].first - cells[i - 1].first, dy = cells[i].second - cells[i - 1].second;
        if (dx == 1 && dy == 0) ans += '>';
        else if (dx == -1 && dy == 0) ans += '<';
        else if (dx == 0 && dy == 1) ans += '^';
        else if (dx == 0 && dy == -1) ans += 'v';
        else return false;
    }
    return ans.size() <= 2000000;
}

int main() {
    scanf("%d", &N);
    px.assign(N + 1, 0); py.assign(N + 1, 0);
    for (int i = 1; i <= N; i++) scanf("%lld %lld", &px[i], &py[i]);
    string ans;
    bool ok = false;
    for (int s : {9, 7, 5, 3, 1}) { if (solveWith(s, ans)) { ok = true; break; } }
    if (!ok) { fprintf(stderr, "FAILED\n"); }
    printf("%s\n", ans.c_str());
    return 0;
}

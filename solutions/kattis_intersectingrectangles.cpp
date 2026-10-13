#include <bits/stdc++.h>
using namespace std;
int N; vector<int> bit;
void upd(int i,int v){ for(i++;i<=N;i+=i&-i) bit[i]+=v; }
int qry(int i){ int s=0; for(;i>0;i-=i&-i) s+=bit[i]; return s; } // sum of [0,i)
int main(){
    int n; scanf("%d",&n);
    vector<array<int,4>> r(n);
    vector<int> ys;
    for(auto&a:r){ scanf("%d %d %d %d",&a[0],&a[1],&a[2],&a[3]); ys.push_back(a[1]); ys.push_back(a[3]); }
    sort(ys.begin(),ys.end());
    N=ys.size(); bit.assign(N+1,0);
    vector<array<int,3>> ev; // x, type(0 open,1 close), idx
    for(int i=0;i<n;i++){ ev.push_back({r[i][0],0,i}); ev.push_back({r[i][2],1,i}); }
    sort(ev.begin(),ev.end());
    for(auto&e:ev){
        int i=e[2];
        int a=lower_bound(ys.begin(),ys.end(),r[i][1])-ys.begin();
        int b=lower_bound(ys.begin(),ys.end(),r[i][3])-ys.begin();
        if(e[1]==1){ upd(a,-1); upd(b,-1); }
        if(qry(b)-qry(a+1)>0){ puts("1"); return 0; }
        if(e[1]==0){ upd(a,1); upd(b,1); }
    }
    puts("0");
}

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
ll px[12],py[12],dx[12],dy[12];
bool par[12][12];
int rk[12][12]; // rank of intersection (i,j) along line i
int ord_[12], lo[12], hi[12];
bool used[12];
ll total=0;
// segments on lines a and b (non-adjacent, both complete) share a point?
static inline bool hit(int a,int b){
    if(par[a][b]) return false;
    return rk[a][b]>=lo[a]&&rk[a][b]<=hi[a]&&rk[b][a]>=lo[b]&&rk[b][a]<=hi[b];
}
void rec(int m){ // ord_[0..m-1] chosen
    int last=ord_[m-1];
    if(m==n){
        int f=ord_[0];
        if(par[last][f]) return;
        int a=rk[last][ord_[m-2]], b=rk[last][f];
        if(a==b) return; lo[last]=min(a,b); hi[last]=max(a,b);
        a=rk[f][last]; b=rk[f][ord_[1]];
        if(a==b) return; lo[f]=min(a,b); hi[f]=max(a,b);
        for(int t=1;t<=n-3;t++) if(hit(last,ord_[t])) return;
        for(int t=2;t<=n-2;t++) if(hit(f,ord_[t])) return;
        total++; return;
    }
    for(int c=1;c<n;c++) if(!used[c]&&!par[last][c]){
        if(m>=2){
            int a=rk[last][ord_[m-2]], b=rk[last][c];
            if(a==b) continue;
            lo[last]=min(a,b); hi[last]=max(a,b);
            bool bad=false;
            for(int t=1;t<=m-3&&!bad;t++) if(hit(last,ord_[t])) bad=true;
            if(bad) continue;
        }
        used[c]=true; ord_[m]=c; rec(m+1); used[c]=false;
    }
}
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++){ ll a,b,c,d; scanf("%lld %lld %lld %lld",&a,&b,&c,&d); px[i]=a;py[i]=b;dx[i]=c-a;dy[i]=d-b; }
    for(int i=0;i<n;i++){
        // parameter t of intersection with j along line i: num/den
        vector<array<ll,3>> v; // num, den(>0), j
        for(int j=0;j<n;j++){
            par[i][j]=true; if(i==j) continue;
            ll den=dx[i]*dy[j]-dy[i]*dx[j];
            if(den==0) continue;
            par[i][j]=false;
            ll num=(px[j]-px[i])*dy[j]-(py[j]-py[i])*dx[j];
            if(den<0){den=-den;num=-num;}
            v.push_back({num,den,(ll)j});
        }
        sort(v.begin(),v.end(),[](const array<ll,3>&a,const array<ll,3>&b){ return a[0]*b[1]<b[0]*a[1]; });
        int r=0;
        for(size_t t=0;t<v.size();t++){
            if(t>0 && v[t][0]*v[t-1][1]!=v[t-1][0]*v[t][1]) r++;
            rk[i][v[t][2]]=r;
        }
    }
    used[0]=true; ord_[0]=0;
    rec(1);
    printf("%lld\n",total/2);
}

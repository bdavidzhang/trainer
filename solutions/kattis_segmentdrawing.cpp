#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 LL;
// For i<j (segment i left of segment j): if y_j<y_i, P_j must not be strictly left of drawn segment i,
// i.e. t_i <= (axis hit of ray P_i->P_j); if y_j>y_i then t_j >= hit of ray P_j->P_i; equal y needs x_i<=x_j.
// So every t_i has an independent interval. Tightest bound = tangent from P_i to the hull of the lower
// points on one index side: CDQ on index + monotone hull by y + binary search.
static vector<ll> X,Y;
static vector<int> ord,bestv,tmp;
static inline ll cross3(int o,int a,int b){return (X[a]-X[o])*(Y[b]-Y[o])-(Y[a]-Y[o])*(X[b]-X[o]);}
static inline bool better(int p,int a,int b){ // ray p->a hits axis strictly left of ray p->b
    return (X[a]-X[p])*(Y[b]-Y[p])-(Y[a]-Y[p])*(X[b]-X[p])>0;
}
static vector<int> st;
static void rec(int lo,int hi){
    if(hi-lo<2)return;
    int mid=(lo+hi)/2;
    rec(lo,mid);rec(mid,hi);
    st.clear();
    int q=mid;
    for(int a=lo;a<mid;a++){
        int i=ord[a];
        while(q<hi && Y[ord[q]]<Y[i]){
            int p=ord[q++];
            while(st.size()>=2 && cross3(st[st.size()-2],st.back(),p)>=0)st.pop_back();
            st.push_back(p);
        }
        if(st.empty())continue;
        int l=0,h=(int)st.size()-1; // first m with !better(st[m+1],st[m]); m=size-1 always qualifies
        while(l<h){
            int m=(l+h)/2;
            if(better(i,st[m+1],st[m]))l=m+1; else h=m;
        }
        int cnd=st[l];
        if(bestv[i]<0||better(i,cnd,bestv[i]))bestv[i]=cnd;
    }
    auto cmp=[&](int a,int b){return Y[a]<Y[b]||(Y[a]==Y[b]&&X[a]<X[b]);};
    merge(ord.begin()+lo,ord.begin()+mid,ord.begin()+mid,ord.begin()+hi,tmp.begin()+lo,cmp);
    copy(tmp.begin()+lo,tmp.begin()+hi,ord.begin()+lo);
}
static vector<int> solve(const vector<ll>&x,const vector<ll>&y){
    int n=x.size(); X=x;Y=y; ord.resize(n);tmp.resize(n);iota(ord.begin(),ord.end(),0);bestv.assign(n,-1);
    rec(0,n); return bestv;
}
struct Fr{LL n,d;}; // d>0
static bool le(const Fr&a,const Fr&b){return a.n*b.d<=b.n*a.d;}
int main(){
    int n; scanf("%d",&n);
    vector<ll> x(n),y(n),l(n),r(n);
    for(int i=0;i<n;i++)scanf("%lld %lld %lld %lld",&x[i],&y[i],&l[i],&r[i]);
    {
        unordered_map<ll,ll> last; last.reserve(2*n);
        for(int i=0;i<n;i++){
            auto it=last.find(y[i]);
            if(it!=last.end()&&x[i]<it->second){puts("-1");return 0;}
            last[y[i]]=x[i];
        }
    }
    vector<int> up=solve(x,y);
    vector<ll> xr(n),yr(n);
    for(int i=0;i<n;i++){xr[i]=-x[n-1-i];yr[i]=y[n-1-i];}
    vector<int> dnr=solve(xr,yr);
    long double tot=0;
    for(int i=0;i<n;i++){
        Fr lo{(LL)l[i],1},hi{(LL)r[i],1};
        int j=up[i];
        if(j>=0){Fr f{(LL)x[j]*y[i]-(LL)x[i]*y[j],(LL)(y[i]-y[j])}; if(le(f,hi))hi=f;}
        int jr=dnr[n-1-i];
        if(jr>=0){int k=n-1-jr; Fr f{(LL)x[k]*y[i]-(LL)x[i]*y[k],(LL)(y[i]-y[k])}; if(le(lo,f))lo=f;}
        if(!le(lo,hi)){puts("-1");return 0;}
        long double a=(long double)lo.n/(long double)lo.d,b=(long double)hi.n/(long double)hi.d;
        long double t=(long double)x[i]; if(t<a)t=a; if(t>b)t=b;
        tot+=hypotl(t-(long double)x[i],(long double)y[i]);
    }
    printf("%.10Lf\n",tot);
}

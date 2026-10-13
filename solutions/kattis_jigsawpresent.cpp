#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// Need nonzero eps in {-1,0,1}^n with sum eps_i*(x_i,y_i)=0.
// 2^n distinct lattice points with variance <= n*2^23 is impossible for n>=31 (disc packing),
// so the first min(n,31) items suffice; meet in the middle over 3^15 signed sums.
struct E{ll key;int code;};
static const ll K=1LL<<20;
static vector<E> build(const vector<ll>&w){
    vector<E> L;L.push_back({0,0});
    int p3=1;
    for(ll v:w){
        vector<E> N;N.reserve(L.size()*3);
        size_t a=0,b=0,c=0,n=L.size();
        // streams: L-v (code+2*p3), L (code), L+v (code+p3)
        while(a<n||b<n||c<n){
            ll ka=a<n?L[a].key-v:LLONG_MAX,kb=b<n?L[b].key:LLONG_MAX,kc=c<n?L[c].key+v:LLONG_MAX;
            E e;
            if(ka<=kb&&ka<=kc){e={ka,L[a].code+2*p3};a++;}
            else if(kb<=kc){e={kb,L[b].code};b++;}
            else{e={kc,L[c].code+p3};c++;}
            if(!N.empty()&&N.back().key==e.key){if(N.back().code==0)N.back().code=e.code;}
            else N.push_back(e);
        }
        L.swap(N);
        p3*=3;
    }
    return L;
}
int main(){
    int n;scanf("%d",&n);
    vector<ll> w(n);
    for(int i=0;i<n;i++){ll x,y;scanf("%lld %lld",&x,&y);w[i]=x*K+y;}
    int m=min(n,31);
    int na=m/2,nb=m-na;
    vector<ll> wa(w.begin(),w.begin()+na),wb(w.begin()+na,w.begin()+m-1);
    ll last=w[m-1];
    vector<E> A=build(wa),L=build(wb);
    ll sh[3]={0,last,-last};
    for(int c=0;c<3;c++){
        ll t=sh[c];
        ll i=0,j=(ll)L.size()-1;
        while(i<(ll)A.size()&&j>=0){
            ll s=A[i].key+L[j].key+t;
            if(s<0)i++;
            else if(s>0)j--;
            else{
                if(A[i].code==0&&L[j].code==0&&c==0){i++;j--;continue;}
                vector<int> eps(m,0);
                int ca=A[i].code;
                for(int q=0;q<na;q++){eps[q]=ca%3;ca/=3;}
                int cb=L[j].code;
                for(int q=0;q<nb-1;q++){eps[na+q]=cb%3;cb/=3;}
                eps[m-1]=c;
                vector<int> P,Q;
                for(int q=0;q<m;q++){if(eps[q]==1)P.push_back(q+1);else if(eps[q]==2)Q.push_back(q+1);}
                puts("no");
                printf("%d",(int)P.size());for(int v:P)printf(" %d",v);puts("");
                printf("%d",(int)Q.size());for(int v:Q)printf(" %d",v);puts("");
                return 0;
            }
        }
    }
    puts("yes");
}

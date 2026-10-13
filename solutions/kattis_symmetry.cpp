#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Ln{ll a,b,c;int t;
    bool operator<(const Ln&o)const{if(a!=o.a)return a<o.a;if(b!=o.b)return b<o.b;if(c!=o.c)return c<o.c;return t<o.t;}};
static ll g3(ll a,ll b,ll c){return std::gcd(std::gcd(llabs(a),llabs(b)),llabs(c));}
static Ln norm(ll a,ll b,ll c,int t){ll g=g3(a,b,c);a/=g;b/=g;c/=g;if(a<0||(a==0&&b<0)){a=-a;b=-b;c=-c;}return {a,b,c,t};}
int main(){
    int n;scanf("%d",&n);vector<ll> x(n),y(n);
    for(int i=0;i<n;i++)scanf("%lld %lld",&x[i],&y[i]);
    if(n==1){puts("0");return 0;}
    int best=1;
    {vector<ll> sums;sums.reserve((size_t)n*(n+1)/2);
     for(int i=0;i<n;i++)for(int j=i;j<n;j++)sums.push_back((x[i]+x[j]+40000)*1000000+(y[i]+y[j]+40000)*2+(i!=j));
     sort(sums.begin(),sums.end());
     // key/2 identifies the centre; ordered pairs: i!=j counts 2, i==j counts 1
     size_t i=0;while(i<sums.size()){size_t j=i;int cnt=0;while(j<sums.size()&&sums[j]/2==sums[i]/2){cnt+=(sums[j]&1)?2:1;j++;}best=max(best,cnt);i=j;}}
    vector<Ln> v;v.reserve((size_t)n*(n-1));
    for(int i=0;i<n;i++)for(int j=i+1;j<n;j++){
        ll a=x[j]-x[i],b=y[j]-y[i];
        v.push_back(norm(2*a,2*b,x[j]*x[j]+y[j]*y[j]-x[i]*x[i]-y[i]*y[i],0));
        ll na=-b,nb=a;
        v.push_back(norm(na,nb,na*x[i]+nb*y[i],1));
    }
    sort(v.begin(),v.end());
    size_t i=0;
    while(i<v.size()){
        size_t j=i;int bis=0,thr=0;
        while(j<v.size()&&v[j].a==v[i].a&&v[j].b==v[i].b&&v[j].c==v[i].c){if(v[j].t)thr++;else bis++;j++;}
        int val;
        if(thr){int m=(int)llround((1+sqrt(1.0+8.0*thr))/2);while((ll)m*(m-1)/2<thr)m++;while((ll)m*(m-1)/2>thr)m--;val=2*bis+m;}
        else{val=2*bis;if(val+1>best){for(int q=0;q<n;q++)if(v[i].a*x[q]+v[i].b*y[q]==v[i].c){val++;break;}}}
        best=max(best,val);
        i=j;
    }
    printf("%d\n",n-best);
}

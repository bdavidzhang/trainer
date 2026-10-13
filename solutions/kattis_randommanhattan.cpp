#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
struct E{ld x1,y1,x2,y2;};
static ld evalAt(const E&e,ld x){return e.y1+(e.y2-e.y1)*((x-e.x1)/(e.x2-e.x1));}
static ld solve(const vector<ld>&X,const vector<ld>&Y){
    int n=X.size();
    vector<E> a,b;
    for(int i=0;i<n;i++){
        int j=(i+1)%n;
        if(X[i]<X[j])a.push_back({X[i],Y[i],X[j],Y[j]});
        else if(X[i]>X[j])b.push_back({X[j],Y[j],X[i],Y[i]});
    }
    auto c=[](const E&p,const E&q){return p.x1<q.x1;};
    sort(a.begin(),a.end(),c);sort(b.begin(),b.end(),c);
    vector<ld> xs(X);sort(xs.begin(),xs.end());xs.erase(unique(xs.begin(),xs.end()),xs.end());
    int m=xs.size();
    vector<ld> w0(m-1),w1(m-1);
    size_t pa=0,pb=0;ld A=0;
    for(int i=0;i+1<m;i++){
        ld l=xs[i],r=xs[i+1];
        while(a[pa].x2<=l)pa++;
        while(b[pb].x2<=l)pb++;
        w0[i]=fabsl(evalAt(a[pa],l)-evalAt(b[pb],l));
        w1[i]=fabsl(evalAt(a[pa],r)-evalAt(b[pb],r));
        A+=(w0[i]+w1[i])/2*(r-l);
    }
    static const ld gx[3]={-sqrtl(0.6L),0,sqrtl(0.6L)},gw[3]={5.0L/9,8.0L/9,5.0L/9};
    ld F0=0,res=0;
    for(int i=0;i+1<m;i++){
        ld L=xs[i+1]-xs[i],s=(w1[i]-w0[i])/L;
        ld tot=(w0[i]+w1[i])/2*L/A;
        for(int g=0;g<3;g++){
            ld t=(gx[g]+1)/2*L;
            ld d=(w0[i]*t+s*t*t/2)/A;      // mass from slab start
            ld F=F0+d;
            ld G=(1-F0-tot)+(tot-d);       // 1-F
            res+=gw[g]*L/2*F*G;
        }
        F0+=tot;
    }
    return 2*res;
}
int main(){
    int n;scanf("%d",&n);
    vector<ld> X(n),Y(n);
    for(int i=0;i<n;i++){long long x,y;scanf("%lld %lld",&x,&y);X[i]=x;Y[i]=y;}
    printf("%.12Lf\n",solve(X,Y)+solve(Y,X));
}

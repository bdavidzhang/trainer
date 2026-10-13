#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// Occupied chairs always lie in a coset B + d*Z_n (d | n, m = n/d).
// chair(slot s) = B + d*((a*s) mod m). Multiplying by x with gcd(x,m)=1 is a bijection on the coset
// (lazy update of a); otherwise the coset shrinks by g=gcd(x,m)>=2 and we rebuild in O(m).
ll egcd(ll a,ll b,ll&x,ll&y){if(!b){x=1;y=0;return a;}ll x1,y1;ll g=egcd(b,a%b,x1,y1);x=y1;y=x1-(a/b)*y1;return g;}
int main(){
    int n,q;if(scanf("%d %d",&n,&q)!=2)return 0;
    ll d=1,m=n,B=0,a=1,ainv=1;
    vector<int> P(n);for(int s=0;s<n;s++)P[s]=(s==0?n:s); // slot s <-> chair s (0 means n)
    a%=m;ainv%=m;
    char op[4];int x;
    while(q--){
        scanf("%s %d",op,&x);
        if(op[0]=='+'){B=(B+x)%n;}
        else if(op[0]=='?'){
            ll t=((x%n)-B)%n;if(t<0)t+=n;
            if(t%d){puts("-1");continue;}
            ll k=t/d;ll s=ainv*k%m;
            printf("%d\n",P[s]);
        } else {
            ll xm=x%m;ll g=std::gcd((ll)x,m);
            if(g==1){
                B=B*(ll)x%n;
                a=a*xm%m;
                ll u,v;egcd(xm,m,u,v);u%=m;if(u<0)u+=m;
                if(m==1)u=0;
                ainv=ainv*u%m;
            } else {
                ll m2=m/g,d2=d*g;ll xr=(x/g)%m2;
                vector<int> NP(m2,-1);vector<ll> best(m2,LLONG_MAX);
                for(ll s=0;s<m;s++){
                    if(P[s]<0)continue;
                    ll k=a*s%m;
                    ll oldc=(B+d*k)%n;
                    ll newc=oldc*(ll)x%n;
                    ll dist=(newc-oldc)%n;if(dist<0)dist+=n;
                    ll k2=xr*(k%m2)%m2;
                    if(dist<best[k2]){best[k2]=dist;NP[k2]=P[s];}
                }
                P.swap(NP);
                B=B*(ll)x%n;d=d2;m=m2;a=1%m;ainv=1%m;
            }
        }
    }
}

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct F{ll p,q;};
static F mk(ll p,ll q){if(q<0){p=-p;q=-q;}ll g=std::gcd(p<0?-p:p,q);if(g>1){p/=g;q/=g;}return {p,q};}
// all results of x op y (both orders)
static void ops(F x,F y,vector<F>&o){
 o.push_back(mk(x.p*y.q+y.p*x.q,x.q*y.q));
 o.push_back(mk(x.p*y.q-y.p*x.q,x.q*y.q));
 o.push_back(mk(y.p*x.q-x.p*y.q,x.q*y.q));
 o.push_back(mk(x.p*y.p,x.q*y.q));
 if(y.p!=0)o.push_back(mk(x.p*y.q,x.q*y.p));
 if(x.p!=0)o.push_back(mk(y.p*x.q,y.q*x.p));
}
int d;
static bool hit(const vector<F>&v){for(auto&f:v)if(f.q==1&&f.p==d)return true;return false;}
static bool solvable(int a,int b,int c){
 int v[3]={a,b,c};
 for(int i=0;i<3;i++)for(int j=i+1;j<3;j++){
  int k=3-i-j;vector<F> o;ops({v[i],1},{v[j],1},o);
  if(hit(o))return true;
  vector<F> o2;for(auto&f:o)ops(f,{v[k],1},o2);
  if(hit(o2))return true;
 }
 return false;
}
int main(){cin>>d;
 for(int a=100;a>=1;a--)if(a!=d)for(int b=a-1;b>=1;b--)if(b!=d)for(int c=b-1;c>=1;c--)if(c!=d){
  if(!solvable(a,b,c)){printf("%d %d %d\n",a,b,c);return 0;}
 }
 return 1;}

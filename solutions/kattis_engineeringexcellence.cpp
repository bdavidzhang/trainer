#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
struct P{ld x,y;};
static P operator-(P a,P b){return {a.x-b.x,a.y-b.y};}
static P operator+(P a,P b){return {a.x+b.x,a.y+b.y};}
static P operator*(P a,ld k){return {a.x*k,a.y*k};}
static ld cross(P a,P b){return a.x*b.y-a.y*b.x;}
static ld dot(P a,P b){return a.x*b.x+a.y*b.y;}
static ld len(P a){return sqrtl(dot(a,a));}
int main(){int n;scanf("%d",&n);vector<P>p(n);for(auto&q:p){long long x,y;scanf("%lld %lld",&x,&y);q={(ld)x,(ld)y};}
 const ld eps=1e-9L;ld best=0;
 for(int i=0;i<n;i++){
  P A=p[(i+n-1)%n],B=p[(i+1)%n],A2=p[(i+n-2)%n],B2=p[(i+2)%n],P0=p[i];
  P u1=A-A2,u3=B2-B,ab=B-A;ld l1=len(u1),l3=len(u3),lab=len(ab);
  P M=(A+B)*0.5L;ld R=lab/2;
  ld orig=len(P0-A)+len(P0-B);
  auto feas=[&](P q){
   if(cross(u1,q-A)/l1< -eps)return false;
   if(dot(u1,q-A)/l1< -eps)return false;
   if(cross(B-q,u3)/l3< -eps)return false;
   if(dot(q-B,u3)/l3> eps)return false;
   if(cross(ab,q-A)/lab> eps)return false;
   if(len(q-M)>R+eps)return false;
   return true;};
  auto tryp=[&](P q){if(feas(q)){ld v=len(q-A)+len(q-B)-orig;if(v>best)best=v;}};
  tryp(A);tryp(B);
  P rn={ab.y/lab,-ab.x/lab};
  tryp(M+rn*R);
  // lines: point + direction
  P lp[5]={A,A,B,B,A};
  P ld_[5]={u1,P{-u1.y,u1.x},u3,P{-u3.y,u3.x},ab};
  for(int a=0;a<5;a++){
   P d=ld_[a];ld dl=len(d);d=d*(1/dl);
   // circle intersection
   ld t0=dot(M-lp[a],d);P foot=lp[a]+d*t0;ld h2=R*R-dot(foot-M,foot-M);
   if(h2>=-1e-12L){ld hh=sqrtl(max((ld)0,h2));tryp(foot+d*hh);tryp(foot-d*hh);}
   for(int c=a+1;c<5;c++){
    P e=ld_[c];ld den=cross(d,e);
    if(fabsl(den)<1e-18L*len(e))continue;
    ld s=cross(lp[c]-lp[a],e)/den;
    tryp(lp[a]+d*s);
   }
  }
 }
 printf("%.12Lf\n",best);}

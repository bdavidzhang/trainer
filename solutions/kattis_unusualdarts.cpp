#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll X[7],Y[7];
ll cr(int a,int b,int c){return (X[b]-X[a])*(Y[c]-Y[a])-(Y[b]-Y[a])*(X[c]-X[a]);}
int sg(ll v){return (v>0)-(v<0);}
bool onseg(int a,int b,int c){ // c on segment ab (collinear assumed)
 return min(X[a],X[b])<=X[c]&&X[c]<=max(X[a],X[b])&&min(Y[a],Y[b])<=Y[c]&&Y[c]<=max(Y[a],Y[b]);}
bool inter(int a,int b,int c,int d){
 int d1=sg(cr(a,b,c)),d2=sg(cr(a,b,d)),d3=sg(cr(c,d,a)),d4=sg(cr(c,d,b));
 if(d1*d2<0&&d3*d4<0)return true;
 if(d1==0&&onseg(a,b,c))return true; if(d2==0&&onseg(a,b,d))return true;
 if(d3==0&&onseg(c,d,a))return true; if(d4==0&&onseg(c,d,b))return true;
 return false;}
int main(){int T;scanf("%d",&T);while(T--){
 for(int i=0;i<7;i++){double x,y;scanf("%lf %lf",&x,&y);X[i]=llround(x*1000);Y[i]=llround(y*1000);}
 double p;scanf("%lf",&p);
 int pm[7];for(int i=0;i<7;i++)pm[i]=i;
 do{
  bool ok=true;
  for(int i=0;i<7&&ok;i++){int a=pm[i],b=pm[(i+1)%7],c=pm[(i+2)%7];
   // adjacent edges ab, bc: must not overlap
   if(cr(a,b,c)==0){ll dot=(X[a]-X[b])*(X[c]-X[b])+(Y[a]-Y[b])*(Y[c]-Y[b]);if(dot>0)ok=false;}
   for(int j=i+2;j<7&&ok;j++){if(i==0&&j==6)continue;
    if(inter(a,b,pm[j],pm[(j+1)%7]))ok=false;}
  }
  if(ok){ll s=0;for(int i=0;i<7;i++){int a=pm[i],b=pm[(i+1)%7];s+=X[a]*Y[b]-X[b]*Y[a];}
   double ar=fabs((double)s)/2e6/4.0;double q=ar*ar*ar;
   if(fabs(q-p)<1e-5+1e-9){for(int i=0;i<7;i++)printf("%d%c",pm[i]+1,i==6?'\n':' ');break;}}
 }while(next_permutation(pm+1,pm+7));
 }}

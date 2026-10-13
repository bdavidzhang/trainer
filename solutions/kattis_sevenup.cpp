#include <bits/stdc++.h>
using namespace std;
// Face-up set after drawing a set of cards is the closure of the drawn values under
// "position v up -> its hidden card's value is also played"; order independent.
int main(){string s;cin>>s;const string F="A234567";int hid[7],c[7];for(int i=0;i<7;i++)c[i]=4;int nonval=24;
for(int i=0;i<7;i++){size_t p=F.find(s[i]);if(p==string::npos){hid[i]=-1;nonval--;}else{hid[i]=(int)p;c[p]--;}}
// log binomials
vector<double> lf(60,0);for(int i=1;i<60;i++)lf[i]=lf[i-1]+log((double)i);
auto C=[&](int a,int b)->double{if(b<0||b>a)return 0;return exp(lf[a]-lf[b]-lf[a-b]);};
int mT[128];bool bad[128];
for(int T=0;T<128;T++){int m=nonval;for(int v=0;v<7;v++)if(T>>v&1)m+=c[v];mT[T]=m;
 int up=T;bool ch=true;while(ch){ch=false;for(int v=0;v<7;v++)if((up>>v&1)&&hid[v]>=0&&!(up>>hid[v]&1)){up|=1<<hid[v];ch=true;}}
 bad[T]=(up!=127);}
double E=0;
for(int k=0;k<45;k++){
 vector<double> g(128);for(int T=0;T<128;T++)g[T]=C(mT[T],k)/C(45,k);
 // mobius: exact[T]=sum_{S sub T} (-1)^{|T\S|} g[S]
 for(int b=0;b<7;b++)for(int T=0;T<128;T++)if(T>>b&1)g[T]-=g[T^(1<<b)];
 double p=0;for(int T=0;T<128;T++)if(bad[T])p+=g[T];
 E+=p;}
printf("%.10f\n",E);}

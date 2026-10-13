#include <bits/stdc++.h>
using namespace std;
typedef __int128 L;
L g(L a,L b){if(a<0)a=-a;if(b<0)b=-b;while(b){L t=a%b;a=b;b=t;}return a;}
struct F{L n,d;F(L a=0,L b=1){if(b<0){a=-a;b=-b;}L x=g(a,b);if(x==0)x=1;n=a/x;d=b/x;}};
F operator*(F a,F b){L x=g(a.n,b.d),y=g(b.n,a.d);if(!x)x=1;if(!y)y=1;return F((a.n/x)*(b.n/y),(a.d/y)*(b.d/x));}
F operator/(F a,F b){return a*F(b.d,b.n);}
F operator-(F a,F b){L x=g(a.d,b.d);return F(a.n*(b.d/x)-b.n*(a.d/x),a.d/x*b.d);}
int main(){vector<map<string,int>>mol;map<string,int>el;int s,k;
while(cin>>s>>k){if(s==0&&k==0)break;map<string,int>m;for(int i=0;i<k;i++){string e;int c;cin>>e>>c;m[e]+=s*c;if(!el.count(e)){int z=el.size();el[e]=z;}}mol.push_back(m);}
int M=mol.size(),E=el.size();vector<vector<F>>a(E,vector<F>(M));
for(int j=0;j<M;j++)for(auto&p:mol[j])a[el[p.first]][j]=F(p.second);
vector<int>piv(M,-1);int row=0;
for(int c=0;c<M&&row<E;c++){int p=-1;for(int i=row;i<E;i++)if(a[i][c].n!=0){p=i;break;}if(p<0)continue;swap(a[p],a[row]);
F iv=a[row][c];for(int j=0;j<M;j++)a[row][j]=a[row][j]/iv;
for(int i=0;i<E;i++)if(i!=row&&a[i][c].n!=0){F f=a[i][c];for(int j=0;j<M;j++)a[i][j]=a[i][j]-f*a[row][j];}
piv[c]=row++;}
// free variables: set last free var to 1 (others 0)
int fr=-1;for(int c=0;c<M;c++)if(piv[c]<0)fr=c;
vector<F>x(M);if(fr>=0){x[fr]=F(1);for(int c=0;c<M;c++)if(piv[c]>=0)x[c]=F(0)-a[piv[c]][fr];}
L l=1;for(int c=0;c<M;c++){l=l/g(l,x[c].d)*x[c].d;}
vector<L>v(M);L gg=0;for(int c=0;c<M;c++){v[c]=x[c].n*(l/x[c].d);gg=g(gg,v[c]);}
if(!gg)gg=1;int sg=1;for(int c=0;c<M;c++)if(v[c]!=0){if(v[c]<0)sg=-1;break;}
for(int c=0;c<M;c++)printf("%lld%c",(long long)(v[c]/gg*sg),c+1<M?' ':'\n');}

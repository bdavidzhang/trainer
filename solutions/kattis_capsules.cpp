#include <bits/stdc++.h>
using namespace std;
int R,C,g[9][9],reg[9][9],rs[60],used[60];
bool ok(int r,int c,int v){if(v>rs[reg[r][c]])return false;if(used[reg[r][c]]>>v&1)return false;
for(int dr=-1;dr<=1;dr++)for(int dc=-1;dc<=1;dc++){if(!dr&&!dc)continue;int a=r+dr,b=c+dc;if(a<0||b<0||a>=R||b>=C)continue;if(g[a][b]==v)return false;}return true;}
bool solve(){int br=-1,bc=-1,bn=100;
for(int r=0;r<R;r++)for(int c=0;c<C;c++)if(!g[r][c]){int k=0;for(int v=1;v<=rs[reg[r][c]];v++)if(ok(r,c,v))k++;if(k<bn){bn=k;br=r;bc=c;}}
if(br<0)return true;if(bn==0)return false;
for(int v=1;v<=rs[reg[br][bc]];v++)if(ok(br,bc,v)){g[br][bc]=v;used[reg[br][bc]]|=1<<v;if(solve())return true;g[br][bc]=0;used[reg[br][bc]]&=~(1<<v);}
return false;}
int main(){cin>>R>>C;for(int r=0;r<R;r++)for(int c=0;c<C;c++){string s;cin>>s;g[r][c]=s=="-"?0:stoi(s);}
int k;cin>>k;for(int i=0;i<k;i++){int n;cin>>n;rs[i]=n;for(int j=0;j<n;j++){string s;cin>>s;int a,b;sscanf(s.c_str(),"(%d,%d)",&a,&b);reg[a-1][b-1]=i;}}
for(int r=0;r<R;r++)for(int c=0;c<C;c++)if(g[r][c])used[reg[r][c]]|=1<<g[r][c];
solve();for(int r=0;r<R;r++)for(int c=0;c<C;c++)printf("%d%c",g[r][c],c+1<C?' ':'\n');}

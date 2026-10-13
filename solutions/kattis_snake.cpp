#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
// state: head cell (7 bits) + (L-1) directions (2 bits each) from segment i to segment i+1
struct HS{vector<u64>t;size_t cnt=0,mask;HS(){t.assign(1<<16,~0ULL);mask=(1<<16)-1;}
 static u64 h(u64 x){x^=x>>33;x*=0xff51afd7ed558ccdULL;x^=x>>33;x*=0xc4ceb9fe1a85ec53ULL;x^=x>>33;return x;}
 bool ins(u64 x){if(cnt*2>=t.size()){vector<u64>o;o.swap(t);t.assign(o.size()*2,~0ULL);mask=t.size()-1;for(u64 v:o)if(v!=~0ULL){size_t p=h(v)&mask;while(t[p]!=~0ULL)p=(p+1)&mask;t[p]=v;}}
  size_t p=h(x)&mask;while(t[p]!=~0ULL){if(t[p]==x)return false;p=(p+1)&mask;}t[p]=x;cnt++;return true;}
};
int R,C,L;
int dr[4]={-1,0,1,0},dc[4]={0,1,0,-1};
int main(){cin>>R>>C;vector<string>g(R);for(auto&s:g)cin>>s;
 int pos[16];L=0;int ar=0,ac=0;for(int i=0;i<16;i++)pos[i]=-1;
 for(int i=0;i<R;i++)for(int j=0;j<C;j++){char ch=g[i][j];if(ch=='A'){ar=i;ac=j;}else if(ch!='.'){int v=isdigit(ch)?ch-'0':ch-'a'+10;pos[v]=i*C+j;L=max(L,v+1);}}
 auto enc=[&](int*p){u64 s=0;for(int i=L-2;i>=0;i--){int a=p[i],b=p[i+1];int d;int rr=b/C-a/C,cc=b%C-a%C;if(rr==-1)d=0;else if(cc==1)d=1;else if(rr==1)d=2;else d=3;s=s<<2|d;}return s<<7|p[0];};
 HS vis;vector<u64>st;u64 s0=enc(pos);vis.ins(s0);st.push_back(s0);int apple=ar*C+ac;
 while(!st.empty()){u64 s=st.back();st.pop_back();int p[16];p[0]=s&127;u64 d=s>>7;bool occ[100]={0};
  for(int i=1;i<L;i++){int dd=d&3;d>>=2;p[i]=p[i-1]+dr[dd]*C+dc[dd];}
  for(int i=0;i+1<L;i++)occ[p[i]]=true;
  int hr=p[0]/C,hc=p[0]%C;
  // collect moves, sort so the closest to apple is pushed last
  pair<int,u64> mv[4];int nm=0;
  for(int k=0;k<4;k++){int nr=hr+dr[k],nc=hc+dc[k];if(nr<0||nc<0||nr>=R||nc>=C)continue;int np=nr*C+nc;if(occ[np])continue;if(L>=2&&np==p[1])continue;
   if(np==apple){puts("1");return 0;}
   int q[16];q[0]=np;for(int i=1;i<L;i++)q[i]=p[i-1];u64 ns=enc(q);if(vis.ins(ns)){mv[nm++]={abs(nr-ar)+abs(nc-ac),ns};}}
  sort(mv,mv+nm,[](const pair<int,u64>&a,const pair<int,u64>&b){return a.first>b.first;});
  for(int i=0;i<nm;i++)st.push_back(mv[i].second);
 }
 puts("0");}

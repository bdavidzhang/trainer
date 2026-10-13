#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Seg{ll x1,y1,x2,y2;ll len;bool hor;bool top;};
int n; vector<Seg> sg; ll L4; vector<int> byLen; // indices sorted by length desc

// minimal U side on one base given crossing list sorted by x; returns true if some pair has dist<=min(e_i,e_j) and dist<=L4
static bool scanU(const vector<ll>&X,const vector<ll>&E){
 int m=X.size(); static vector<int> st; st.clear();
 for(int i=0;i<m;i++){ while(!st.empty()&&E[st.back()]<E[i])st.pop_back();
  if(!st.empty()){ll D=X[i]-X[st.back()]; if(D<=E[i]&&D<=L4)return true;} st.push_back(i);}
 st.clear();
 for(int i=m-1;i>=0;i--){ while(!st.empty()&&E[st.back()]<E[i])st.pop_back();
  if(!st.empty()){ll D=X[st.back()]-X[i]; if(D<=E[i]&&D<=L4)return true;} st.push_back(i);}
 return false;}

// handles horizontal bases only
bool passH(){
 vector<int> H,V; for(int i=0;i<n;i++)(sg[i].hor?H:V).push_back(i);
 ll VR=0; for(int v:V)if(!sg[v].top)VR++;
 ll lim=VR*(VR-1)/2, cnt=0;
 sort(H.begin(),H.end(),[&](int a,int b){return sg[a].y1<sg[b].y1;});
 vector<int> Va=V,Vr=V;
 sort(Va.begin(),Va.end(),[&](int a,int b){return sg[a].y1<sg[b].y1;});
 sort(Vr.begin(),Vr.end(),[&](int a,int b){return sg[a].y2<sg[b].y2;});
 set<pair<ll,int>> act; size_t pa=0,pr=0;
 vector<ll> X,U,D;
 for(int h:H){ ll y=sg[h].y1;
  while(pa<Va.size()&&sg[Va[pa]].y1<=y){act.insert({sg[Va[pa]].x1,Va[pa]});pa++;}
  while(pr<Vr.size()&&sg[Vr[pr]].y2<y){act.erase({sg[Vr[pr]].x1,Vr[pr]});pr++;}
  X.clear();U.clear();D.clear(); ll dR=0;
  for(auto it=act.lower_bound({sg[h].x1,-1});it!=act.end()&&it->first<=sg[h].x2;++it){
   int v=it->second; X.push_back(it->first);U.push_back(sg[v].y2-y);D.push_back(y-sg[v].y1); if(!sg[v].top)dR++; }
  if(!sg[h].top){cnt+=dR*(dR-1)/2; if(cnt>lim)return true;}
  if(X.size()>=2){ if(scanU(X,U))return true; if(scanU(X,D))return true; }
 }
 // special: U made of the three longest segments, base horizontal
 if(n>=3){ int t[3]={byLen[0],byLen[1],byLen[2]}; int b=-1,cH=0; for(int k=0;k<3;k++)if(sg[t[k]].hor){b=t[k];cH++;}
  if(cH==1){ int p=-1,q=-1; for(int k=0;k<3;k++)if(t[k]!=b){if(p<0)p=t[k];else q=t[k];}
   if(sg[p].x1>sg[q].x1)swap(p,q);
   ll Y=sg[b].y1, xa=sg[p].x1, xb=sg[q].x1, s=xb-xa;
   auto touches=[&](int v){return sg[b].x1<=sg[v].x1&&sg[v].x1<=sg[b].x2&&sg[v].y1<=Y&&Y<=sg[v].y2;};
   if(s>0&&touches(p)&&touches(q)){
    for(int dir=-1;dir<=1;dir+=2){
     bool ok= dir==1 ? (sg[p].y2>=Y+s&&sg[q].y2>=Y+s) : (sg[p].y1<=Y-s&&sg[q].y1<=Y-s);
     if(!ok)continue; ll ly=Y+dir*s;
     vector<int> I; bool many=false;
     for(int i=0;i<n&&!many;i++){ if(!sg[i].hor||i==b||sg[i].y1!=ly)continue;
      if(min(sg[i].x2,xb)-max(sg[i].x1,xa)>0){I.push_back(i); if(I.size()>=4)many=true;} }
     if(many)continue;
     vector<int> movers=I;
     for(int k=0;k<n&&k<8;k++){int m=byLen[k]; if(m==b||m==p||m==q)continue; if(find(I.begin(),I.end(),m)!=I.end())continue; movers.push_back(m);break;}
     for(int m:movers){ vector<pair<ll,ll>> cv; for(int i:I)if(i!=m)cv.push_back({max(sg[i].x1,xa),min(sg[i].x2,xb)});
      sort(cv.begin(),cv.end()); ll cur=xa; int gaps=0; ll glen=0;
      for(auto&c:cv){ if(c.first>cur){gaps++;glen=c.first-cur;} cur=max(cur,c.second);} 
      if(cur<xb){gaps++;glen=xb-cur;}
      if(gaps==0||(gaps==1&&glen<=sg[m].len))return true; }
    }}}}
 return false;}

int main(){int T;scanf("%d",&T);while(T--){scanf("%d",&n);sg.assign(n,Seg());
 for(auto&s:sg){scanf("%lld %lld %lld %lld",&s.x1,&s.y1,&s.x2,&s.y2);s.hor=(s.y1==s.y2);s.len=(s.x2-s.x1)+(s.y2-s.y1);s.top=false;}
 byLen.resize(n);iota(byLen.begin(),byLen.end(),0);
 sort(byLen.begin(),byLen.end(),[&](int a,int b){return sg[a].len>sg[b].len;});
 for(int k=0;k<3;k++)sg[byLen[k]].top=true; L4=sg[byLen[3]].len;
 bool ans=passH();
 if(!ans){ for(auto&s:sg){swap(s.x1,s.y1);swap(s.x2,s.y2);s.hor=!s.hor;} ans=passH(); }
 puts(ans?"yes":"no"); }}

#include <bits/stdc++.h>
using namespace std;
int n,p1[21],p2[21],c[21];
int main(){cin>>n;vector<int>nr;for(int i=0;i<n;i++){char ch;cin>>p1[i]>>p2[i]>>ch;p1[i]--;p2[i]--;c[i]=ch-'a';if(p1[i]>=0)nr.push_back(i);}
 int k=nr.size();int dom[21],oth[21];int ex[21],lb[21],o[21],best[21];bool have=false;int Lreq[21];
 for(int mask=0;mask<(1<<k);mask++){
  for(int i=0;i<n;i++){ex[i]=-1;lb[i]=-1;dom[i]=-1;}
  for(int t=0;t<k;t++){int i=nr[t];if(mask>>t&1){dom[i]=p2[i];oth[i]=p1[i];}else{dom[i]=p1[i];oth[i]=p2[i];}}
  bool ok=true;
  auto demEx=[&](int q,int v){if(c[q]==v)return;if(v<c[q]){ok=false;return;}if(ex[q]!=-1&&ex[q]!=v){ok=false;return;}ex[q]=v;};
  for(int i=n-1;i>=0&&ok;i--){
   if(ex[i]!=-1&&lb[i]>ex[i]){ok=false;break;}
   if(dom[i]<0)continue;
   demEx(dom[i],c[i]);if(!ok)break;
   int q=oth[i];
   if(ex[i]!=-1){demEx(q,ex[i]);Lreq[i]=-1;}
   else{int L=max(lb[i],c[i]);Lreq[i]=L;if(c[q]<L)lb[q]=max(lb[q],L);}
  }
  if(!ok)continue;
  for(int i=0;i<n;i++){
   if(ex[i]!=-1)o[i]=ex[i];
   else if(dom[i]<0)o[i]=max(lb[i],c[i]);
   else{int q=oth[i];o[i]=c[q]>=Lreq[i]?c[q]:o[q];}
  }
  if(!have||lexicographical_compare(o,o+n,best,best+n)){have=true;copy(o,o+n,best);}
 }
 if(!have){puts("-1");return 0;}
 for(int i=0;i<n;i++)printf("%c%c\n",'a'+c[i],'a'+best[i]);}

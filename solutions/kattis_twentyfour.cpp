#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// tokens: numbers >=0 encoded, operators and parens as negative codes
vector<ll> tok;size_t pos;bool bad;
ll expr();
ll factor(){ll t=tok[pos];if(t==-5){pos++;ll v=expr();pos++;return v;}pos++;return t;}
ll term(){ll v=factor();while(pos<tok.size()&&(tok[pos]==-3||tok[pos]==-4)){ll op=tok[pos++];ll w=factor();if(bad)return 0;
  if(op==-3)v*=w;else{if(w==0||v%w!=0){bad=true;return 0;}v/=w;}}return v;}
ll expr(){ll v=term();while(pos<tok.size()&&(tok[pos]==-1||tok[pos]==-2)){ll op=tok[pos++];ll w=term();if(bad)return 0;
  if(op==-1)v+=w;else v-=w;}return v;}
int main(){int a[4];for(int i=0;i<4;i++)cin>>a[i];
 int L[5]={0,1,2,0,1},R[5]={1,2,3,2,3};
 vector<int> masks;
 for(int ms=0;ms<32;ms++){bool ok=true;
  for(int i=0;i<5&&ok;i++)if(ms>>i&1)for(int j=i+1;j<5;j++)if(ms>>j&1){
   bool disj=R[i]<L[j]||R[j]<L[i];bool nest=(L[i]<=L[j]&&R[j]<=R[i])||(L[j]<=L[i]&&R[i]<=R[j]);
   if(!disj&&!nest){ok=false;break;}}
  if(ok)masks.push_back(ms);}
 int p[4]={0,1,2,3};int best=INT_MAX;
 do{int inv=0;for(int i=0;i<4;i++)for(int j=i+1;j<4;j++)if(p[i]>p[j])inv++;
  for(int ops=0;ops<64;ops++)for(int ms:masks){
   int cost=2*inv+__builtin_popcount(ms);if(cost>=best)continue;
   tok.clear();
   for(int i=0;i<4;i++){
    if(i)tok.push_back(-1-((ops>>(2*(i-1)))&3));
    for(int q=0;q<5;q++)if((ms>>q&1)&&L[q]==i)tok.push_back(-5);
    tok.push_back(a[p[i]]);
    for(int q=0;q<5;q++)if((ms>>q&1)&&R[q]==i)tok.push_back(-6);
   }
   pos=0;bad=false;ll v=expr();
   if(!bad&&v==24)best=cost;
  }
 }while(next_permutation(p,p+4));
 if(best==INT_MAX)puts("impossible");else printf("%d\n",best);}

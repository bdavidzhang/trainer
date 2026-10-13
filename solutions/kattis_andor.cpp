#include <bits/stdc++.h>
using namespace std;
int main(){int n;string t;cin>>n>>t;bool rootAnd=t=="A";
vector<vector<int>> lv(n); // -1 T, -2 F, else child count
long long cnt=1;
for(int i=0;i<n;i++){long long nx=0;lv[i].resize(cnt);for(long long j=0;j<cnt;j++){string s;cin>>s;if(s=="T")lv[i][j]=-1;else if(s=="F")lv[i][j]=-2;else{lv[i][j]=stoi(s);nx+=lv[i][j];}}cnt=nx;}
const long long INF=1e18;
vector<long long> cT,cF; // costs of next level
for(int i=n-1;i>=0;i--){vector<long long> nT(lv[i].size()),nF(lv[i].size());size_t p=0;bool isAnd=(i%2==0)?rootAnd:!rootAnd;
 for(size_t j=0;j<lv[i].size();j++){int e=lv[i][j];if(e==-1){nT[j]=0;nF[j]=1;}else if(e==-2){nT[j]=1;nF[j]=0;}else{
   long long sT=0,sF=0,mT=INF,mF=INF;for(int k=0;k<e;k++,p++){sT+=cT[p];sF+=cF[p];mT=min(mT,cT[p]);mF=min(mF,cF[p]);}
   if(isAnd){nT[j]=sT;nF[j]=mF;}else{nT[j]=mT;nF[j]=sF;}}}
 cT=nT;cF=nF;}
cout<<max(cT[0],cF[0])<<"\n";}

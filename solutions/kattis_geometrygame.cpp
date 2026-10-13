#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){ll x[4],y[4];for(int i=0;i<4;i++)cin>>x[i]>>y[i];
ll dx[4],dy[4],len[4];for(int i=0;i<4;i++){int j=(i+1)%4;dx[i]=x[j]-x[i];dy[i]=y[j]-y[i];len[i]=dx[i]*dx[i]+dy[i]*dy[i];}
auto par=[&](int a,int b){return dx[a]*dy[b]-dy[a]*dx[b]==0;};
bool p02=par(0,2),p13=par(1,3);
bool pg=p02&&p13;
bool right=dx[0]*dx[1]+dy[0]*dy[1]==0;
bool rh=len[0]==len[1]&&len[1]==len[2]&&len[2]==len[3];
bool rect=pg&&right;
bool kite=(len[0]==len[3]&&len[1]==len[2])||(len[0]==len[1]&&len[2]==len[3]);
const char*r;
if(rect&&rh)r="square";else if(rect)r="rectangle";else if(rh)r="rhombus";else if(pg)r="parallelogram";else if(p02||p13)r="trapezium";else if(kite)r="kite";else r="none";
puts(r);}

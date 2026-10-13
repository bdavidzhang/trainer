#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n; scanf("%d",&n);
    vector<ll> x(n),y(n);
    for(int i=0;i<n;i++) scanf("%lld %lld",&x[i],&y[i]);
    ll cx,cy,px,py; scanf("%lld %lld %lld %lld",&cx,&cy,&px,&py);
    ll area=0;
    for(int i=0;i<n;i++){int j=(i+1)%n; area+=x[i]*y[j]-x[j]*y[i];}
    int orient=area>0?1:-1;
    ll rx=px-cx,ry=py-cy;
    bool seenIn=false,seenOut=false,par=false,any=false;
    for(int i=0;i<n;i++){
        int j=(i+1)%n;
        ll ex=x[j]-x[i],ey=y[j]-y[i];
        if(ex*(cy-y[i])-ey*(cx-x[i])!=0) continue;
        if(cx<min(x[i],x[j])||cx>max(x[i],x[j])||cy<min(y[i],y[j])||cy>max(y[i],y[j])) continue;
        any=true;
        ll cr=ex*ry-ey*rx;
        if(cr==0) par=true;
        else if((cr>0?1:-1)==orient) seenIn=true; else seenOut=true;
    }
    if(!any||par||(seenIn&&seenOut)) puts("?");
    else puts(seenIn?"inside":"outside");
}

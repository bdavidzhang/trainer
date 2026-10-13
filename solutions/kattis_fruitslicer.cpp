#include <bits/stdc++.h>
using namespace std;
typedef long long ll; typedef long double ld; typedef __int128 LL;
int main(){
    int n; scanf("%d",&n);
    vector<ll> X(n),Y(n);
    for(int i=0;i<n;i++){ double a,b; scanf("%lf %lf",&a,&b); X[i]=llround(a*100); Y[i]=llround(b*100); }
    int ans=1;
    // coincident centres
    for(int i=0;i<n;i++){ int c=0; for(int k=0;k<n;k++) if(X[k]==X[i]&&Y[k]==Y[i]) c++; ans=max(ans,c); }
    const ld EPS=1e-7L;
    for(int i=0;i<n;i++)for(int j=0;j<n;j++){
        ll dx=X[j]-X[i], dy=Y[j]-Y[i];
        if(dx==0&&dy==0) continue;
        ll d2=dx*dx+dy*dy;
        // outer tangents (parallel to d, offset 100 to side s): exact integer test
        for(int s=-1;s<=1;s+=2){
            int c=0;
            for(int k=0;k<n;k++){
                ll cr=dx*(Y[k]-Y[i])-dy*(X[k]-X[i]);
                cr*=s;
                if(cr<0) continue;
                if((LL)cr*cr<=(LL)40000*d2) c++;
            }
            ans=max(ans,c);
        }
        // inner tangents: unit normal u with u.d = 200
        if(d2>=40000){
            ld D=sqrtl((ld)d2);
            ld ca=200.0L/D; ld sa=sqrtl(max((ld)0,1-ca*ca));
            ld ex=dx/D, ey=dy/D;
            for(int s=-1;s<=1;s+=2){
                ld ux=ca*ex-s*sa*ey, uy=ca*ey+s*sa*ex;
                int c=0;
                for(int k=0;k<n;k++){
                    ld v=ux*(X[k]-X[i])+uy*(Y[k]-Y[i]);
                    if(v>=-EPS&&v<=200+EPS) c++;
                }
                ans=max(ans,c);
            }
        }
    }
    printf("%d\n",ans);
}

#include <bits/stdc++.h>
using namespace std;
typedef long double ld;
struct V{ld x,y,z;};
V cr(V a,V b){return {a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x};}
ld dt(V a,V b){return a.x*b.x+a.y*b.y+a.z*b.z;}
ld nm(V a){return sqrtl(dt(a,a));}
V un(V a){ld l=nm(a);return {a.x/l,a.y/l,a.z/l};}
ld ang(V a,V b){return atan2l(nm(cr(a,b)),dt(a,b));}
V rd(){double x,y,z;scanf("%lf %lf %lf",&x,&y,&z);return un(V{(ld)x,(ld)y,(ld)z});}
int main(){
    V P=rd();int n;scanf("%d",&n);
    ld best=1e18;bool inside=false;
    while(n--){
        int k;scanf("%d",&k);vector<V>p(k),nr(k);
        for(int i=0;i<k;i++)p[i]=rd();
        for(int i=0;i<k;i++)nr[i]=un(cr(p[i],p[(i+1)%k]));
        // nearest boundary point overall decides the side: the geodesic to it crosses no coast
        for(int i=0;i<k;i++){
            V A=p[i],B=p[(i+1)%k];
            ld s=dt(P,nr[i]);
            if(dt(cr(A,P),nr[i])>=0&&dt(cr(P,B),nr[i])>=0){
                ld c=sqrtl(max((ld)0,1-s*s));
                ld d=atan2l(fabsl(s),c);
                if(d<best){best=d;inside=s>0;}
            }
        }
        for(int i=0;i<k;i++){
            ld d=ang(P,p[i]);
            if(d<best){
                int pv=(i+k-1)%k,nx=(i+1)%k;
                bool convex=dt(nr[pv],p[nx])>=0;
                bool a=dt(P,nr[pv])>0,b=dt(P,nr[i])>0;
                best=d;inside=convex?(a&&b):(a||b);
            }
        }
    }
    if(inside)best=0;
    printf("%.7Lf\n",best*6371.0L);
}

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m;
// area of square [0,n]^2 on the left side of directed line through (px,py) with direction (dx,dy)
static double leftArea(double px,double py,double dx,double dy){
    double X[4]={0,(double)n,(double)n,0},Y[4]={0,0,(double)n,(double)n};
    double ox[8],oy[8]; int k=0;
    double s[4];
    for(int i=0;i<4;i++) s[i]=dx*(Y[i]-py)-dy*(X[i]-px);
    for(int i=0;i<4;i++){
        int j=(i+1)&3;
        if(s[i]>=0){ox[k]=X[i];oy[k]=Y[i];k++;}
        if((s[i]>0&&s[j]<0)||(s[i]<0&&s[j]>0)){
            double t=s[i]/(s[i]-s[j]);
            ox[k]=X[i]+t*(X[j]-X[i]);oy[k]=Y[i]+t*(Y[j]-Y[i]);k++;
        }
    }
    double a=0;
    for(int i=0;i<k;i++){int j=(i+1)%k;a+=ox[i]*oy[j]-ox[j]*oy[i];}
    return fabs(a)/2;
}
int main(){
    scanf("%d %d",&n,&m);
    vector<int> x(m),y(m);
    for(int i=0;i<m;i++)scanf("%d %d",&x[i],&y[i]);
    double N2=(double)n*n, best=0;
    // corner triangles with the chip as chord midpoint
    for(int i=0;i<m;i++)for(int c=0;c<4;c++){
        int dx=(c&1)?n-x[i]:x[i], dy=(c&2)?n-y[i]:y[i];
        if(2*dx>n||2*dy>n)continue;
        ll lim=2LL*dx*dy; int cnt=0;
        for(int j=0;j<m;j++){
            int ex=(c&1)?n-x[j]:x[j], ey=(c&2)?n-y[j]:y[j];
            if((ll)ex*dy+(ll)ey*dx<=lim)cnt++;
        }
        best=max(best,(double)cnt/m-(double)lim/N2);
    }
    struct V{int dx,dy;bool up;};
    vector<V> v; v.reserve(m);
    for(int i=0;i<m;i++){
        v.clear(); int L=0;
        for(int j=0;j<m;j++) if(j!=i){
            int dx=x[j]-x[i],dy=y[j]-y[i];
            bool up=dy>0||(dy==0&&dx>0);
            if(!up){dx=-dx;dy=-dy;}
            v.push_back({dx,dy,up}); if(up)L++;
        }
        sort(v.begin(),v.end(),[](const V&a,const V&b){return (ll)a.dx*b.dy-(ll)a.dy*b.dx>0;});
        int k=v.size();
        for(int s=0;s<k;){
            int e=s,u=0,l=0;
            while(e<k&&(ll)v[s].dx*v[e].dy-(ll)v[s].dy*v[e].dx==0){ if(v[e].up)u++;else l++; e++; }
            int on=u+l+1;
            int left=L-u, right=(k-L)-l;
            double aL=leftArea(x[i],y[i],v[s].dx,v[s].dy);
            best=max(best,(double)(left+on)/m-aL/N2);
            best=max(best,(double)(right+on)/m-(N2-aL)/N2);
            L=L-u+l;
            s=e;
        }
    }
    printf("%.9f\n",best);
}

#include <bits/stdc++.h>
using namespace std;
int n; double len[9]; double best=0;
// chain of triangles: each new triangle is built on one of the two new edges of the previous one
void rec(double px,double py,double qx,double qy,double d,int used){
    double ux=(qx-px)/d,uy=(qy-py)/d;
    for(int a=0;a<n;a++){ if(used>>a&1)continue;
        for(int b=0;b<n;b++){ if(b==a||(used>>b&1))continue;
            double A=len[a],B=len[b];
            if(A+B<=d||A+d<=B||B+d<=A)continue;
            double t=(A*A-B*B+d*d)/(2*d); double h2=A*A-t*t; if(h2<=0)continue; double h=sqrt(h2);
            for(int s=-1;s<=1;s+=2){
                double rx=px+ux*t-s*uy*h, ry=py+uy*t+s*ux*h;
                if(rx<-1e-9)continue;
                if(rx>best)best=rx;
                int nu=used|1<<a|1<<b;
                if(__builtin_popcount(nu)+2<=n){
                    rec(px,py,rx,ry,A,nu);
                    rec(qx,qy,rx,ry,B,nu);
                }
            }
        }
    }
}
int main(){
    scanf("%d",&n); for(int i=0;i<n;i++)scanf("%lf",&len[i]);
    for(int i=0;i<n;i++)rec(0,0,0,len[i],len[i],1<<i);
    printf("%.7f\n",best);
}

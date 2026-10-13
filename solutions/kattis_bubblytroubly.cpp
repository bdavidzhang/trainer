#include <bits/stdc++.h>
using namespace std;
int n;
long long X[25],Y[25],Z[25],R[25],V[25];
double f[25][25];
int main(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)scanf("%lld %lld %lld %lld %lld",&X[i],&Y[i],&Z[i],&R[i],&V[i]);
    const double PI=acos(-1.0);
    for(int i=0;i<n;i++){
        vector<double> ang;
        ang.push_back(0);ang.push_back(2*PI);
        for(int j=0;j<n;j++){
            if(Z[j]>=Z[i])continue;
            long long dx=X[j]-X[i],dy=Y[j]-Y[i];
            long long d2=dx*dx+dy*dy;
            if(d2>=(R[i]+R[j])*(R[i]+R[j]))continue;
            if(d2<=(R[i]-R[j])*(R[i]-R[j]))continue;
            double d=sqrt((double)d2);
            double base=atan2((double)dy,(double)dx);
            double c=(d2+R[i]*R[i]-R[j]*R[j])/(2.0*d*R[i]);
            c=max(-1.0,min(1.0,c));
            double a=acos(c);
            for(double t:{base-a,base+a}){
                while(t<0)t+=2*PI;
                while(t>=2*PI)t-=2*PI;
                ang.push_back(t);
            }
        }
        sort(ang.begin(),ang.end());
        for(size_t k=0;k+1<ang.size();k++){
            double len=ang[k+1]-ang[k];
            if(len<1e-12)continue;
            double m=(ang[k]+ang[k+1])/2;
            double px=X[i]+R[i]*cos(m),py=Y[i]+R[i]*sin(m);
            int best=-1;
            for(int j=0;j<n;j++){
                if(Z[j]>=Z[i])continue;
                if(X[j]==X[i]&&Y[j]==Y[i]&&R[j]==R[i])continue;
                double ddx=px-X[j],ddy=py-Y[j];
                if(ddx*ddx+ddy*ddy<(double)R[j]*R[j]-1e-9){
                    if(best<0||Z[j]>Z[best])best=j;
                }
            }
            if(best>=0)f[i][best]+=len/(2*PI);
        }
    }
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int a,int b){return Z[a]>Z[b];});
    vector<double> amt(n,0);
    vector<bool> full(n,false);
    int nfull=0;
    double t=0;
    while(nfull<n){
        vector<double> in(n,0);
        in[ord[0]]=100;
        for(int idx=0;idx<n;idx++){
            int i=ord[idx];
            if(full[i]&&in[i]>0){
                for(int j=0;j<n;j++)if(f[i][j]>0)in[j]+=in[i]*f[i][j];
            }
        }
        double best=1e18;
        for(int i=0;i<n;i++)if(!full[i]&&in[i]>1e-10){
            best=min(best,(V[i]-amt[i])/in[i]);
        }
        if(best>1e17){puts("Invalid");return 0;}
        t+=best;
        for(int i=0;i<n;i++)if(!full[i]&&in[i]>1e-10){
            amt[i]+=in[i]*best;
            if(amt[i]>=V[i]-1e-9){full[i]=true;nfull++;}
        }
    }
    printf("%.2f\n",t);
}

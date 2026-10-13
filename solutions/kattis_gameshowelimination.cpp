#include <bits/stdc++.h>
using namespace std;
int n,k;
static double P[11][512][12];
int main(){
    scanf("%d %d",&n,&k);
    int M=1<<(k-1);
    const double gx[3]={0.2386191860831969,0.6612093864662645,0.9324695142031521};
    const double gw[3]={0.4679139345726910,0.3607615730481386,0.1713244923791704};
    // P[d][mask][c]: probability that candidate c places second (c=0 top, 1 = second-highest m2, 2+b = player m2-1-b)
    for(int d=1;d<=k;d++) for(int mask=0;mask<M;mask++){
        int pos[12],cid[12],m=0;
        if(d<k){pos[m]=d;cid[m++]=0;}
        pos[m]=0;cid[m++]=1;
        for(int b=0;b<k-1;b++) if(mask>>b&1){pos[m]=-(1+b);cid[m++]=2+b;}
        double res[12]={};
        int lo=-(k-1), hi=(d<k?d:0)+k;
        for(int a=lo;a<hi;a++) for(int g=0;g<6;g++){
            double x=a+0.5+(g<3?gx[g]:-gx[g-3])*0.5, w=gw[g%3]*0.5;
            double F[12];
            for(int i=0;i<m;i++){ double t=(x-pos[i])/k; F[i]=t<0?0:(t>1?1:t); }
            // prefix/suffix: a0 = prod F, a1 = sum over one w of (1-F_w) prod rest
            double p0[13],p1[13],s0[13],s1[13];
            p0[0]=1;p1[0]=0;
            for(int i=0;i<m;i++){ p0[i+1]=p0[i]*F[i]; p1[i+1]=p1[i]*F[i]+p0[i]*(1-F[i]); }
            s0[m]=1;s1[m]=0;
            for(int i=m-1;i>=0;i--){ s0[i]=s0[i+1]*F[i]; s1[i]=s1[i+1]*F[i]+s0[i+1]*(1-F[i]); }
            for(int j=0;j<m;j++){
                if(x<pos[j]||x>pos[j]+k) continue;
                double v = d<k ? p1[j]*s0[j+1]+p0[j]*s1[j+1] : p0[j]*s0[j+1];
                res[j]+=w*v/k;
            }
        }
        for(int c=0;c<12;c++) P[d][mask][c]=0;
        for(int j=0;j<m;j++) P[d][mask][cid[j]]=res[j];
    }
    // f[m2][mask][d]
    vector<double> f((size_t)(n+1)*M*(k+1),0.0);
    auto at=[&](int m2,int mask,int d)->double&{ return f[((size_t)m2*M+mask)*(k+1)+d]; };
    vector<double> E(n+2,0.0);
    {
        int mask=0; for(int b=0;b<k-1;b++) if(n-2-b>=1) mask|=1<<b;
        at(n-1,mask,1)=1.0;
    }
    for(int m2=n-1;m2>=1;m2--) for(int mask=M-1;mask>=0;mask--){
        // successor when the second-highest slot must be refilled
        int nm2=-1,nmask=0,shift=0;
        if(mask){
            int b0=0; while(!(mask>>b0&1)) b0++;
            nm2=m2-1-b0; shift=1+b0;
        } else if(m2-k>=1){ nm2=m2-k; shift=k; }
        if(nm2>=1){
            for(int b=0;b<k-1;b++){
                int ob=shift+b; bool pr;
                if(ob<=k-2) pr=mask>>ob&1; else pr=(nm2-1-b>=1);
                if(pr) nmask|=1<<b;
            }
        }
        int r=2+__builtin_popcount(mask)+max(0,m2-k);
        for(int d=1;d<=k;d++){
            double pr=at(m2,mask,d); if(pr==0) continue;
            const double*Q=P[d][mask];
            for(int b=0;b<k-1;b++) if(mask>>b&1){
                double q=pr*Q[2+b];
                E[m2-1-b]+=q*(r-1);
                at(m2,mask^(1<<b),d)+=q;
            }
            { // m2 eliminated
                double q=pr*Q[1];
                E[m2]+=q*(r-1);
                if(nm2>=1) at(nm2,nmask,min(k,d+shift))+=q;
            }
            if(d<k){ // top eliminated
                double q=pr*Q[0];
                E[m2+d]+=q*(r-1);
                if(nm2>=1) at(nm2,nmask,min(k,shift))+=q;
            }
        }
    }
    for(int i=1;i<=n;i++) printf("%.9f\n",E[i]+1);
}

#include <bits/stdc++.h>
using namespace std;
int main(){
    double a,b; if(scanf("%lf %lf",&a,&b)!=2) return 0;
    long long tf=llround(a*1000),tr=llround(b*1000);
    vector<long long> v; double s;
    while(scanf("%lf",&s)==1) v.push_back(llround(s*1000));
    for(size_t t=0;t<v.size();t++){
        long long x=v[t],i=x/1000,fr=x%1000,out;
        if(x==0) out=0;
        else if(x<1000) out=1;
        else if(fr<tf) out=i;
        else if(fr>tr) out=i+1;
        else{
            out=i;
            long long lo=i*1000+tf,hi=i*1000+tr;
            for(int u=(int)t-1;u>=0;u--){
                if(v[u]<lo){out=i;break;}
                if(v[u]>hi){out=i+1;break;}
            }
        }
        printf("%lld\n",out);
    }
}

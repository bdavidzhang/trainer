#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n;
char g[22][22][22];
int main(){
    scanf("%d",&n);
    for(int x=0;x<n;x++){
        char buf[64];scanf("%s",buf);
        for(int y=0;y<n;y++){scanf("%s",buf);for(int z=0;z<n;z++)g[x][y][z]=buf[z];}
    }
    // lists
    vector<array<int,3>> Bs,Cs,As;
    for(int x=0;x<n;x++)for(int y=0;y<n;y++)for(int z=0;z<n;z++){
        char c=g[x][y][z];
        if(c=='B')Bs.push_back({x,y,z});
        else if(c=='C')Cs.push_back({x,y,z});
        else if(c=='A')As.push_back({x,y,z});
    }
    const int OFF=3*21*21+5;
    vector<ll> hB(2*OFF+5),hC(2*OFF+5);
    ll ans=0;
    int m=n-1;
    for(int a=0;a<=m;a++)for(int b=-m;b<=m;b++)for(int c=-m;c<=m;c++){
        if(a==0){ if(b<0)continue; if(b==0&&c<=0)continue; }
        if(std::gcd(std::gcd(a,abs(b)),abs(c))!=1)continue;
        bool filled=false;
        for(auto&A:As){
            ll hb=-1;
            int da=a*A[0]+b*A[1]+c*A[2];
            for(int sgn=-1;sgn<=1;sgn+=2){
                int x=A[0]+sgn*a,y=A[1]+sgn*b,z=A[2]+sgn*c;
                int dp=da+sgn*(a*a+b*b+c*c);
                while(x>=0&&x<n&&y>=0&&y<n&&z>=0&&z<n){
                    if(g[x][y][z]=='P'){
                        if(!filled){
                            filled=true;
                            fill(hB.begin(),hB.end(),0);fill(hC.begin(),hC.end(),0);
                            for(auto&p:Bs)hB[a*p[0]+b*p[1]+c*p[2]+OFF]++;
                            for(auto&p:Cs)hC[a*p[0]+b*p[1]+c*p[2]+OFF]++;
                        }
                        if(hb<0)hb=hB[da+OFF];
                        ans+=hb*hC[dp+OFF];
                    }
                    x+=sgn*a;y+=sgn*b;z+=sgn*c;dp+=sgn*(a*a+b*b+c*c);
                }
            }
        }
    }
    printf("%lld\n",ans);
}

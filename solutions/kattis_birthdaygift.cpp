#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const ll MOD=1e9+7;
const int S=90; // state = sum mod 9 * 10 + last digit
typedef vector<vector<ll>> Mat;
Mat mul(const Mat&A,const Mat&B){
    Mat C(S,vector<ll>(S,0));
    for(int i=0;i<S;i++)for(int k=0;k<S;k++){ ll a=A[i][k]; if(!a)continue;
        for(int j=0;j<S;j++) C[i][j]=(C[i][j]+a*B[k][j])%MOD; }
    return C;
}
int main(){
    ll a; int b; scanf("%lld %d",&a,&b);
    if(a==1){ int c=0; for(int d=1;d<=9;d++) if(d%225==b) c++; printf("%d\n",c); return 0; }
    if(a==2){ int c=0; for(int v=10;v<100;v++) if(v/10!=v%10 && v%225==b) c++; printf("%d\n",c); return 0; }
    // prefix of length a-2
    Mat M(S,vector<ll>(S,0));
    for(int sm=0;sm<9;sm++)for(int d=0;d<10;d++)for(int e=0;e<10;e++) if(e!=d)
        M[sm*10+d][((sm+e)%9)*10+e]=1;
    vector<ll> v(S,0);
    for(int d=1;d<=9;d++) v[(d%9)*10+d]=1;
    ll e=a-3;
    while(e>0){
        if(e&1){ vector<ll> w(S,0);
            for(int i=0;i<S;i++) if(v[i]) for(int j=0;j<S;j++) w[j]=(w[j]+v[i]*M[i][j])%MOD;
            v=w; }
        e>>=1; if(e) M=mul(M,M);
    }
    ll ans=0;
    for(int d1=0;d1<10;d1++)for(int d2=0;d2<10;d2++){
        if(d1==d2) continue;
        if((10*d1+d2)%25!=b%25) continue;
        for(int sm=0;sm<9;sm++) if((sm+d1+d2)%9==b%9)
            for(int d=0;d<10;d++) if(d!=d1) ans=(ans+v[sm*10+d])%MOD;
    }
    printf("%lld\n",ans);
}

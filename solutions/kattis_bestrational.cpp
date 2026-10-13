#include <bits/stdc++.h>
using namespace std;
typedef __int128 L; typedef long long ll;
int main(){
    int P; scanf("%d",&P);
    while(P--){
        int K; ll M; char buf[100]; scanf("%d %lld %s",&K,&M,buf);
        // parse x = A / D, D = 1e18
        ll D=1000000000000000000LL, A=0;
        string s(buf); size_t dot=s.find('.');
        string ip = dot==string::npos? s : s.substr(0,dot);
        string fp = dot==string::npos? "" : s.substr(dot+1);
        while(fp.size()<18) fp+='0';
        fp=fp.substr(0,18);
        A=0; for(char ch:fp) A=A*10+(ch-'0');
        ll ipv=0; for(char ch:ip) if(isdigit(ch)) ipv=ipv*10+(ch-'0');
        // x<1 guaranteed; handle integer part generically anyway
        ll a=0,b=1,c=1,d=1; // lo=a/b <= frac <= hi=c/d
        while(b+d<=M){
            L nl=(L)A*b-(L)a*D;   // >=0, x-lo scaled
            L nh=(L)c*D-(L)A*d;   // >=0, hi-x scaled
            if(nl==0||nh==0) break;
            // compare x with mediant
            L cmp=(L)A*(b+d)-(L)(a+c)*D;
            if(cmp>=0){
                ll k=(ll)min<L>(nl/nh,(L)((M-b)/d));
                if(k<1) k=1;
                a+=k*c; b+=k*d;
            } else {
                ll k=(ll)min<L>(nh/nl,(L)((M-d)/b));
                if(k<1) k=1;
                c+=k*a; d+=k*b;
            }
        }
        L nl=(L)A*b-(L)a*D, nh=(L)c*D-(L)A*d;
        ll p,q;
        if(nl*d<=nh*b){p=a;q=b;} else {p=c;q=d;}
        p+=ipv*q;
        printf("%d %lld/%lld\n",K,p,q);
    }
}

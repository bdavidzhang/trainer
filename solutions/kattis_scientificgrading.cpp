#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 LL;
struct Term{ LL c; ll e; };
// sign of sum of c*10^e ; |c| < 1e30, at most ~6 terms
int signSum(vector<Term> t){
    vector<Term> u;
    for(auto&x:t) if(x.c!=0) u.push_back(x);
    if(u.empty()) return 0;
    sort(u.begin(),u.end(),[](const Term&a,const Term&b){return a.e>b.e;});
    vector<ll> dg; int sg=0; // value = sg * sum dg[i]*10^i, dg in [0,9]
    auto norm=[&](){
        // dg holds signed digits; produce sg and nonneg digits
        for(int rep=0;rep<2;rep++){
            ll carry=0;
            for(size_t i=0;i<dg.size();i++){
                ll v=dg[i]+carry; ll r=((v%10)+10)%10; carry=(v-r)/10; dg[i]=r;
            }
            if(carry>=0){
                while(carry>0){dg.push_back(carry%10);carry/=10;}
                break;
            }
            dg.push_back(carry);
            for(auto&v:dg) v=-v;
            sg=-sg;
        }
        while(!dg.empty()&&dg.back()==0) dg.pop_back();
        if(dg.empty()) sg=0;
    };
    ll cur=u[0].e;
    for(size_t k=0;k<u.size();k++){
        ll gap=cur-u[k].e;
        if(sg!=0){
            if(gap>40) return sg;
            dg.insert(dg.begin(),(size_t)gap,0);
        }
        cur=u[k].e;
        // signed digits
        if(sg<0) for(auto&v:dg) v=-v;
        LL c=u[k].c; int cs=c<0?-1:1; if(c<0) c=-c;
        size_t i=0;
        while(c>0){ if(i>=dg.size()) dg.push_back(0); dg[i]+=cs*(ll)(c%10); c/=10; i++; }
        sg=1;
        norm();
    }
    return sg;
}
Term rd(){
    char buf[64]; scanf("%s",buf);
    string s=buf; size_t ep=s.find('e');
    string m=s.substr(0,ep), ex=s.substr(ep+1);
    ll v=0; for(char ch:m) if(isdigit(ch)) v=v*10+(ch-'0');
    if(m[0]=='-') v=-v;
    ll e=atoll(ex.c_str());
    return {(LL)v,e-9};
}
int main(){
    Term x=rd(),y=rd();
    for(int k=0;k<4;k++){
        Term z=rd();
        vector<Term> N; LL D=1; ll shift=0; // true = (sum N)/D
        if(k==0) N={x,y};
        else if(k==1) N={x,{-y.c,y.e}};
        else if(k==2) N={{x.c*y.c,x.e+y.e}};
        else { N={{x.c,x.e-y.e}}; D=y.c; }
        (void)shift;
        int sN=signSum(N);
        bool ok;
        if(sN==0) ok=(z.c==0);
        else {
            // E = z*D - N
            vector<Term> E; E.push_back({z.c*D,z.e});
            for(auto&t:N) E.push_back({-t.c,t.e});
            int sE=signSum(E);
            if(sE==0) ok=true;
            else {
                LL aD=D<0?-D:D;
                vector<Term> A,B;
                for(auto&t:E){A.push_back({t.c*sE,t.e});B.push_back({t.c*sE,t.e});}
                for(auto&t:N) A.push_back({-t.c*sN,t.e-9}); // |E| - 1e-9|N| < 0
                B.push_back({-aD,-9});                       // |E| - 1e-9|D| < 0
                ok=signSum(A)<0&&signSum(B)<0;
            }
        }
        puts(ok?"Correct":"Incorrect");
    }
}

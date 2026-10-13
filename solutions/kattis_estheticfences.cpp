#include <bits/stdc++.h>
using namespace std;
static char dp[31][31][31][1728];
int main(){
    int n; scanf("%d",&n);
    vector<int> red,blue;
    for(int i=0;i<n;i++){int l; char c; scanf("%d %c",&l,&c); (c=='r'?red:blue).push_back(l);}
    if(red.size()>blue.size()) swap(red,blue);
    // red = minority (<=10): +1 ; blue: -1 ; d stored as d+1 in 0..11
    auto enc=[](int a,int b,int c){return (a*12+b)*12+c;};
    dp[0][0][0][enc(1,1,1)]=1;
    int tot=0;
    int stepD[3]={144,12,1};
    for(int phase=0;phase<2;phase++){
        vector<int>& v = phase==0?red:blue;
        int sg = phase==0?1:-1;
        for(int len: v){
            for(int l1=tot;l1>=0;l1--) for(int l2=tot-l1;l2>=0;l2--) for(int l3=tot-l1-l2;l3>=0;l3--){
                char* src=dp[l1][l2][l3];
                char* t[3]={dp[l1+len>30?0:l1+len][l2][l3], dp[l1][l2+len>30?0:l2+len][l3], dp[l1][l2][l3+len>30?0:l3+len]};
                for(int e=0;e<1728;e++) if(src[e]){
                    int dd[3]={e/144,(e/12)%12,e%12};
                    for(int k=0;k<3;k++){
                        int nd=dd[k]+sg;
                        if(nd<0||nd>11) continue;
                        t[k][e+sg*stepD[k]]=1;
                    }
                }
            }
            tot+=len;
        }
    }
    long long best=0;
    for(int l1=1;l1<=tot;l1++) for(int l2=1;l1+l2<=tot;l2++) for(int l3=1;l1+l2+l3<=tot;l3++){
        if(l1+l2<=l3||l1+l3<=l2||l2+l3<=l1) continue;
        long long pr=(long long)l1*l2*l3; if(pr<=best) continue;
        bool ok=false;
        for(int a=0;a<3&&!ok;a++) for(int b=0;b<3&&!ok;b++){ int c=3-a-b; if(c<0||c>2) continue; if(dp[l1][l2][l3][enc(a,b,c)]) ok=true; }
        if(ok) best=pr;
    }
    printf("%lld\n",best);
}

#include <bits/stdc++.h>
using namespace std;
int n; vector<int> fw;
void upd(int i,int v){ for(;i<=n;i+=i&-i) fw[i]+=v; }
int qry(int i){ int s=0; for(;i>0;i-=i&-i) s+=fw[i]; return s; }
int main(){
    int q; scanf("%d %d",&n,&q); fw.assign(n+1,0);
    vector<char> cl(n+1,0); int tot=0;
    while(q--){
        char c; int a,b; scanf(" %c %d",&c,&a);
        if(c=='-'){ cl[a]=1; upd(a,1); tot++; }
        else if(c=='+'){ cl[a]=0; upd(a,-1); tot--; }
        else{
            scanf("%d",&b);
            bool ok=false;
            if(!cl[a]&&!cl[b]){
                int lo=min(a,b), hi=max(a,b);
                int in=qry(hi)-qry(lo);
                ok = in==0 || tot-in==0;
            }
            puts(ok?"possible":"impossible");
        }
    }
}

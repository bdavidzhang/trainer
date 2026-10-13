#include <bits/stdc++.h>
using namespace std;
typedef bitset<2501> B;
int n,k; char s[64];
static inline int id(int p,int c,int a){return (p*41+c)*401+a;}
int main(){
    scanf("%d %d %s",&n,&k,s);
    vector<B> dp((size_t)41*41*401);
    dp[id(0,0,0)][0]=1;
    const char* opts="NACB";
    for(int p=0;p<n;p++) for(int c=0;c<=p;c++) for(int a=0;a<=400;a++){
        const B&cur=dp[id(p,c,a)];
        if(cur.none()) continue;
        for(int o=0;o<4;o++){
            char ch=opts[o];
            if(s[p]!='?'){ if(o<3){ if(s[p]!=ch) continue; } else { if(s[p]=='N'||s[p]=='A'||s[p]=='C') continue; } }
            if(ch=='N') dp[id(p+1,c+1,a)]|=cur;
            else if(ch=='A'){ if(a+c<=400) dp[id(p+1,c,a+c)]|=cur; }
            else if(ch=='C') dp[id(p+1,c,a)]|=cur<<a;
            else dp[id(p+1,c,a)]|=cur;
        }
    }
    int fc=-1,fa=-1;
    for(int c=0;c<=n&&fc<0;c++) for(int a=0;a<=400;a++) if(dp[id(n,c,a)][k]){fc=c;fa=a;break;}
    if(fc<0){puts("-1");return 0;}
    string res(n,'?'); int c=fc,a=fa,kk=k;
    for(int p=n;p>=1;p--){
        char o=s[p-1]; bool done=false;
        for(int t=0;t<4&&!done;t++){
            char ch=opts[t];
            if(o!='?'){ if(t<3){ if(o!=ch) continue; } else { if(o=='N'||o=='A'||o=='C') continue; } }
            if(ch=='N'){ if(c>=1&&dp[id(p-1,c-1,a)][kk]){c--;res[p-1]='N';done=true;} }
            else if(ch=='A'){ if(a>=c&&dp[id(p-1,c,a-c)][kk]){a-=c;res[p-1]='A';done=true;} }
            else if(ch=='C'){ if(kk>=a&&dp[id(p-1,c,a)][kk-a]){kk-=a;res[p-1]='C';done=true;} }
            else { if(dp[id(p-1,c,a)][kk]){res[p-1]=(o=='?'?'B':o);done=true;} }
        }
        if(!done){puts("BUG");return 1;}
    }
    puts(res.c_str());
}

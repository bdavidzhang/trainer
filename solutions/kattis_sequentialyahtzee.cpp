#include <bits/stdc++.h>
using namespace std;
int score(int cat,const int*h){
    int c[7]={0},sum=0,mx=0;
    for(int i=0;i<5;i++){c[h[i]]++;sum+=h[i];}
    for(int v=1;v<=6;v++)mx=max(mx,c[v]);
    if(cat<6)return (cat+1)*c[cat+1];
    auto run=[&](int len){for(int s=1;s+len-1<=6;s++){bool ok=true;for(int v=s;v<s+len;v++)if(!c[v])ok=false;if(ok)return true;}return false;};
    switch(cat){
        case 6:return mx>=3?sum:0;
        case 7:return mx>=4?sum:0;
        case 8:{bool t=false,p=false;for(int v=1;v<=6;v++){if(c[v]==3)t=true;if(c[v]==2)p=true;}return t&&p?25:0;}
        case 9:return run(4)?30:0;
        case 10:return run(5)?40:0;
        case 11:return sum;
        default:return mx==5?50:0;
    }
}
int main(){
    int n;scanf("%d",&n);vector<int> s(n);for(auto&x:s)scanf("%d",&x);
    vector<vector<int>> dp(14,vector<int>(n+1,-1));
    dp[0][0]=0;
    for(int cat=0;cat<13;cat++)for(int pos=0;pos+5<=n;pos++){
        int base=dp[cat][pos];if(base<0)continue;
        for(int m1=0;m1<32;m1++){
            int h1[5],q=pos+5;bool ok=true;
            for(int i=0;i<5;i++){if(m1>>i&1){if(q>=n){ok=false;break;}h1[i]=s[q++];}else h1[i]=s[pos+i];}
            if(!ok)continue;
            for(int m2=0;m2<32;m2++){
                if(m1==0&&m2)break;
                int h2[5],q2=q;bool ok2=true;
                for(int i=0;i<5;i++){if(m2>>i&1){if(q2>=n){ok2=false;break;}h2[i]=s[q2++];}else h2[i]=h1[i];}
                if(!ok2)continue;
                int v=base+score(cat,h2);
                if(v>dp[cat+1][q2])dp[cat+1][q2]=v;
            }
        }
    }
    int ans=0;for(int p=0;p<=n;p++)ans=max(ans,dp[13][p]);
    printf("%d\n",ans);
}

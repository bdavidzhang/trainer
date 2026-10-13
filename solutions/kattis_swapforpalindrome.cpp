#include <bits/stdc++.h>
using namespace std;
int n; string s;
static int pre[26][5002];
int tot[26];
inline int inside(int c,int l,int r){return pre[c][r+1]-pre[c][l];}
int main(){
    cin>>s; n=s.size();
    for(int c=0;c<26;c++){for(int i=0;i<n;i++)pre[c][i+1]=pre[c][i]+(s[i]-'a'==c); tot[c]=pre[c][n];}
    int best=1;
    for(int par=0;par<2;par++){
        for(int i=0;i+par<n;i++){
            int l=i,r=i+par; int mm=0; int ma[2],mb[2];
            while(l>=0&&r<n){
                if(s[l]!=s[r]){ if(mm==2)break; ma[mm]=s[l]-'a'; mb[mm]=s[r]-'a'; mm++; }
                int len=r-l+1;
                if(len>best){
                    bool ok=false;
                    if(mm==0) ok=true;
                    else if(mm==1){
                        int a=ma[0],b=mb[0];
                        if(par==0){int c=s[i]-'a'; if(c==a||c==b)ok=true;}
                        if(!ok && (tot[a]-inside(a,l,r)>0 || tot[b]-inside(b,l,r)>0)) ok=true;
                    } else {
                        if((ma[0]==ma[1]&&mb[0]==mb[1])||(ma[0]==mb[1]&&mb[0]==ma[1])) ok=true;
                    }
                    if(ok)best=len;
                }
                l--;r++;
            }
        }
    }
    printf("%d\n",best);
}

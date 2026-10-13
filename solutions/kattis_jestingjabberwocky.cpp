#include <bits/stdc++.h>
using namespace std;
int main(){
    string s; cin>>s; int n=s.size();
    string p="cdhs"; int best=0;
    do{
        int id[256]; for(int i=0;i<4;i++) id[(int)p[i]]=i;
        int f[4]={0,0,0,0};
        for(char ch:s){
            int k=id[(int)ch];
            int mx=0; for(int j=0;j<=k;j++) mx=max(mx,f[j]);
            f[k]=mx+1;
        }
        for(int j=0;j<4;j++) best=max(best,f[j]);
    }while(next_permutation(p.begin(),p.end()));
    printf("%d\n",n-best);
}

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int m,k,c;
ll C[30][30];
ll rankOf(int mask){
    // lexicographic rank of the sorted k-subset
    ll r=0;int prev=-1;int left=k;
    for(int x=0;x<m;x++)if(mask>>x&1){
        for(int y=prev+1;y<x;y++)r+=C[m-1-y][left-1];
        prev=x;left--;
    }
    return r;
}
int main(){
    for(int i=0;i<30;i++){C[i][0]=1;for(int j=1;j<=i;j++)C[i][j]=C[i-1][j-1]+(j<=i-1?C[i-1][j]:0);}
    string line;
    getline(cin,line);
    sscanf(line.c_str(),"%d %d %d",&m,&k,&c);
    vector<int> ch;
    while(getline(cin,line)){
        for(char&x:line)if(x=='['||x==']'||x==',')x=' ';
        stringstream ss(line);int v,mask=0,any=0;
        while(ss>>v){mask|=1<<v;any=1;}
        if(any)ch.push_back(mask);
    }
    int n=ch.size();
    vector<ll> ans(n,-1);
    bool det=false;int key=0;int U=0;int start=0;
    auto unique1=[&](int u){return __builtin_popcount(u)==k||m==k;};
    for(int i=0;i<n;i++){
        if(det){
            if((ch[i]&~key)==0){ans[i]=rankOf(key);continue;}
            det=false;U=0;start=i;
        }
        U|=ch[i];
        if(__builtin_popcount(U)>k){
            // give up on past chords, start over
            start=i;U=ch[i];
        }
        if(unique1(U)){
            key=(m==k)?((1<<m)-1):U;
            det=true;
            ll r=rankOf(key);
            for(int j=start;j<=i;j++)ans[j]=r;
        }
    }
    for(int i=0;i<n;i++){
        if(ans[i]<0)puts("?");else printf("%lld\n",ans[i]);
    }
}

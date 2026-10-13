#include <bits/stdc++.h>
using namespace std;
int main(){
    string s;cin>>s;int n=s.size();
    vector<int> sa(n),rk(n),tmp(n);
    iota(sa.begin(),sa.end(),0);
    for(int i=0;i<n;i++)rk[i]=s[i];
    for(int k=1;;k<<=1){
        auto cmp=[&](int a,int b){
            if(rk[a]!=rk[b])return rk[a]<rk[b];
            int ra=a+k<n?rk[a+k]:-1,rb=b+k<n?rk[b+k]:-1;
            return ra<rb;};
        sort(sa.begin(),sa.end(),cmp);
        tmp[sa[0]]=0;
        for(int i=1;i<n;i++)tmp[sa[i]]=tmp[sa[i-1]]+(cmp(sa[i-1],sa[i])?1:0);
        rk=tmp;
        if(rk[sa[n-1]]==n-1)break;
    }
    int best=0,pos=0,h=0;
    vector<int> lcp(n,0);
    for(int i=0;i<n;i++){
        if(rk[i]==0){h=0;continue;}
        int j=sa[rk[i]-1];
        while(i+h<n&&j+h<n&&s[i+h]==s[j+h])h++;
        lcp[rk[i]]=h;
        if(h>0)h--;
    }
    for(int r=1;r<n;r++)if(lcp[r]>best){best=lcp[r];pos=sa[r];}
    cout<<s.substr(pos,best)<<"\n";
}

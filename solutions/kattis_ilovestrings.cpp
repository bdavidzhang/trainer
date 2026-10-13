#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long u64;
typedef unsigned __int128 u128;
int main(){
    string s;cin>>s;int n=s.size();
    const u64 MOD=1000000007ULL;
    // map chars: vowels 0..9, consonants 0..41
    int vid[256],cid[256];memset(vid,-1,sizeof vid);memset(cid,-1,sizeof cid);
    string vs="aeiouAEIOU";int nv=0,nc=0;
    for(char c:vs)vid[(unsigned char)c]=nv++;
    for(int c='a';c<='z';c++)if(vid[c]<0)cid[c]=nc++;
    for(int c='A';c<='Z';c++)if(vid[c]<0)cid[c]=nc++;
    static u64 P[10][42],Q[10][42]; // Q[c][x]: pairs (consonant x, later vowel c) to the right
    u64 PA[10]={0},QC[10]={0};
    u64 pre[10]={0},suf[10]={0};
    for(int i=n-1;i>=0;i--){
        unsigned char ch=s[i];
        if(vid[ch]>=0)suf[vid[ch]]++;
        else{int x=cid[ch];for(int c=0;c<10;c++){Q[c][x]+=suf[c];QC[c]+=suf[c];}}
    }
    u64 ans=0;
    for(int j=0;j<n;j++){
        unsigned char ch=s[j];
        if(vid[ch]>=0){
            int b=vid[ch];
            suf[b]--;
            u128 tot=0;
            for(int a=0;a<10;a++){
                if(a==b||PA[a]==0)continue;
                for(int c=0;c<10;c++){
                    if(c==b||c==a||QC[c]==0)continue;
                    u128 S=0;
                    const u64*p=P[a];const u64*q=Q[c];
                    for(int x=0;x<42;x++)S+=(u128)p[x]*q[x];
                    tot+=(u128)PA[a]*QC[c]-S;
                }
            }
            ans=(ans+(u64)(tot%MOD))%MOD;
            pre[b]++;
        }else{
            int x=cid[ch];
            for(int c=0;c<10;c++){Q[c][x]-=suf[c];QC[c]-=suf[c];}
            for(int a=0;a<10;a++){P[a][x]+=pre[a];PA[a]+=pre[a];}
        }
    }
    printf("%llu\n",ans);
}

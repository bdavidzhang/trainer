#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,l,k;if(scanf("%d %d %d",&n,&l,&k)!=3)return 0;
    vector<string> id(n);vector<unsigned char> v((size_t)n*l);
    char buf[64];
    for(int i=0;i<n;i++){scanf("%s",buf);id[i]=buf;for(int j=0;j<l;j++){int x;scanf("%d",&x);v[(size_t)i*l+j]=(unsigned char)x;}}
    auto dist=[&](int a,int b){const unsigned char*p=&v[(size_t)a*l],*q=&v[(size_t)b*l];int s=0;for(int j=0;j<l;j++){int d=(int)p[j]-(int)q[j];s+=d<0?-d:d;}return s;};
    vector<int> md(n,INT_MAX);vector<char> used(n,0);
    int best=0,bd=-1;
    for(int i=0;i<n;i++){int d=dist(0,i);if(d>bd){bd=d;best=i;}}
    string out;
    for(int step=0;step<k;step++){
        used[best]=1;out+=id[best];out+='\n';
        int c=best;int nb=-1,nd=-1;
        for(int i=0;i<n;i++){int d=dist(c,i);if(d<md[i])md[i]=d;if(!used[i]&&md[i]>nd){nd=md[i];nb=i;}}
        best=nb;
    }
    fputs(out.c_str(),stdout);
}

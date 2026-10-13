#include <bits/stdc++.h>
using namespace std;
int ask(int a,int b){
    if(!a)return b; if(!b)return a;
    printf("? %d %d\n",a,b);fflush(stdout);
    int r;if(scanf("%d",&r)!=1||r<0)exit(0);
    return r;
}
int main(){
    int n,k;if(scanf("%d %d",&n,&k)!=2)return 0;
    int sz=1;while(sz<n)sz<<=1;
    vector<int> t(2*sz,0);
    for(int i=0;i<n;i++)t[sz+i]=i+1;
    for(int i=sz-1;i>=1;i--)t[i]=ask(t[2*i],t[2*i+1]);
    vector<int> res;
    for(int it=0;it<k;it++){
        int w=t[1];res.push_back(w);
        if(it==k-1)break;
        int i=sz+w-1;t[i]=0;
        for(i>>=1;i>=1;i>>=1)t[i]=ask(t[2*i],t[2*i+1]);
    }
    printf("!");for(int x:res)printf(" %d",x);puts("");fflush(stdout);
}

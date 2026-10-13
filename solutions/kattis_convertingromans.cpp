#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; 
    if(scanf("%d",&n)!=1) return 0;
    static char buf[300005];
    int val[256]; memset(val,0,sizeof val);
    val['I']=1;val['V']=5;val['X']=10;val['L']=50;val['C']=100;val['D']=500;val['M']=1000;
    while(n--){
        if(scanf("%300004s",buf)!=1) break;
        int len=strlen(buf);
        long long s=0; int mx=0;
        for(int i=len-1;i>=0;i--){
            int v=val[(unsigned char)buf[i]];
            if(v<mx) s-=v; else { s+=v; mx=v; }
        }
        printf("%lld\n",s);
    }
}

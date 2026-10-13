#include <bits/stdc++.h>
using namespace std;
int main(){
    int r,c; static char s[200005];
    scanf("%d %d %s",&r,&c,s);
    long long ans=0; long long od=0, orr=0;
    // upper region: D opens, R closes; lower region: R opens, D closes
    for(int i=0;s[i];i++){
        if(s[i]=='D'){ od++; if(orr>0){orr--;ans++;} }
        else { orr++; if(od>0){od--;ans++;} }
    }
    printf("%lld\n",ans);
}

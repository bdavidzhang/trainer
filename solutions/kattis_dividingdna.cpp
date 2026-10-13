#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; if(scanf("%d",&n)!=1) return 0;
    int s=0,cnt=0;
    for(int e=1;e<=n;e++){
        printf("? %d %d\n",s,e); fflush(stdout);
        char buf[32]; if(scanf("%31s",buf)!=1) return 0;
        if(buf[0]=='a'){cnt++;s=e;}
    }
    printf("! %d\n",cnt); fflush(stdout);
}

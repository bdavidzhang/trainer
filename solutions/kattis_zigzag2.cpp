#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n);
    int prev=0, dir=0, ans=1;
    for(int i=0;i<n;i++){
        int x; scanf("%d",&x);
        if(i){
            int d = x>prev?1:(x<prev?-1:0);
            if(d!=0 && d!=dir){ans++;dir=d;}
        }
        prev=x;
    }
    printf("%d\n",ans);
}

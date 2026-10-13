#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n);
    int c[10]={0};
    for(int i=0;i<n;i++){int d;scanf("%d",&d);c[d]++;}
    bool unit=c[1]||c[3]||c[7];
    bool five=c[5]>0;
    bool ev=c[2]||c[4]||c[6]||c[8];
    if(unit||(five&&ev)) puts("1"); else printf("%d\n",n);
}

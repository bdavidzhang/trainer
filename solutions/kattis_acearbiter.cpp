#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n);
    int pa=0,pb=0;
    for(int i=1;i<=n;i++){
        int x,y; scanf("%d-%d",&x,&y);
        int s=x+y;
        // next round is s+1; Alice serves rounds r with (r/2) even
        bool alice=(((s+1)/2)%2==0);
        int a=alice?x:y, b=alice?y:x;
        bool ok=true;
        if(a==11&&b==11) ok=false;
        if(a<pa||b<pb) ok=false;
        if((pa==11||pb==11)&&(a!=pa||b!=pb)) ok=false;
        if(!ok){ printf("error %d\n",i); return 0; }
        pa=a; pb=b;
    }
    puts("ok");
}

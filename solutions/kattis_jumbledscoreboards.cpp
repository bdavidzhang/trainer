#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; scanf("%d",&n); int pa=-1,pb=-1; bool ok=true;
    for(int i=0;i<n;i++){int a,b; scanf("%d %d",&a,&b); if(a<pa||b<pb) ok=false; pa=a;pb=b;}
    puts(ok?"yes":"no");
}

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n,q; scanf("%d %d",&n,&q);
    static char s[200005]; scanf("%s",s);
    vector<int> p(n+1,0);
    for(int i=0;i<n;i++) p[i+1]=p[i]+(s[i]=='8');
    while(q--){
        int l,r; ll x,y; scanf("%d %d %lld %lld",&l,&r,&x,&y);
        ll b=p[r]-p[l-1], a=(r-l+1)-b;
        x=llabs(x); y=llabs(y);
        puts((max(x,y)<=a+b && x+y<=a+2*b)?"YES":"NO");
    }
}

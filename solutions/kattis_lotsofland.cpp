#include <bits/stdc++.h>
using namespace std;
int main(){
    int l,w,n; scanf("%d %d %d",&l,&w,&n);
    if((l*w)%n){ puts("impossible"); return 0; }
    int a=std::gcd(n,l), b=n/a; // a | l and b | w
    int h=l/a, v=w/b;
    for(int i=0;i<l;i++){
        string r(w,'A');
        for(int j=0;j<w;j++) r[j]='A'+(i/h)*b+(j/v);
        puts(r.c_str());
    }
}

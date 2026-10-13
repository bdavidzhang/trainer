#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
ull pos(const string&g){ ull r=0; int b=0; for(char c:g){ b^=(c-'0'); r=r*2+b; } return r; }
int main(){
    int n; string a,b; cin>>n>>a>>b;
    cout<<pos(b)-pos(a)-1<<endl;
}

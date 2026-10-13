#include <bits/stdc++.h>
using namespace std;
int main(){int n;cin>>n;vector<long long>s,t,d;int dep=0;bool bad=false;
    for(int i=0;i<n;i++){string x;cin>>x;long long a=0,b=0;for(char c:x){if(c=='s')a++;else if(c=='t')b++;}
        int my;if(x.back()=='{'){my=dep;dep++;}else{dep--;my=dep;}
        if(my==0){if(a||b)bad=true;}else{s.push_back(a);t.push_back(b);d.push_back(my);}}
    if(bad){puts("-1");return 0;}
    if(s.empty()){puts("1");return 0;}
    for(long long T=1;T<=200000;T++){
        long long I=-1;bool ok=true;
        for(size_t j=0;j<s.size();j++){long long v=s[j]+t[j]*T;
            if(v<=0||v%d[j]){ok=false;break;}
            long long q=v/d[j];if(I<0)I=q;else if(I!=q){ok=false;break;}}
        if(ok){printf("%lld\n",T);return 0;}
    }
    puts("-1");}

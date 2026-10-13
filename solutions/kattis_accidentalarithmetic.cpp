#include <bits/stdc++.h>
using namespace std;
int main(){
    string s;cin>>s;
    int n=s.size();
    // Only the first term has nonzero expected sign. a_L = prefix_L / 10^(L-1).
    long double a=0,pw=1,sum=0,ans=0;
    for(int L=1;L<=n;L++){
        a+= (s[L-1]-'0')*pw;
        pw/=10;
        if(L<n)sum+=a; else ans=0.9L*sum+a;
    }
    printf("%.10Lf\n",ans);
}

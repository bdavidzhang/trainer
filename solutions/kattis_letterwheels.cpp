#include <bits/stdc++.h>
using namespace std;
int n;
vector<char> compat(const string&a,const string&b){
    vector<char> r(n,1);
    for(int k=0;k<n;k++){
        for(int c=0;c<n;c++){int d=c+k; if(d>=n)d-=n; if(a[c]==b[d]){r[k]=0;break;}}
    }
    return r;
}
int main(){
    string s[3];cin>>s[0]>>s[1]>>s[2];n=s[0].size();
    auto c12=compat(s[0],s[1]),c13=compat(s[0],s[2]),c23=compat(s[1],s[2]);
    int best=INT_MAX;
    for(int i=0;i<n;i++){ if(!c12[i])continue;
        for(int j=0;j<n;j++){ if(!c13[j])continue; int d=j-i; if(d<0)d+=n; if(!c23[d])continue;
            for(int a=0;a<2;a++)for(int b=0;b<2;b++){
                int x=a?i-n:i,y=b?j-n:j;
                int c=max({0,x,y})-min({0,x,y});
                best=min(best,c);
            }
        }
    }
    printf("%d\n",best==INT_MAX?-1:best);
}

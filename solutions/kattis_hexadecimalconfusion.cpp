#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;cin>>n;long long mx=0,mn=0;
    while(n--){
        string s;cin>>s;string a=s,b=s;
        for(size_t i=0;i<s.size();i++){
            if(s[i]=='8'||s[i]=='B'){a[i]='B';b[i]='8';}
            if(s[i]=='0'||s[i]=='D'){a[i]='D';b[i]=(i==0&&s.size()>1)?'D':'0';}
        }
        mx+=stoll(a,nullptr,16);mn+=stoll(b,nullptr,16);
    }
    printf("%llX\n%llX\n",mx,mn);
}

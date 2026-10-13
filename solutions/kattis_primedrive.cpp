#include <bits/stdc++.h>
using namespace std;
bool isp(int x){
    if(x<2)return false;
    for(int i=2;i*i<=x;i++)if(x%i==0)return false;
    return true;
}
int main(){
    string s;int x;
    while(cin>>s>>x){
        if(s=="END"&&x==0)break;
        while(x<=9999&&!isp(x))x++;
        if(x>9999){
            x=2;
            int i=2;
            while(i>=0){
                if(s[i]=='Z'){s[i]='A';i--;}
                else{s[i]++;break;}
            }
        }
        printf("%s %04d\n",s.c_str(),x);
    }
}

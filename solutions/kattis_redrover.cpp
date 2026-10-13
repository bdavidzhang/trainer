#include <bits/stdc++.h>
using namespace std;
int main(){
    string s;cin>>s;
    int n=s.size(),best=n;
    for(int i=0;i<n;i++)for(int len=2;i+len<=n;len++){
        string m=s.substr(i,len);
        int cnt=0;
        for(int p=0;p+len<=n;){
            if(s.compare(p,len,m)==0){cnt++;p+=len;}
            else p++;
        }
        best=min(best,n-cnt*(len-1)+len);
    }
    cout<<best<<endl;
}

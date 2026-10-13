#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;scanf("%d",&n);
    int k=n/2;
    string s;
    s+=to_string(k)+"\n";
    for(int i=0;i<k;i++){
        if(i)s+=' ';
        s+=(i==0&&(n&1))?'3':'2';
    }
    s+='\n';
    fputs(s.c_str(),stdout);
}

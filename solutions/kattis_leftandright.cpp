#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;string s;cin>>n>>s;
    string out;
    for(int i=0;i<n;){
        int j=i;while(j<n-1&&s[j]=='L')j++;
        for(int k=j;k>=i;k--){out+=to_string(k+1);out+='\n';}
        i=j+1;
    }
    fputs(out.c_str(),stdout);
}

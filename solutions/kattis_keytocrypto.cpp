#include <bits/stdc++.h>
using namespace std;
int main(){
    string c,k; cin>>c>>k;
    string m;
    for(size_t i=0;i<c.size();i++){
        int sh=k[i]-'A';
        char ch='A'+((c[i]-'A'-sh)%26+26)%26;
        m+=ch; k+=ch;
    }
    cout<<m<<"\n";
}

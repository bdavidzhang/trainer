#include <bits/stdc++.h>
using namespace std;
int main(){
    string s[4]; cin>>s[1]>>s[2]>>s[3];
    size_t p[4]={0,0,0,0};
    string out;
    auto head=[&](int i)->char{ return p[i]<s[i].size()?s[i][p[i]]:0; };
    while(true){
        bool found=false;
        for(int x=1;x<=3&&!found;x++){
            int a=x%3+1,b=a%3+1; char ch='0'+x;
            if(head(a)==ch&&head(b)==ch){ out+=ch; p[a]++; p[b]++; found=true; }
        }
        if(!found) break;
    }
    cout<<out<<"\n";
}

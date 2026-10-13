#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; cin>>n; int c=0; string s;
    while(n--){cin>>s; if(s.size()>=3&&s.compare(0,3,"+39")==0){size_t l=s.size()-3; if(l==9||l==10)c++;}}
    cout<<c<<"\n";
}

#include <bits/stdc++.h>
using namespace std;
int main(){
    int n; cin>>n; set<string> s; string t;
    while(n--){cin>>t;s.insert(t);}
    cout<<s.size()+1<<"\n";
}

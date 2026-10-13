#include <bits/stdc++.h>
using namespace std;
int main(){
    vector<int> code(10001,0); int len=0;
    for(int b=0;b<5;b++){
        string q;
        for(int c=0;c<26;c++) if(((c+1)>>b)&1) q+=char('a'+c);
        cout<<"? "<<q<<endl;
        int n; cin>>n;
        for(int i=0;i<n;i++){ int p; cin>>p; code[p]|=1<<b; len=max(len,p); }
    }
    string s;
    for(int i=1;i<=len;i++) s+=char('a'+code[i]-1);
    cout<<"! "<<s<<endl;
    string r; cin>>r;
}

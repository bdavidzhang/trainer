#include <bits/stdc++.h>
using namespace std;
int main(){
    string s;
    while(getline(cin,s)){
        while(!s.empty()&&isspace((unsigned char)s.back())) s.pop_back();
        if(s.empty()) continue;
        int n=s.size();
        set<char> all(s.begin(),s.end()); size_t k=all.size();
        auto full=[&](int l,int r){ if(l>r) return false; set<char> t(s.begin()+l,s.begin()+r+1); return t.size()==k; };
        set<string> res;
        for(int l=0;l<n;l++) for(int r=l;r<n;r++){
            if(l==0&&r==n-1) continue;
            if(full(l,r)&&!full(l+1,r)&&!full(l,r-1)) res.insert(s.substr(l,r-l+1));
        }
        printf("%d\n",(int)res.size());
    }
}

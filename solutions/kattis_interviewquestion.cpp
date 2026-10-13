#include <bits/stdc++.h>
using namespace std;
int main(){
    int c,d; cin>>c>>d;
    long long ga=0,gb=0;
    for(int i=c;i<=d;i++){
        string s; cin>>s;
        if(s.find("Fizz")!=string::npos) ga=std::gcd(ga,(long long)i);
        if(s.find("Buzz")!=string::npos) gb=std::gcd(gb,(long long)i);
    }
    if(!ga) ga=d+1;
    if(!gb) gb=d+1;
    cout<<ga<<" "<<gb<<"\n";
}

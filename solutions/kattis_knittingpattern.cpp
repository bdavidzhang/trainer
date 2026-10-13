#include <bits/stdc++.h>
using namespace std;
int main(){
    long long n,p; cin>>n>>p;
    long long side=(n-p)/2;
    long long k=side/p;
    long long left=n-p-2*k*p;
    if(left==p) left=0;
    cout<<left<<endl;
}

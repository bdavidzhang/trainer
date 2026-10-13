#include <bits/stdc++.h>
using namespace std;

int main(){
    double x,y; cin>>x>>y;
    printf("%.12f\n", x*(100-y)/(y*(100-x)));
}

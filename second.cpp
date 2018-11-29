#include <vector>
#include <list>
#include <deque>
#include <cstdlib>
#include <cmath>
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

typedef unsigned long long int llu;


llu at[200000];
llu au[200000];
llu bt[200000];
llu bu[200000];
llu L;

long double getdxright(llu index,long double time) {
  if(time<bt[index]) return L;
  return (long double) L- bu[index]*(time-bt[index]);
}

long double getposleft(llu index,long double time) {
    if(time<at[index]) return 0;
    return (long double) au[index]*(time-at[index]);
}


int main(int argc, char* argv[]) {
    int K;
    int collision=0;
    llu N,i,j,k;
    cin >> N >> L >> K;
    for ( i=0;i<N;i++){
      cin >> at[i] >> au[i];
    }
    for ( i=0;i<N;i++){
      cin >> bt[i] >> bu[i];
    }

    for(k=0;k<K;k++) {
        llu sfa=1,sfb=1;
        long double lefti=0.0,righti=(double) L,mid=(double) lefti+(righti-lefti)/2;
        long double temp,maxx=0.0,maxx2=0.0;
        while(1 == 1)  {
            maxx=0.0;
            maxx2=L;
            mid=lefti+(righti-lefti)/2;
            for(i=0;i<N;i++) {
                temp=getposleft(i,mid);
                if(temp>maxx) { maxx=temp; sfa=i+1;}
            }
            for(i=0;i<N;i++) {
                temp=getdxright(i,mid);
                if (temp<maxx2) {maxx2=temp; sfb=i+1; }
            }
            if(maxx>maxx2)
                 righti=mid-1;
            else
                lefti=mid+1;
            if (abs(maxx- maxx2) < 1)  {
                            break;
            }

         } //cout<<"next K"<<endl;
    cout << sfa <<" "<<sfb  <<endl;
    au[sfa-1]=bu[sfb-1]=0;
    }
    return 0;
}

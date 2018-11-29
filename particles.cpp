#include <iostream>
//#include <stdlib.h>
using namespace std;
typedef unsigned long long int ulli;
long double at[200000],av[200000],bt[200000],bv[200000];
long double xa[200000],xb[200000];
ulli n,k;
int l;
ulli max_a,max_b,max_xa,max_xb;

float abso(float x){
  if (x > 0 )return x;
  else return -x ;
}

void computex(float t){

  for (ulli i = 0 ; i < n ; i++)
  {
    if (at[i] >= t ) xa[i] = 0;
    else  xa[i] = av[i] * (t - at[i]);
    if (bt[i] >= t) xb[i] = l;
    else  xb[i] = l - bv[i] * (t - bt[i]);
  }
}


int sigkrousi(float t){

   computex(t);
   max_xa = xa[0];
   max_xb = xb[0];
  for(ulli i = 1;i < n;i++){
    if (xa[i] > max_xa)
    {
      max_xa = xa[i];
      max_a = i;
      //cout << max_xa << endl;
    }
    if (xb[i] < max_xb)
    {
       max_xb = xb[i];
       max_b = i;
     }
//     cout << xa[i] << " " << xb[i] << endl;
  //   cout << "brhka max" << endl;
  }
//    max_xa > max_xb // abso(max_xa - max_xb) < 1
  if (max_xa > max_xb  ) return 1;
  else return 0;
}

float binarySearch(long double le,long double r)
{
    int s = 0;
    long double t;
    //r=(double) r;
    while (1)
    {
        t = (double) le + (r-le)/2;

        s = sigkrousi(t);
        if (s == 1)
        {
          // If x greater, ignore left half
          //cout << "mphka ksana meta to max"<<endl;
            r = t - 1;
          //  cout << " s == 1 " << endl;
          }
        // If x is smaller, ignore right half
        else{
            le = t - 1;
          //  cout << " s == 0" <<endl;
            // brikame thn pio aristeri
          }
          if(abso(max_xa - max_xb) < 1){break;}
        }
    return t;
  }


int main(){
  cin >> n >> l >> k;
  for (ulli i=0;i<n;i++){
    cin >> at[i] >> av[i];
  }
  for (ulli i=0;i<n;i++){
    cin >> bt[i] >> bv[i];
  }
  float t = 0;
  for (ulli i = 0 ; i<k ; i++)
  {
    t = binarySearch(0.0,l);
    av[max_a] = bv[max_b] = 0;
    cout << max_a + 1 << " " << max_b + 1 << endl;
  }

}

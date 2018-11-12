#include <iostream>
using namespace std;
typedef unsigned long long int ulli;
float at[200000],av[200000],bt[200000],bv[200000];
float xa[200000],xb[200000];
ulli n,k;
float l;
ulli max_a,max_b,max_xa,max_xb;


ulli computex(float t){

  for (ulli i = 0 ; i < n ; i++)
  {
    if (at[i] >= t ) xa[i] = 0;
    else  xa[i] = av[i] * (t - at[i]);
    if (bt[i] >= t) xb[i] = 0;
    else  xb[i] = bv[i] * (t - bt[i]);
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
    }
    if (xb[i] > max_xb)
    {
       max_xb = xb[i];
       max_b = i;
     }
  }
  if ( max_xa + max_xb > l ) return 1; else return 0;
}

int binarySearch(ulli l,ulli r)
{
    int s = 0;
    while (l <= r)
    {
        ulli t = l + (r-l)/2;

        // If x greater, ignore left half
        s = sigkrousi(t);
        if (s == 1)
            r = t - 1;
        // If x is smaller, ignore right half
        else
            l = t + 1;
            // brikame thn pio aristeri
          }
    }


int main(){
  cin >> n >> l >> k;
  for (ulli i=0;i<n;i++){
    cin >> at[i] >> av[i];
  }
  for (ulli i=0;i<n;i++){
    cin >> bt[i] >> bv[i];
  }
  for (ulli i = 0 ; i<k ; i++){
    binarySearch(0,l);
    av[max_a] = bv[max_b] = 0;
    cout << max_a + 1 << " " << max_b + 1 << endl;
  }

}

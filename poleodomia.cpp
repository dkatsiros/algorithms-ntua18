
// A Stack based C++ program to find next
// greater element for all array elements
// in same order as input.
#include <bits/stdc++.h>
typedef unsigned long long int ulli;
using namespace std;
ulli b[1000000],l[1000000],r[1000000];
ulli kd[1000000],ka[1000000];
//for (ulli i=0;i<1000000;i++){
//  kd[n]=0;
//  ka[n]=0;
//}

class element{
  public: ulli num,index;
  element() {}
  element(ulli a,ulli b) {
	  num=a;index=b; }
};

/* prints element and NGE pair for all
elements of arr[] of size n */
void printNGE(element arr[], ulli n)
{
    stack <element> s;
    ulli i;
    /* push the first element to stack */
    s.push(arr[0]);


    // iterate for rest of the elements
    for ( i = 1; i < n; i++) {

        if (s.empty()) {
            s.push(arr[i]);
            continue;
        }

        /* if stack is not empty, then
    pop an element from stack.
    If the popped element is smaller
    than next, then
    a) print the pair
    b) keep popping while elements are
    smaller and stack is not empty */
        while (s.empty() == false && s.top().num < arr[i].num) {

            b[s.top().index]=arr[i].index-s.top().index;
            s.pop();
        }

        /* push next to stack so that we can find
    next smaller for it */
        s.push(arr[i]);
    }

    /* After iterating over the loop, the remaining
elements in stack do not have the next smaller
element, so print 0 for them */
    while (s.empty() == false) {
        b[s.top().index] = 0;
        s.pop();
    }

}
void printNGE2(element arr[], ulli n)
{
    stack <element> s;
    ulli i;
    /* push the first element to stack */
    s.push(arr[0]);


    // iterate for rest of the elements
    for ( i = 1; i < n; i++) {

        if (s.empty()) {
            s.push(arr[i]);
            continue;
        }

        /* if stack is not empty, then
    pop an element from stack.
    If the popped element is smaller
    than next, then
    a) print the pair
    b) keep popping while elements are
    smaller and stack is not empty */
        while (s.empty() == false && s.top().num < arr[i].num) {

            b[s.top().index]=s.top().index-arr[i].index;
            s.pop();
        }

        /* push next to stack so that we can find
    next smaller for it */
        s.push(arr[i]);
    }

    /* After iterating over the loop, the remaining
elements in stack do not have the next smaller
element, so print 0 for them */
    while (s.empty() == false) {
        b[s.top().index] = 0;
        s.pop();
    }

}




/* Driver program to test above functions */
int main()
{

    ulli n=0;
    cin >> n ;

    ulli a[n];
    for(ulli i=0;i<n;i++){
    	cin>>a[i];
    }
    element arr[n],arrinv[n];
    for (ulli i=0;i<n;i++){
	    element t(a[i],i);
	    element d(a[n-i-1],n-i-1);
      arr[i]=t;
	    arrinv[i]=d; }

    printNGE(arr, n);
    for(ulli i=0;i<n;i++){
    	r[i]=b[i];}

    printNGE2(arrinv,n);
    for(ulli i=0;i<n;i++){
    	l[i]=b[i];}

    ka[0]=arr[0].num;

    for (ulli i=0;i<n;i++){
      if(l[i]==0) {
        ka[i]=(i+1)*(arr[i].num);
      }
      else{
        ka[i]=l[i]*(arr[i].num)+ka[(i-l[i])];
      }
    }
    kd[n-1]=arr[n-1].num;
    for (ulli i=n-2;i!=-1;i--){
      if (r[i]==0){
        kd[i]=(n-i)*(arr[i].num);
      }
      else{
      kd[i]=r[i]*(arr[i].num)+kd[(i+r[i])];
      }
    }
    for (ulli i=0;i<n;i++){
      kd[i]=kd[i]+ka[i]-arr[i].num;
    }
    ulli min=kd[0];
    for(ulli i=0;i<n;i++){
      if (kd[i]<min) min=kd[i];
    }
    cout <<min<<endl;
    return 0;
}

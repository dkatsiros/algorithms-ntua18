#include <iostream>
using namespace std;
int* d;
int* d_inv;
int n;
// Binary search (note boundaries in the caller)
int CeilIndex(int* v, int l, int r, int key)
{
	while (r - l > 1) {
		int m = l + (r - l) / 2;
		if (v[m] >= key)
			r = m;
		else
			l = m;
	}

	return r;
}

int BotIndex(int* v, int l, int r, int key)
{
	while (r - l > 1) {
		int m = l + (r - l) / 2;
		if (v[m] <= key)
			r = m;
		else
			l = m;
	}

	return r;
}


int LongestIncreasingSubsequenceLength(int* v)
{
	if (n == 0)
		return 0;

	int tail[n];
	int length = 1; // always points empty slot in tail

	tail[0] = v[0];
	for ( int i = 1; i < n; i++) {

		// new smallest value
		if (v[i] < tail[0]){
			tail[0] = v[i];
      d[i] = 1;}

		// v[i] extends largest subsequence
		else if (v[i] > tail[length - 1]) {
			tail[length++] = v[i];
      d[i] = length ;}

		// v[i] will become end candidate of an existing
		// subsequence or Throw away larger elements in all
		// LIS, to make room for upcoming grater elements
		// than v[i] (and also, v[i] would have already
		// appeared in one of LIS, identify the location
		// and replace it)
		else{
      int r = CeilIndex(tail, -1, length - 1, v[i]);
			tail[r] = v[i];
      d[i] = r + 1; }
	}

	return length;
}

int LongestDecreasingSubsequenceLength(int* v)
{
	if (n == 0)
		return 0;

	int tail[n];
	int length = 1; // always points empty slot in tail

	tail[0] = v[0];
	for ( int i = 1; i < n; i++) {

		// new smallest value
		if (v[i] > tail[0]){
			tail[0] = v[i];
      d_inv[i] = 1;}

		// v[i] extends largest subsequence
		else if (v[i] < tail[length - 1]) {
			tail[length++] = v[i];
      d_inv[i] = length ;}

		// v[i] will become end candidate of an existing
		// subsequence or Throw away larger elements in all
		// LIS, to make room for upcoming grater elements
		// than v[i] (and also, v[i] would have already
		// appeared in one of LIS, identify the location
		// and replace it)
		else{
      int r = BotIndex(tail, -1, length - 1, v[i]);
			tail[r] = v[i];
      d_inv[i] = r + 1; }
	}

	return length;
}


int main()
{
  cin >> n;
  int v[n];
  for (int i = 0; i < n; i++){
    cin >> v[i];
  }
  d = (int*) malloc(n * sizeof(int));
  LongestIncreasingSubsequenceLength(v);
// original array
  d[0] = 1;
  // invert array
  int v_inv[n];
  for (int i = 0; i < n ; i++){
    v_inv[i] = v[n-1-i];
  }
  d_inv = (int*) malloc(n * sizeof(int));
  LongestDecreasingSubsequenceLength(v_inv);
  d_inv[0] = 1;
  int d_inv2[n];
  for (int i = 0; i < n ; i++){
    d_inv2[i] = d_inv[n-1-i];
  }
  for (int i = 0; i < n ; i++){
    d_inv[i] = d_inv2[i];
  }

  int lis[n],lis2[n];
  lis[0] = d[0];
  lis2[n-1] = d_inv[n-1];
  for (int i = 1; i < n ; i++){
    lis[i] = max(lis[i-1],d[i]);
  }
  for(int i = n-2; i >= 0; i--){
    lis2[i] = max(lis2[i+1],d_inv[i]);
  }
  int final[n+1];
  final[0] = lis2[1];
  final[n-1] = lis[n-2];
  final[n] = lis[n-1];
  for (int k = 1;k < n-1;k++){
    final[k]=lis[k-1]+lis2[k+1];
  }
  int max = final[0];
  for (int i = 1;i < n + 1;i++){
    if(final[i] > max) max = final[i];
  }
  cout << max << endl;
// free everything, and return
  free(d);
  free(d_inv);
  return 0;
}

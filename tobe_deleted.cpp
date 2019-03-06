int v[9];
v = [2, 5, 3, 7, 11, 8, 10, 13, 6 ] ;
2 5 3 7 11 8 10 13 6

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
      int r = CeilIndex(tail, -1, length - 1, v[i]);
			tail[r] = v[i];
      d_inv[i] = r + 1; }
	}

	return length;
}

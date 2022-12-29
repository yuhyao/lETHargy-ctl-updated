/**
 * Author: Yuhao Yao
 * Date: 22-10-24
 * Description: Fast Subtset Transform, which is also known as fast zeta transform. Length of $a$ should be a power of $2$.
 * Time: O(N \log N), where $N$ is the length of $a$.
 * Status: tested on https://codeforces.com/contest/914/problem/G.
 */
template<class T>
void fst(vector<T> &a, int is_inv) {
	int n = sz(a);
	for (int s = 1; s < n; s <<= 1) {
		rep(i, 0, n - 1) if (i & s) {
			if (is_inv == 0) a[i] += a[i ^ s];
			else a[i] -= a[i ^ s];
		}
	}
}

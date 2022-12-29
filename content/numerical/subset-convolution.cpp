/**
 * Author: Yuhao Yao
 * Date: 22-10-24
 * Description: Subset Convolution of array $a$ and $b$. Resulting array $c$ satisfies $c_z = \sum_{x, y:\, x | y = z, x \& y = 0} a_x \cdot b_y$. Length of $a$ and $b$ should be same and be a power of $2$.
 * Time: O(N \log^2 N), where $N$ is the length of $a$.
 * Status: tested on https://codeforces.com/contest/914/problem/G.
 */
 #include "fast-subset-transform.cpp"
 
template<class T>
vector<T> SubsetConv(const vector<T> &as, const vector<T> &bs) {
	int n = sz(as);
	assert(n > 0 && sz(bs) == n);
	int k = __lg(n);
	vector<vector<T>> ps(k + 1, vector<T>(n)), qs(ps), rs(ps);
	rep(x, 0, n - 1) {
		ps[__builtin_popcount(x)][x] = as[x];
		qs[__builtin_popcount(x)][x] = bs[x];
	}
	for (auto &vec: ps) fst(vec, 0);
	for (auto &vec: qs) fst(vec, 0);
	rep(i, 0, k) rep(j, 0, k - i) {
		rep(x, 0, n - 1) rs[i + j][x] += ps[i][x] * qs[j][x];
	}
	for (auto &vec: rs) fst(vec, 1);
	vector<T> cs(n);
	rep(x, 0, n - 1) {
		cs[x] = rs[__builtin_popcount(x)][x];
	}
	return cs;
}

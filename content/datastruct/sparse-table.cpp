/**
 * Author: Yuhao Yao
 * Date: 22-10-20
 * Description: Sparse Table of an array of length $N$.
 * Time: O(N \log N) for construction, O(1) per query.
 * Status: tested on https://qoj.ac/contest/695/problem/1857, https://codeforces.com/gym/103371/problem/M.
 */

template<class T, class F = function<T(const T&, const T&)>>
class SparseTable {
	int n;
	vector<vector<T>> st;
	const F func;
public:
	SparseTable(const vector<T> &init, const F &f): n(sz(init)), func(f) {
		assert(n > 0);
		st.assign(__lg(n) + 1, vector<T>(n));
		st[0] = init;
		rep(i, 1, __lg(n)) rep(x, 0, n - (1 << i)) st[i][x] = func(st[i - 1][x], st[i - 1][x + (1 << (i - 1))]);
	}

	T ask(int l, int r) {
		assert(0 <= l && l <= r && r < n);
		int k = __lg(r - l + 1);
		return func(st[k][l], st[k][r - (1 << k) + 1]);
	}
};
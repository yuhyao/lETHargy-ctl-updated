/**
 * Author: Yuhao Yao
 * Date: 22-10-24
 * Description: Hash of a string.
 * Usage: StringHash<unsigned long long> ha(s); // $s$ can be string or vector<int>.
 * Time: O(|s|).
 * Status: tested on https://qoj.ac/contest/144/problem/3009.
 */
template<class hashv> 
struct StringHash {
	const hashv base = 131; // change this if you hash a vector<int>.
	int n;
	vector<hashv> hs, pw;

	template<class T>
	StringHash(const T &s): n(sz(s)), hs(n + 1), pw(n + 1) {
		pw[0] = 1;
		rep(i, 1, n) pw[i] = pw[i - 1] * base;
		rep(i, 0, n - 1) hs[i + 1] = hs[i] * base + s[i];
	}

	hashv get(int l, int r) { return hs[r + 1] - hs[l] * pw[r + 1 - l]; }
};

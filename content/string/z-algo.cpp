/**
 * Author: Yuhao Yao
 * Date: 22-10-24
 * Description: Given string $s = s_0...s_{n - 1}$, compute array $z$ where $z[i]$ is the lcp of $s_0...s_{n - 1}$ and $s_{i}...s_{n - 1}$.
 *  Use function $cal(t)$ (where $|t| = m$) to calculate the lcp of of $s_0...s_{n - 1}$ and $t_{i}...t_{m - 1}$ for each $i$.
 * Usage: zAlgo za(s); // $s$ can be string or vector.
 * Time: O(|s|) for precalculation and O(|t|) for matching.
 * Status: tested on https://www.codechef.com/submit/SSTRPREF2.
 */

template<class T>
struct zAlgo {
	const T s; /// start-hash
	int n;
	vi z;

	zAlgo(const T &s): s(s), n(sz(s)), z(n) {
		z[0] = n;
		int l = 0, r = 0;
		rep(i, 1, n - 1) {
			z[i] = max(0, min(z[i - l], r - i));
			while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
			if (i + z[i] > r) {
				l = i;
				r = i + z[i];
			}
		}
	} /// end-hash

	vi cal(const T &t) { /// start-hash
		int m = sz(t);
		vi res(m);
		int l = 0, r = 0;
		rep(i, 0, m - 1) {
			res[i] = max(0, min(i - l < n ? z[i - l] : 0, r - i));
			while (i + res[i] < m && s[res[i]] == t[i + res[i]]) res[i]++;
			if (i + res[i] > r) {
				l = i;
				r = i + res[i];
			}
		}
		return res;
	} /// end-hash
};

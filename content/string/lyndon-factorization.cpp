/**
 * Author: Yuhao Yao
 * Date: 22-10-24
 * Description: Lyndon factorization of string $s$. Return a vector of pairs $(l, r)$, representing substring $s_l...s_r$.
 * Time: O(|s|).
 * Status: tested on https://www.luogu.com.cn/problem/P6114.
 */
vector<pii> duval(string const& s) {
	int n = sz(s), i = 0;
	vector<pii> res;
	while (i < n) {
		int j = i + 1, k = i;
		while (j < n && s[k] <= s[j]) {
			if (s[k] < s[j]) k = i;
			else k++;
			j++;
		}
		while (i <= k) {
			res.emplace_back(i, i + j - k - 1);
			i += j - k;
		}
	}
	return res;
}

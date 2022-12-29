/**
 * Author: Antti Roeyskoe
 * Date: 22-06-15
 * License: MIT
 * Source: Code by self, algorithm from https://codeforces.com/blog/entry/61203#s2-2
 * Description: Hilbert curve sorting order for Mo's algorithm. Sorts queries $(L_i, R_i)$ where $0 \leq L_i \leq R_i < n$ into order $\pi$, such that $\sum_i \left|L_{\pi_{i + 1}} - L_{\pi_{i}}\right| + \left|R_{\pi_{i + 1}} - R_{\pi_{i}}\right| = \mathcal{O}(n \sqrt q)$
 * Time: O(N \log N).
 * Usage: hilbertOrder(n, qs) returns $\pi$
 * Status: untested
 */

ll hilbertOrd(int y, int x, int h) {
	if (h == -1) return 0;
	int s = (1 << h), r = (1 << h) - 1;
	int y0 = y >> h, x0 = x >> h;
	int y1 = y & r, x1 = x & r;
	int ny = (y0 ? y1 : (x0 ? r - x1 : x1)); // x1 : r - x1));
	int nx = (y0 ? x1 : (x0 ? r - y1 : y1)); // y1 : r - y1)); // r - y1 : y1));
	return s*s * (2*x0 + (x0 ^ y0)) + hilbertOrd(ny, nx, h-1);
}
vector<int> hilbertOrder(int n, const vector<pair<int, int>>& qs) {
	int h = 0, q = qs.size();
	while((1 << h) < n) ++h;

	vector<pair<ll, int>> tmp(q);
	for (int i = 0; i < q; ++i) tmp[i] = {hilbertOrd(qs[i].first, qs[i].second, h - 1), i};
	sort(tmp.begin(), tmp.end());

	vector<int> res(q);
	for (int qi = 0; qi < q; ++qi) res[qi] = tmp[qi].second;
	return res;
}

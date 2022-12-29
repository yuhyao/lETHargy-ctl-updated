/**
 * Author: Yuhao Yao
 * Date: 22-11-01
 * Description: Compute the Minkovski Sum of two \textbf{Convex Hulls} $P$ and $Q$. The result is also a \textbf{Convex Hull}.
 *  Convex Hulls $P$ and $Q$ should \textbf{not} have duplicate (same) points while consecutive collinear points are allowed.
 *  The returned Convex Hull \textbf{may} have collinear points (on the borders), but \textbf{no} duplicate points.
 *  \textbf{Needed function(s): argcmp}.
 * Time: O(|P| + |Q|).
 * Status: (long long) tested on https://ac.nowcoder.com/acm/contest/33188/G.
 */
template<class P>
vector<P> MinkovskiSum(vector<P> as, vector<P> bs) {
	auto pre = [](vector<P> &as) {
		auto it = min_element(all(as), [&](P a, P b) {
			return P::cmp(a.y, b.y) != 0 ? a.y > b.y : P::cmp(a.x, b.x) < 0;
		});
		rotate(as.begin(), it, as.end());
		int n = sz(as);
		vector<P> res(n);
		rep(i, 0, n - 1) res[i] = as[(i + 1) % n] - as[i];
		return res;
	};
	vector<P> us = pre(as), vs = pre(bs), res(sz(as) + sz(bs));
	merge(all(us), all(vs), res.begin(), [](P a, P b) { return P::argcmp(a, b) < 0; });
	P last = as[0] + bs[0];
	for (auto &p: res) {
		p = p + last; // accumulates error here when dealing with imprecise points.
		last = p;
	}
	return res;
}

/**
 * Author: Yuhao Yao
 * Date: 22-10-29
 * Description: Given $n$ points $p_0, ..., p_{n - 1}$ on the plane, find the closest pair in euclidean distance. Returns the minimum squared distance.
 * Time: $O(n\log^2 n)$.
 * Status: tested on https://www.luogu.com.cn/problem/P7883.
 */
template<class P, class T = typename P::type>
T ClosestPair(vector<P> as) {
	sort(all(as), [](P a, P b) { return a.x < b.x; });
	assert(sz(as) > 1);
	T ans = (as[0] - as[1]).len2();
	auto dfs = [&](auto &dfs, int l, int r) -> void {
		if (l == r) return;
		int mid = (l + r) >> 1;
		dfs(dfs, l, mid);
		dfs(dfs, mid + 1, r);
		vector<P> bs;
		rep(i, l, r) {
			T dx = (as[i] - as[mid]).x;
			if (dx * dx <= ans) bs.push_back(as[i]);
		}
		sort(all(bs), [](P a, P b) { return a.y < b.y; });
		rep(i, 0, sz(bs) - 1) {
			rep(j, i + 1, min(sz(bs) - 1, i + 6)) {
				chmin(ans, (bs[i] - bs[j]).len2());
			}
		}
	};
	dfs(dfs, 0, sz(as) - 1);
	return ans;
}

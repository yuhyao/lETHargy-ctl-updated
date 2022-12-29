/**
 * Author: Yuhao Yao
 * Date: 22-11-01
 * Description: MinimumEnclosingCircle of points $as$.
 * Status: (long double) tested on https://www.luogu.com.cn/problem/P1742.
 */
 #include "circumcircle.cpp"
template<class P, class T = typename P::type>
pair<P, T> Welzl(vector<P> as) {
	mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
	shuffle(all(as), rng);
	auto dfs = [&](auto &dfs, int n, vector<P> R) -> pair<P, T> {
		auto [o, r] = sz(R) > 0 ? circumcircle(R) : pair<P, T>{as[0], 0};
		rep(i, 0, n - 1) {
			if (P::cmp((as[i] - o).len(), r) > 0) {
				auto nR = R;
				nR.push_back(as[i]);
				tie(o, r) = dfs(dfs, i, nR);
			}
		}
		return {o, r};
	};
	return dfs(dfs, sz(as), vector<P>{});
}

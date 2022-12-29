/**
 * Author: Yuhao Yao
 * Date: 22-09-13
 * Description: Compute the Edge-BiConnected Components of a \textbf{connected} graph. Multiple edges and self loops are allowed. Return the size of BCCs and the index of the component each vertex belongs to.
 * Time: O(|E|).
 * Status: tested on https://codeforces.com/contest/732/problem/F, https://codeforces.com/contest/231/problem/E.
 */

auto EdgeBCC(int n, const vector<pii> &es, int st = 0) {
	vi dfn(n, -1), low(n), id(n), mark(sz(es), 0), sta;
	int cnt = 0, bcc = 0;
	vector<vi> g(n);
	rep(ind, 0, sz(es) - 1) {
		auto [x, y] = es[ind];
		g[x].push_back(ind);
		g[y].push_back(ind);
	}

	auto dfs = [&](auto dfs, int now) -> void {
		low[now] = dfn[now] = cnt++;
		sta.push_back(now);
		for (auto ind: g[now]) if (mark[ind] == 0) {
			mark[ind] = 1;
			auto [x, y] = es[ind];
			int v = now ^ x ^ y;
			if (dfn[v] == -1) {
				dfs(dfs, v);
				low[now] = min(low[now], low[v]);
			} else low[now] = min(low[now], dfn[v]);
		}
		if (low[now] == dfn[now]) {
			while (sta.back() != now) {
				id[sta.back()] = bcc;
				sta.pop_back();
			}
			id[now] = bcc;
			sta.pop_back();
			bcc++;
		}
	};
	dfs(dfs, st);
	return make_tuple(bcc, id);
}
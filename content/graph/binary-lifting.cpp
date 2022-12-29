/**
 * Author: Yuhao Yao
 * Date: 22-10-23
 * Description: Compute the sparse table for binary lifting of a rooted tree $T$. The root is set as $0$ by default.
 *  $g$ should be the adjacent list of the tree $T$.
 * Time: O(|V|\log |V|) for precalculation and O(\log |V|) for each $lca$ query.
 * Status: tested on https://codeforces.com/contest/231/problem/E. https://codeforces.com/contest/1707/problem/C.
 */
struct BinaryLifting {
	int n;
	vi dep;
	vector<vi> anc;

	BinaryLifting(const vector<vi> &g, int rt = 0): n(sz(g)), dep(n, -1) {
		assert(n > 0);
		anc.assign(n, vi(__lg(n) + 1));
		auto dfs = [&](auto &dfs, int now, int fa) -> void {
			assert(dep[now] == -1); // make sure it is indeed a tree.
			dep[now] = fa == -1 ? 0 : dep[fa] + 1;
			anc[now][0] = fa;
			rep(i, 1, __lg(n)) {
				anc[now][i] = anc[now][i - 1] == -1 ? -1 : anc[anc[now][i - 1]][i - 1];
			}
			for (auto v: g[now]) if (v != fa) dfs(dfs, v, now);
		};
		dfs(dfs, rt, -1);
	}
	int swim(int x, int h) {
		for (int i = 0; h && x != -1; h >>= 1, i++) {
			if (h & 1) x = anc[x][i];
		}
		return x;
	}
	int lca(int x, int y) {
		if (dep[x] < dep[y]) swap(x, y);
		x = swim(x, dep[x] - dep[y]);
		if (x == y) return x;
		for (int i = __lg(n); i >= 0; --i) {
			if (anc[x][i] != anc[y][i]) {
				x = anc[x][i];
				y = anc[y][i];
			}
		}
		return anc[x][0];
	}
};

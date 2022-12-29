/**
 * Author: Yuhao Yao
 * Date: 22-10-24
 * Description: 2SAT solver, returns if a 2SAT system of $V$ variables and $C$ constraints is satisfiable. If yes, it also gives an assignment.
 *  Call $addClause$ to add clauses. For example, if you want to add clause $\neg x \lor y$, just call $addClause(x, 0, y, 1)$.
 * Time: O(|V| + |C|).
 * Status: tested on https://codeforces.com/gym/103260/problem/E.
 */

struct TwoSat {
	int n;
	vector<vi> e;
	vi ans;

	TwoSat(int n): n(n), e(n * 2), ans(n) {}

	void addClause(int x, bool f, int y, bool g) {
		e[x * 2 + !f].push_back(y * 2 + g);
		e[y * 2 + !g].push_back(x * 2 + f);
	}

	bool satisfiable() {
		vi id(n * 2, -1), dfn(n * 2, -1), low(n * 2, -1), sta;
		int cnt = 0, scc = 0;

		auto dfs = [&](auto &dfs, int now) -> void {
			dfn[now] = low[now] = cnt++;
			sta.push_back(now);
			for (auto v: e[now]) {
				if (dfn[v] == -1) {
					dfs(dfs, v);
					low[now] = min(low[now], low[v]);
				} else if (id[v] == -1) low[now] = min(low[now], dfn[v]);
			}
			if (low[now] == dfn[now]) {
				while (sta.back() != now) {
					id[sta.back()] = scc;
					sta.pop_back();
				}
				id[sta.back()] = scc;
				sta.pop_back();
				scc++;
			}
		};

		rep(i, 0, n * 2 - 1) if (dfn[i] == -1) dfs(dfs, i);
		rep(i, 0, n - 1) {
			if (id[i * 2] == id[i * 2 + 1]) return 0;
			ans[i] = id[i * 2] > id[i * 2 + 1];
		}
		return 1;
	}

	vi getAss() { return ans; }
};

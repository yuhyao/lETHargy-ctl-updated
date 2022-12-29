/**
 * Author: Yuhao Yao
 * Date: 22-10-23
 * Description: Persistent Segment Tree of range $[0, N - 1]$. Point apply and thus no lazy propogation.
 *  Always define a global $apply$ function to tell segment tree how you apply modification. 
 *  Combine is set as + operation. If you use your own struct, then please define constructor and + operation.
 *  In constructor, $q$ is the number of $pointApply$ you will use.
 * Usage: Point Add and Range Sum.
 *  void apply(int \&a, int b) { a += b; } // global
 *  ...
 *  PersistSegtree<int> pseg(10, 1); // len = 10 and 1 update.
 *  int rt = 0; // empty node.
 *  int new_rt = pseg.pointApply(rt, 9, 1); // add 1 to last position (position 9).
 *  int sum = pseg.rangeAsk(new_rt, 7, 9); // ask the sum between position 7 and 9, wrt version new_rt.
 * Time: O(\log N) per operation.
 * Status: tested on https://codeforces.com/contest/1479/problem/D, https://www.luogu.com.cn/problem/P7361, https://www.luogu.com.cn/problem/P4094.
 */
template<class Info>
struct PersistSegtree {
	struct node { Info info; int ls, rs; }; /// start-hash
	int n;
	vector<node> t;
	// node 0 is left as virtual empty node.
	PersistSegtree(int n, int q): n(n), t(1) {
		assert(n > 0);
		t.reserve(q * (__lg(n) + 2) + 1);
	}

	// pointApply returns the id of new root.
	template<class... T>
	int pointApply(int rt, int pos, const T&... val) {
		auto dfs = [&](auto &dfs, int &i, int l, int r) {
			t.push_back(t[i]);
			i = sz(t) - 1;

			if (l == r) {
				::apply(t[i].info, val...);
				return;
			}
			int mid = (l + r) >> 1;
			if (pos <= mid) dfs(dfs, t[i].ls, l, mid);
			else dfs(dfs, t[i].rs, mid + 1, r);
			t[i].info = t[t[i].ls].info + t[t[i].rs].info;
		};
		dfs(dfs, rt, 0, n - 1);
		return rt;
	}

	Info rangeAsk(int rt, int ql, int qr) {
		Info res{};
		auto dfs = [&](auto &dfs, int i, int l, int r) {
			if (i == 0 || qr < l || r < ql) return;
			if (ql <= l && r <= qr) {
				res = res + t[i].info;
				return;
			}
			int mid = (l + r) >> 1;
			dfs(dfs, t[i].ls, l, mid);
			dfs(dfs, t[i].rs, mid + 1, r);
		};
		dfs(dfs, rt, 0, n - 1);
		return res;
	} /// end-hash

	// lower_bound on prefix sums of difference between two versions.
	int lower_bound(int rt_l, int rt_r, Info val) { /// start-hash
		Info sum{};
		auto dfs = [&](auto &dfs, int x ,int y, int l, int r) {
			if (l == r) return sum + t[y].info - t[x].info >= val ? l : l + 1;
			int mid = (l + r) >> 1;
			Info s = t[t[y].ls].info - t[t[x].ls].info;
			if (sum + s >= val) return dfs(dfs, t[x].ls, t[y].ls, l, mid);
			else {
				sum = sum + s;
				return dfs(dfs, t[x].rx, t[y].rs, mid + 1, r);
			}
		};
		return dfs(dfs, rt_l, rt_r, 0, n - 1);
	} /// end-hash
};

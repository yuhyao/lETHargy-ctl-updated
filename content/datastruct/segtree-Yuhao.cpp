/**
 * Author: Yuhao Yao
 * Date: 22-09-13
 * Description: Segment tree. Point apply and thus no lazy propogation.
 * Usage: Always define a global apply function for class $Info$ you use to tell segment tree how you apply modification.
 *  Combine is set as plus so if you just let T be numerical type then you have range sum in the info and as range query result. To have something different, say rangeMin, define a struct with constructer and + operation.
 * Time: O(\log N) per operation.
 * Status: tested on https://qoj.ac/contest/695/problem/1856.
 */

template<class Info> struct Segtree {
	#define ls i * 2
	#define rs i * 2 + 1

	int n; 
	vector<Info> info;

	Segtree(const vector<Info> &init): n(sz(init)) {
		assert(n > 0);
		info.resize(4 << __lg(n));
		auto build = [&](auto dfs, int i, int l, int r) {
			if (l == r) {
				info[i] = init[l];
				return;
			}
			int mid = (l + r) >> 1;
			dfs(dfs, ls, l, mid);
			dfs(dfs, rs, mid + 1, r);
			pull(i);
		};
		build(build, 1, 0, n - 1);
	}
	void pull(int i) { info[i] = info[ls] + info[rs]; }
	
	template<class... T>
	void pointApply(int p, const T&... val) {
		auto dfs = [&](auto dfs, int i, int l, int r) {
			if (p < l || r < p) return;
			if (l == r) {
				::apply(info[i], val...);
				return;
			}
			int mid = (l + r) >> 1;
			dfs(dfs, ls, l, mid);
			dfs(dfs, rs, mid + 1, r);
			pull(i);
		};
		dfs(dfs, 1, 0, n - 1);
	}
	Info rangeAsk(int ql, int qr) {
		Info res{};
		auto dfs = [&](auto dfs, int i, int l, int r) {
			if (qr < l || r < ql) return;
			if (ql <= l && r <= qr) {
				res = res + info[i];
				return;
			}
			int mid = (l + r) >> 1;
			dfs(dfs, ls, l, mid);
			dfs(dfs, rs, mid + 1, r);
		};
		dfs(dfs, 1, 0, n - 1);
		return res;
	}
	#undef ls
	#undef rs
};
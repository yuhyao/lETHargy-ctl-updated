/**
 * Author: Yuhao Yao
 * Date: 22-10-23
 * Description: Cartesian Tree of array $as$ (of distinct values) of length $N$. Node with smaller depth has smaller value. Set $gr = 1$ to have top with the greatest value. Returns the root of Cartesian Tree, left sons of nodes and right sons of nodes. ($-1$ means no left son / right son.)
 * Time: O(N) for construction.
 * Status: Tested on https://qoj.ac/contest/695/problem/1857, https://codeforces.com/gym/103371/problem/M, https://codeforces.com/contest/1718/problem/D.
 */

template<class T>
auto CartesianTree(const vector<T> &as, int gr = 0) {
	int n = sz(as);
	vi ls(n, -1), rs(n, -1), sta;
	rep(i, 0, n - 1) {
		while (sz(sta) && ((as[i] < as[sta.back()]) ^ gr)) {
			ls[i] = sta.back();
			sta.pop_back();
		}
		if (sz(sta)) rs[sta.back()] = i;
		sta.push_back(i);
	}
	return make_tuple(sta[0], ls, rs);
}

/**
 * Author: Yuhao Yao
 * Date: 22-09-19
 * Description: Circumcircle of at most three points.
 * Status: (long double) tested on https://www.luogu.com.cn/problem/P1742.
 */
template<class P, class T = typename P::type>
pair<P, T> circumcircle(const vector<P> &as) {
	assert(sz(as) > 0);
	if (sz(as) == 1) return {as[0], 0};
	else if (sz(as) == 2) return {(as[0] + as[1]) / 2, (as[1] - as[0]).len() / 2};
	else {
		P u = as[1] - as[0], v = as[2] - as[0];
		T r = u.len() * v.len() * (u - v).len() / abs(u.cross(v) * 2);
		T B = u.len2(), C = v.len2();
		P w = P{v.y * B - u.y * C, u.x * C - v.x * B} / (u.cross(v) * 2);
		return {as[0] + w, r};
	}
}

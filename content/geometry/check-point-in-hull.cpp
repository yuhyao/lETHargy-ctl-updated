/**
 * Author: Yuhao Yao
 * Date: 22-11-01
 * Description: Given a c.c.w convex hull $p_0...p_{n - 1}$, check if Point $q$ is in the hull.
 *  $p_0, \cdots, p_{n - 1}$ should be distinct points. (It should be fine that $3$ of them are collinear.)
 *  Returns $0$ if Point $q$ is outside the hull; $1$ if it is inside the hull; $2$ if it is on the border of the hull.
 *  \textbf{Needed function(s): dis\_to\_line}.
 * Time: $O(\log n)$.
 * Status: tested on https://codeforces.com/gym/101201/problem/E, https://www.luogu.com.cn/problem/P4557.
 */
template<class P>
int PointInHull(const vector<P> &poly, P q) {
	int n = sz(poly);
	if (q.dis_to_line(poly[0], poly[1]) > P::eps) return 0;
	if (q.dis_to_line(poly[0], poly[n - 1]) < -P::eps) return 0;
	int l = 1, r = n;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (q.dis_to_line(poly[0], poly[mid]) > P::eps) r = mid;
		else l = mid + 1;
	}
	int id = r - 1;
	if (id == n - 1) {
		return (poly[n - 1] - poly[0]).len2() >= (q - poly[0]).len2() ? 2 : 0;
	} else if (id == 1 && q.dis_to_line(poly[0], poly[1]) >= -P::eps) {
		return (poly[1] - poly[0]).len2() >= (q - poly[0]).len2() ? 2 : 0;
	} else {
		int s = P::sgn(q.dis_to_line(poly[id], poly[id + 1]));
		if (s > 0) return 0;
		else if (s == 0) return 2;
		else return 1;
	}
}

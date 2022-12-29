/**
 * Author: Yuhao Yao
 * Date: 22-11-01
 * Description: Compute the intersection points of a Circle and a Segment $ab$. $ab$ can be degenerate.
 *  Only works for double or long double.
 *  \textbf{Needed function(s): dis\_to\_line, project\_len, project\_to\_line, dis\_to\_seg, on\_seg}.
 * Status: (double) tested on https://acm.hdu.edu.cn/showproblem.php?pid=6419.
 */
template<class T, class P = Point<T>>
vector<P> capCircleSeg(P o, T r, P a, P b) {
	if (a == b) {
		vector<P> res;
		if ((a - o).len2() == r * r) res.push_back(a);
		return res;
	}
	T d = o.dis_to_line(a, b);
	if (abs(d) > r + P::eps) return {};
	P p = o.project_to_line(a, b), v = (b - a).unit();
	T len = sqrt(max(T{0}, r * r - d * d));
	vector<P> res;
	if ((p + v * len).on_seg(a, b)) res.push_back(p + v * len);
	if ((p - v * len).on_seg(a, b)) res.push_back(p - v * len);
	return res;
}

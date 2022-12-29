/**
 * Author: Yuhao Yao
 * Date: 22-11-01
 * Description: Check if \textbf{Ray} $ab$ intersects Segment $cd$. $ab$ should \textbf{not} degenerate but $cd$ can degenerate.
 *  Returns 0 if they do not intersect;
 *  Returns 1 if they intersect properly;
 *  Returns 2 if they intersect o.w. (i.e. intersection is some endpoint).
 *  Can be used for long long, double and long double.
 *  Please make sure $a \ne b$.
 *  \textbf{Needed function(s): dis\_to\_line, on\_line, project\_len, dis\_to\_seg, on\_seg}.
 * Status: (long long) tested on https://ac.nowcoder.com/acm/contest/33188/G, https://codeforces.com/gym/256788/problem/C.
 */
template<class P>
int checkcapRaySeg(P a, P b, P c, P d) {
	assert(!(a == b));
	auto r1 = P::sgn(c.dis_to_line(a, b));
	auto r2 = P::sgn(d.dis_to_line(a, b));
	auto r3 = c == d ? 0 : P::sgn(a.dis_to_line(c, d));
	auto r4 = c == d ? 0 : P::sgn(b.dis_to_line(c, d) - a.dis_to_line(c, d));
	if (r1 * r2 < 0 && r3 * r4 < 0) return 1;
	if (c.on_line(a, b) && c.project_len(a, b) >= -P::eps) return 2;
	if (d.on_line(a, b) && d.project_len(a, b) >= -P::eps) return 2;
	if (a.on_seg(c, d)) return 2;
	return 0;
}

/**
 * Author: Yuhao Yao
 * Date: 22-11-01
 * Description: check if Segment $ab$ intersects Segment $cd$. Safe when segments degenerate.
 *  Returns 0 if they do not intersect;
 *  Returns 1 if they intersect properly;
 *  Returns 2 if they intersect o.w. (i.e. intersection is some endpoint).
 *  Can be used for long long, double and long double.
 *  \textbf{Needed function(s): dis\_to\_line, project\_len, dis\_to\_seg, on\_seg}.
 * Status: (long long) tested on https://official.contest.yandex.com/contest/39025/problems/D/.
 *  (double) tested on https://acm.hdu.edu.cn/showproblem.php?pid=6419.
 */
template<class P>
int checkcapSegSeg(P a, P b, P c, P d) {
	auto s1 = a == b ? 0 : P::sgn(c.dis_to_line(a, b));
	auto s2 = a == b ? 0 : P::sgn(d.dis_to_line(a, b));
	auto s3 = c == d ? 0 : P::sgn(a.dis_to_line(c, d));
	auto s4 = c == d ? 0 : P::sgn(b.dis_to_line(c, d));
	if (s1 * s2 < 0 && s3 * s4 < 0) return 1;
	if (c.on_seg(a, b)) return 2;
	if (d.on_seg(a, b)) return 2;
	if (a.on_seg(c, d)) return 2;
	if (b.on_seg(c, d)) return 2;
	return 0;
}

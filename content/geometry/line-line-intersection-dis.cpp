/**
 * Author: Yuhao Yao
 * Date: 22-08-23
 * Description: Compute the distance from Point $a$ to the intersection point of Line $ab$ and Line $cd$.
 */
template<class P>
auto discapLineLine(P a, P b, P c, P d) {
	return (c - a).cross(d - a) / (b - a).cross(d - c) * (b - a).len();
}

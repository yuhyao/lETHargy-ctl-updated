# Author: Yuhao Yao
# Date: 22-10-24
def exgcd(a, b):
	if b == 0:
		return 1, 0
	x, y = exgcd(b, a % b)
	return y, x - a // b * y

# Returned A is the minimum non-negative integer satisfying given two equations.
def merge(a1, m1, a2, m2):
	if m1 == -1 or m2 == -1:
		return -1, -1
	y1, y2 = exgcd(m1, m2)
	g = m1 * y1 + m2 * y2
	if (a2 - a1) % g != 0:
		return -1, -1
	y1 = y1 * ((a2 - a1) // g) % (m2 // g)
	if y1 < 0: 
		y1 += m2 // g
	M = m1 // g * m2
	A = m1 * y1 + a1
	return A, M

# Given a list of pairs (a_i, m_i) representing equations x = a_i (mod m_i)
# Return a, m such that a + m * k are solutions. -1, -1 means that there is no solution.
def general_chinese(ps): 
	a, m = 0, 1
	for a2, m2 in ps:
		a, m = merge(a, m, a2, m2)
	return a, m

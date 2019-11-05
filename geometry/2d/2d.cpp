#include "../../contest/header.hpp"

// 2D geometry operations. This file should not have algorithms.
// Author: some of it by Arthur Pratti Dadalto.
// Source: some of it from https://github.com/
// kth-competitive-programming/kactl/blob/master/content/geometry/.
// Usage: avoid int unless necessary.

// When increasing EPS, keep in mind that 
// sqrt(1e9^2 + 1) = 1e9 + 5e-10.
const double EPS = 1e-12;

// Point struct implementation. Some methods are useful only when
// using this to represent vectors.
template <class T>
struct point
{
	typedef point<T> P;
	T x, y;

	explicit point(T x = 0, T y = 0) : x(x), y(y) {}
	
	bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
	
	bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
	
	P operator+(P p) const { return P(x + p.x, y + p.y); }
	
	P operator-(P p) const { return P(x - p.x, y - p.y); }
	
	P operator*(T d) const { return P(x * d, y * d); }
	
	P operator/(T d) const { return P(x / d, y / d); }
	
	T dot(P p) const { return x * p.x + y * p.y; }
	
	T cross(P p) const { return x * p.y - y * p.x; }
	
	// product sign: right hand rule from a to b.
	T cross(P a, P b) const { return (a - *this).cross(b - *this); } 
	
	// Distance squared to origin.
	T dist2() const { return x * x + y * y; }

	// Vector norm (distance to origin).
	double dist() const { return sqrt((double)dist2()); }
	
	// angle to x-axis in interval [-pi, pi]			 
	double angle() const { return atan2(y, x); }					 

	// makes dist()=1 (unit vector).
	point<double> unit() const { return *this / dist(); }			 
	
	// rotates +90 degrees around origin.
	P perp() const { return P(-y, x); }

	// perpendicular unit vector.
	point<double> normal() const { return perp().unit(); }			 

	// returns point rotated 'a' radians ccw around the origin.
	point<double> rotate(double a) const							 
	{
		return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
	}

	// Returns projection of vector p on this vector.
	point<double> proj(P p) const 
	{
		double d = (double)dot(p);
		return point<double>((double)x * d, (double)y * d) / (double)dist2();
	}

	// Angle between the vectors in interval [-pi, pi]. Positive if p
	// is ccw from this.
	double angle(P p) const { return p.rotate(-angle()).angle(); } 
};

// Solves the linear system {a * x + b * y = e
//                          {c * x + d * y = f
// Returns {1, {x, y}} if solution is unique, {0, {0,0}} if no
// solution and {-1, {0,0}} if infinite solutions.
// If using integer function type, this will give wrong answer if
// answer is not integer.
// TODO: test me with integer and non-integer.
template <class T>
pair<int, point<T>> linear_solve2(T a, T b, T c, T d, T e, T f)
{
	point<T> retv;
	T det = a * d - b * c;

	if (det == 0) // Maybe do EPS compare if using floating point.
	{
		if (b * f == d * e && a * f == c * e)
			return {-1, point<T>()};
		return {0, point<T>()};
	}

	// In case solution needs to be integer, use something like the
	// line below.
	// assert((e * d - f * b) % det == 0 &&
    //        (a * f - c * e) % det == 0);

	return {1, point<T>((e * d - f * b) / det, (a * f - c * e) / det)};
}

// Represents line segments defined by two points.
template <class T>
struct segment
{
	typedef point<T> P;
	P pi, pf; // Initial and final points.

	explicit segment(P a = P(), P b = P()) : pi(a), pf(b) {}

	// Distance from this segment to a given point.
	// ***IMPORTANT*** DOES NOT WORK FOR LONG LONG IF X > 1000.
	double dist(P p)
	{
		if (pi == pf)
			return (p - pi).dist();
		auto d = (pf - pi).dist2();
		auto t = min(d, max((T)0, (p - pi).dot(pf - pi)));
		return ((p - pi) * d - (pf - pi) * t).dist() / (double)d;
	}

	// Checks if given point belongs to segment. Use dist(p) <= EPS
	// instead when using point<double>.
	bool on_segment(P p)
	{
		return p.cross(pi, pf) == 0 && (pi - p).dot(pf - p) <= 0;
	}

	// If a unique intersection point between the line segments exists
	// then it is returned.
	// If no intersection point exists an empty vector is returned.
	// If infinitely many exist a vector with 2 elements is returned,
	// containing the endpoints of the common line segment.
	// The wrong position will be returned if P is point<ll> and the 
	// intersection point does not have integer coordinates.
	// However, no problem in using it to check if intersects or not
	// in this case (size of vector will be correct).
	// *** IMPORTANT *** Products of **three** coordinates are used in 
	// intermediate steps so watch out for overflow if using int or
	// long long.
	vector<P> intersect(segment rhs)
	{
		auto oa = rhs.pi.cross(rhs.pf, pi), ob = rhs.pi.cross(rhs.pf, pf),
			 oc = pi.cross(pf, rhs.pi), od = pi.cross(pf, rhs.pf);

		// Checks if intersection is single non-endpoint point.
		if (sign(oa) * sign(ob) < 0 && sign(oc) * sign(od) < 0)
			return {(pi * ob - pf * oa) / (ob - oa)};

		set<P> s;
		if (rhs.on_segment(pi))
			s.insert(pi);
		if (rhs.on_segment(pf))
			s.insert(pf);
		if (on_segment(rhs.pi))
			s.insert(rhs.pi);
		if (on_segment(rhs.pf))
			s.insert(rhs.pf);
		return vector<P>(s.begin(), s.end());
	}
};

// Represents a line by its equation in the form a * x + b * y = c.
// Can be created from two points or directly from constants.
template <class T>
struct line
{
	typedef point<T> P;
	T a, b, c; // line a * x + b * y = c

	explicit line(P p1, P p2) // TODO: test me.
	{
		assert(!(p1 == p2));
		a = p2.y - p1.y;
		b = p1.x - p2.x;
		c = a * p1.x + b * p1.y;

		// In case of int, it is useful to scale down by gcd (e.g to
		// use in a set).
		// Might be useful to normalize here.
	}

	explicit line(T _a, T _b, T _c) : a(_a), b(_b), c(_c) {}

	// Distance from this line to a given point. TODO: test me.
	double dist(P p)
	{
		return (double)abs(a * p.x + b * p.y - c) / sqrt((double)(a * a + b * b));
	}

	// Intersects this line with another given line. See linear_solve2
	// for usage. TODO: test me.
	pair<int, P> intersect(line rhs)
	{
		return linear_solve2(a, b, rhs.a, rhs.b, c, rhs.c);
	}

	// Normalize line to c >= 0, a*a + b*b == 1. Only use with double.
	line normalize()
	{
		double d = P(a, b).dist() * (c < 0 ? -1 : 1);
		return line(a / d, b / d, c / d);
	}

	// Reflects point in current line
	P reflect(P p)
	{
		P res;

		res.x = ((b * b - a * a) * p.x - 2 * a * b * p.y + 2 * a * c) / (a * a + b * b);
		res.y = ((a * a - b * b) * p.y - 2 * a * b * p.x + 2 * b * c) / (a * a + b * b);

		return res;
	}
};

// Represents a circle by its center and radius. Mostly only works
// with double.
template <class T>
struct circle
{
	typedef point<T> P;
	P center;
	T r;

	// Intersects circle with a given line. This does not work with
	// integer types.
	// If there is no intersection, returns 0 and retv is whatever.
	// If intersection is a single point, returns 1 and retv is a pair
	// of equal points.
	// If intersection is two points, return 2 and retv is the two
	// intersection points.
	// Assume points are given in no particular order. If you really
	// need it, should be leftmost first when looking from center of
	// the circle.
	int intersect(line<T> l, pair<P, P> &retv)
	{
		l = l.normalize();
		l.c -= l.a * center.x + l.b * center.y; // Recenter so that we
												// can consider circle
												// center in origin.
		P v(l.a, l.b);
		P p0 = v * l.c; // p0 is the point in the line closest to
						// origin.

		if (p0.dist() > r + EPS) // No intersection.
			return 0;
		else if (p0.dist() > r - EPS) // dist in [r - EPS, r + EPS] -> 
									  //single point intersection at
									  // p0.
		{
			retv = {p0, p0};
			return 1;
		}

		double d = sqrt(r * r - l.c * l.c); // d is distance from p0
											// to the intersection
											// points.
		retv = {center + p0 + v.normal() * d, center + p0 - v.normal() * d};
		return 2;
	}

	// Intersects circle with another circle. This does not work with
	// integer types.
	// This assumes the circles do not have the same center. Check
	// this case if needed, can have 0 or infinite intersection
	// points.
	// If there is no intersection, returns 0 and retv is whatever.
	// If intersection is a single point, returns 1 and retv is a pair
	// of equal points.
	// If intersection is two points, return 2 and retv is the two
	// intersection points.
	// Assume points are given in no particular order. If you really
	// need it, should be leftmost first when looking from center of
	// the rhs circle.
	int intersect(circle rhs, pair<P, P> &retv)
	{
		rhs.center = rhs.center - center;
		int num = rhs.intersect(line<T>(2 * rhs.center.x, 2 * rhs.center.y, rhs.center.x * rhs.center.x + rhs.center.y * rhs.center.y + r * r - rhs.r * rhs.r), retv);
		retv.first = retv.first + center;
		retv.second = retv.second + center;
		return num;
	}

	// Returns a pair of the two points on the circle whose tangent
	// lines intersect p.
	// If p lies within the circle NaN-points are returned. P is
	// intended to be Point<double>.
	// The first point is the one to the right as seen from the point
	// p towards the circle.
	pair<P, P> tangents(P p)
	{
		p = p - center;
		double k1 = r * r / p.dist2();
		double k2 = sqrt(k1 - k1 * k1);
		return {center + p * k1 + p.perp() * k2, center + p * k1 - p.perp() * k2};
	}

	// Finds all the outter tangent lines between current circle and
	// 'other'.
	// Returns the points in the current circle crossed by those
	// tangents in retV1, and in retV2 the points in the circle
	// 'other'.
	// First point of each pair is one line, and second point of each
	// pair is the other.
	// IMPORTANT: You have to verify if one circle is not strictly
	// inside the other.
	// IMPORTANT: Only use with double.
	// In the case that one circle is inside the other with one
	// tangent point p, first points equals to p, and second points
	// are out of the circles and in the tangent line;
	void outter_tangents(circle other, pair<P, P> &retV1, pair<P, P> &retV2)
	{
		T a1 = asin((other.r - r) / (center - other.center).dist());
		T a2 = -atan2(other.center.y - center.y, other.center.x - center.x);
		T a3 = asin(1) - a2 + a1;

		retV1.first = P(center.x + r * cos(a3), center.y + r * sin(a3));
		retV2.first = P(other.center.x + other.r * cos(a3), other.center.y + other.r * sin(a3));

		// In the case there is one tangent point (and circles are
		// external),
		// sets second point in a way that the tangent line can be
		// found.
		if (abs((center - other.center).dist() + min(r, other.r) - max(r, other.r)) < EPS)
		{
			P vec = center - retV1.first;
			retV1.second = retV2.second = retV1.first + vec.rotate(asin(1));
		}

		else
		{
			line<double> l = line<double>(center, other.center);
			retV1.second = l.reflect(retV1.first);
			retV2.second = l.reflect(retV2.first);
		}
	}

	// Finds all the inner tangent lines between current circle
	// and 'other'.
	// Returns the points in the current circle crossed by those
	// tangents in retV1, and in retV2 the points in the circle
	// 'other'.
	// First point of each pair is one line, and second point of each
	// pair is the other.
	// IMPORTANT: You have to verify if one circle does not intersect
	// the other in more than one point (verify centers distance vs
	// r + other.r).
	// IMPORTANT: Only use with double.
	// In the case that the circles intersect in one point p and are
	// exterior to one another, points returned as first will be p,
	// and points returned as second
	// will be points outside the circles in the tangent line)
	void inner_tangents(circle other, pair<P, P> &retV1, pair<P, P> &retV2)
	{
		// Point where inner tangents cross (when they are the same
		// line, it's the point in the segment between circle centers)
		P cp = (other.center * r + center * other.r) / (r + other.r);

		//Finds points for current circle
		double u = r / (center - cp).dist();
		double angle = acos(u);
		P vec = cp - center;
		retV1 = {center + vec.rotate(angle) * u, center + vec.rotate(-angle) * u};

		//find points for other circle
		u = other.r / (other.center - cp).dist();
		angle = acos(u);
		vec = cp - other.center;
		retV2 = {other.center + vec.rotate(angle) * u, other.center + vec.rotate(-angle) * u};

		//In the case there is one tangent point (and circles are
		// external), sets second point in a way that the tangent line
		// can be found.
		if (abs(r + other.r - (center - other.center).dist()) < EPS)
			retV1.second = retV2.second = cp + vec.rotate(asin(1));
	}
};

// The circumcircle of a triangle is the circle intersecting all
// three vertices.
// Returns the unique circle going through points A, B and C (given
// in no particular order).
// This assumes that the triangle has non-zero area.
// TODO: test specifically.
circle<double> circumcircle(const point<double> &A, const point<double> &B, const point<double> &C)
{
	circle<double> retv;
	point<double> a = C - B, b = C - A, c = B - A;
	retv.r = a.dist() * b.dist() * c.dist() / abs(c.cross(b)) / 2;
	retv.center = A + (b * c.dist2() - c * b.dist2()).perp() / b.cross(c) / 2;
	return retv;
}

// Returns TWO TIMES the area of the SIMPLE (non self intersecting)
// polygon defined in pol.
// The area is NEGATIVE if the polygon is in CLOCKWISE.
template <class T>
T area_polygon2(vector<point<T>> pol)
{
	T area = 0;
	for (int i = 0; i < (int)pol.size() - 1; i++)
		area += pol[i].cross(pol[i + 1]);

	area += pol[pol.size() - 1].cross(pol[0]);

	return area;
}

template <class T>
ostream &operator<<(ostream &os, point<T> p)
{
	return os << "(" << p.x << ", " << p.y << ")";
}

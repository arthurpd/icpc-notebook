#include "../../contest/header.hpp"
/**
 * 3D geometry operations. 
 * Status: tested, except for phi and theta
 * Source: https://github.com/kth-competitive-programming/kactl
 */

template <class T>
struct point3D
{
    typedef point3D P;
    typedef const P &R;
    T x, y, z;

    explicit point3D(T x = 0, T y = 0, T z = 0) : x(x), y(y), z(z) {}
    bool operator<(R p) const
    {
        return tie(x, y, z) < tie(p.x, p.y, p.z);
    }
    bool operator==(R p) const
    {
        return tie(x, y, z) == tie(p.x, p.y, p.z);
    }
    P operator+(R p) const { return P(x + p.x, y + p.y, z + p.z); }
    P operator-(R p) const { return P(x - p.x, y - p.y, z - p.z); }
    P operator*(T d) const { return P(x * d, y * d, z * d); }
    P operator/(T d) const { return P(x / d, y / d, z / d); }
    T dot(R p) const { return x * p.x + y * p.y + z * p.z; }
    P cross(R p) const
    {
        return P(y * p.z - z * p.y, z * p.x - x * p.z, x * p.y - y * p.x);
    }
    T dist2() const { return x * x + y * y + z * z; }
    double dist() const { return sqrt((double)dist2()); }
    //Azimuthal angle (longitude) to x-axis in interval [-pi, pi]
    double phi() const { return atan2(y, x); }
    //Zenith angle (latitude) to the z-axis in interval [0, pi]
    double theta() const { return atan2(sqrt(x * x + y * y), z); }
    P unit() const { return *this / (T)dist(); } //makes dist()=1
    //returns unit vector normal to *this and p
    P normal(P p) const { return cross(p).unit(); }
    //returns point rotated 'angle' radians ccw around axis
    P rotate(double angle, P axis) const
    {
        double s = sin(angle), c = cos(angle);
        P u = axis.unit();
        return u * dot(u) * (1 - c) + (*this) * c - cross(u) * s;
    }
};

// Returns the shortest distance on the sphere with radius "radius"
// between the points with azimuthal angles (longitude) f1 and f2
// from x axis and zenith angles (latitude) t1 and t2
// from z axis. All angles measured in radians.
// The algorithm starts by converting the spherical coordinates
// to cartesian coordinates so if that is what you have you can
// use only the two last rows. dx*radius is then the difference
// between the two points in the x direction and d*radius is the
// total distance between the points.
double spherical_distance(double f1, double t1,
                          double f2, double t2, double radius)
{
    double dx = cos(t2) * cos(f2) - cos(t1) * cos(f1);
    double dy = cos(t2) * sin(f2) - cos(t1) * sin(f1);
    double dz = sin(t2) - sin(t1);
    double d = sqrt(dx * dx + dy * dy + dz * dz);
    return radius * 2 * asin(d / 2);
}
// Testado com o geogebra
// Valores usados/Saidas esperadas: (in )
#include "../2d.cpp"
#define point point<double>
#define circle circle<double>
int main() {
  int n = 5;
  while (n--) {
    point c1, c2;
    double r1, r2;
    cin >> c1.x >> c1.y >> r1;
    cin >> c2.x >> c2.y >> r2;
    circle cir1, cir2;
    cir1.center = c1;
    cir1.r = r1;
    cir2.center = c2;
    cir2.r = r2;
    pair<point, point> pi1, pi2, pe1, pe2;
    cir1.outter_tangents(cir2, pe1, pe2);
    cir1.inner_tangents(cir2, pi1, pi2);
    printf("(%.2f %.2f)(%.2f %.2f)(%.2f %.2f)(%.2f %.2f)\n", pi1.first.x,
           pi1.first.y, pi1.second.x, pi1.second.y, pi2.first.x,
           pi2.first.y, pi2.second.x, pi2.second.y);
    printf("(%.2f %.2f)(%.2f %.2f)(%.2f %.2f)(%.2f %.2f)\n", pe1.first.x,
           pe1.first.y, pe1.second.x, pe1.second.y, pe2.first.x,
           pe2.first.y, pe2.second.x, pe2.second.y);
    cout << endl;
  }
}

// https://open.kattis.com/problems/airlinehub
#include "../3d.cpp"
double to_rad(double a) {
  double res = a * M_PI / 180.0;
  while (res < 0) {
    res += 2 * M_PI;
  }
  return res;
}
int main() {
  ll n;
  while (scanf("%lld", &n) != EOF) {
    vector<pair<double, double>> vet_points(n);
    for (int i = 0; i < n; i++) {
      scanf("%lf%lf", &vet_points[i].first, &vet_points[i].second);
    }
    double best_v = 1e9;
    int best_e;
    for (int i = 0; i < n; i++) {
      double max_dist = 0;
      for (int j = 0; j < n; j++) {
        max_dist = max(max_dist,
                       spherical_distance(to_rad(vet_points[i].second),
                                          to_rad(vet_points[i].first),
                                          to_rad(vet_points[j].second),
                                          to_rad(vet_points[j].first), 1));
      }
      if (max_dist <= best_v) {
        best_v = max_dist;
        best_e = i;
      }
    }
    printf("%.2lf %.2lf\n", vet_points[best_e].first,
           vet_points[best_e].second);
  }
}
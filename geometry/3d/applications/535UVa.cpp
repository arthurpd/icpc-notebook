#include "../3d.cpp"
#define RADIUS 6378
map<string, int> str2id;
map<int, string> id2str;
vector<double> vet_lat, vet_longi;
double to_rad(double a) {
  double res = a * M_PI / 180.0;
  while (res < 0) {
    res += 2 * M_PI;
  }
  return res;
}
int main() {
  string city;
  int id = 0;
  while (cin >> city, city != "#") {
    double lat, longi;
    cin >> lat >> longi;
    vet_lat.push_back(lat);
    vet_longi.push_back(longi);
    str2id[city] = id;
    id2str[id] = city;
    ++id;
  }
  string u, v;
  while (cin >> u >> v, u != "#") {
    cout << u << " - " << v << endl;
    if (str2id.count(u) == 0 || str2id.count(v) == 0)
      cout << "Unknown" << endl;
    else {
      double res = spherical_distance(to_rad(vet_longi[str2id[u]]),
                                      to_rad(vet_lat[str2id[u]]),
                                      to_rad(vet_longi[str2id[v]]),
                                      to_rad(vet_lat[str2id[v]]), RADIUS);
      cout << int(round(res)) << " km" << endl;
    }
  }
}
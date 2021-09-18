// https://codeforces.com/contest/300/problem/C
#include "../mod_inverse.cpp"
#define MAXN 1123456
const ll mod = 1e9 + 7;
ll fat[MAXN];
ll choose(ll n, ll k) {
  return (fat[n] * mod_inverse((fat[n - k] * fat[k]) % mod, mod)) % mod;
}
int a, b;
bool good(ll x) {
  while (x) {
    if (x % 10 != a && x % 10 != b) return false;
    x /= 10;
  }
  return true;
}
int main(void) {
  ll n;
  cin >> a >> b >> n;
  fat[0] = 1;
  for (int i = 1; i <= n; i++) fat[i] = (fat[i - 1] * i) % mod;
  ll ans = 0;
  for (int i = 0; i <= n; i++) {
    ll sum = a * i + b * (n - i);
    if (good(sum)) ans = (ans + choose(n, i)) % mod;
  }
  cout << ans << endl;
}

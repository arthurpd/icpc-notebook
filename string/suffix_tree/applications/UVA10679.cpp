/*https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1620
 * Verify if strings are subvstrings of each other
 */
#include "../suffix_tree.cpp"
int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    string s;
    cin >> s;
    suffix_tree st = suffix_tree(s);
    // st.print();
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
      string s;
      cin >> s;
      if (st.verify_substring(s))
        printf("y\n");
      else
        printf("n\n");
    }
  }
  return 0;
}

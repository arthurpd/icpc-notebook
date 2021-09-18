// http://www.spoj.com/problems/ORDERSET/
#include "../key_treap.cpp"
int main(void) {
  int q, x;
  char tp;
  treap::node *root = NULL;
  scanf("%d", &q);
  while (q-- && scanf(" %c %d", &tp, &x)) {
    if (tp == 'I')
      root = treap::insert(root, x);
    else if (tp == 'D')
      root = treap::remove(root, x);
    else if (tp == 'C')
      printf("%d\n", treap::count(root, x));
    else {
      if (treap::get_num(root) < x)
        printf("invalid\n");
      else
        printf("%d\n", treap::kth(root, x));
    }
  }
}

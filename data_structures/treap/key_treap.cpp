#include "../../contest/header.hpp"

/*
	Treap:
		This treap implements something like a c++ set with additional 
		operations: find the k-th element and count elements less than
		a given value.
	
	Time: O(log N) per operation.

	Author: Arthur Pratti Dadalto
*/

namespace treap
{
struct node
{
	int val; // node key.
	int p;   // node heap priority.
	int num; // node subtree size.
	node *left, *right;

	node(int _val) : val(_val), p(rand()), num(1), left(NULL), right(NULL) {}
};

int get_num(node *root)
{
	return (root == NULL) ? 0 : root->num;
}

void update_num(node *root)
{
	root->num = get_num(root->left) + get_num(root->right) + 1;
}

node *rotate_left(node *root)
{
	node *a = root;
	node *b = root->right;

	a->right = b->left;
	b->left = a;
	update_num(a);
	update_num(b);
	return b;
}

node *rotate_right(node *root)
{
	node *a = root;
	node *b = root->left;

	a->left = b->right;
	b->right = a;
	update_num(a);
	update_num(b);
	return b;
}

// Insert new node with key x in treap rooted at root if not already
// there.
node *insert(node *root, int x)
{
	if (root == NULL)
		return new node(x);
	if (x > root->val)
		root->right = insert(root->right, x);
	else if (x < root->val)
		root->left = insert(root->left, x);

	update_num(root);

	if (root->right && root->right->p > root->p)
		root = rotate_left(root);
	if (root->left && root->left->p > root->p)
		root = rotate_right(root);
	return root;
}

// Remove node with key x in treap rooted at root if present.
node *remove(node *root, int x)
{
	if (root == NULL)
		return NULL;
	if (x > root->val)
		root->right = remove(root->right, x);
	else if (x < root->val)
		root->left = remove(root->left, x);
	else if (root->left == NULL)
		root = root->right;
	else if (root->right == NULL)
		root = root->left;
	else if (root->left->p > root->right->p)
	{
		root = rotate_right(root);
		root->right = remove(root->right, x);
	}
	else
	{
		root = rotate_left(root);
		root->left = remove(root->left, x);
	}
	if (root)
		update_num(root);
	return root;
}

// Return the k-th smallest element in tree rooted at root.
int kth(node *root, int k)
{
	if (get_num(root->left) >= k)
		return kth(root->left, k);
	else if (get_num(root->left) + 1 == k)
		return root->val;
	else
		return kth(root->right, k - get_num(root->left) - 1);
}

// Return the number of elements smaller than x in tree rooted at root
int count(node *root, int x)
{
	if (root == NULL)
		return 0;
	if (x < root->val)
		return count(root->left, x);
	else if (x == root->val)
		return get_num(root->left);
	else
		return get_num(root->left) + 1 + count(root->right, x);
}
} // namespace treap

// Balanced Binary Search Tree implementation.

#include <bits/stdc++.h>

using namespace std;

struct node {
	int height, value, size;
	node *l, *r;
};

struct AVL {
	node *root;
	AVL() : root(NULL) {}
	int height(node *cur) {
		if (cur == NULL) return 0;
		return cur->height;
	}
	int size(node *cur) {
		if (cur == NULL) return 0;
		return cur->size;
	}
	int size() {
		return size(root);
	}
	void update(node *cur) {
		if (cur == NULL) return;
		cur->height = max(height(cur->l), height(cur->r));
		cur->size = 1 + size(cur->l) + size(cur->r);
	}
	node *left_rotate(node *cur) {
		node *tmp = cur->l;
		cur->l = tmp->r;
		tmp->r = cur;
		update(cur);
		update(tmp);
		return tmp;
	}
	node *right_rotate(node *cur) {
		node *tmp = cur->r;
		cur->r = tmp->l;
		tmp->l = cur;
		update(cur);
		update(tmp);
		return tmp;
	}
	node *balance(node *cur) {
		if (cur == NULL) return cur;
		if (height(cur->l) - height(cur->r) == 2) {
			node *tmp = cur->l;
			if (height(tmp->l) - height(tmp->r) == -1) {
				cur->l = right_rotate(tmp);
			}
			return left_rotate(cur);
		}
		if (height(cur->l) - height(cur->r) == -2) {
			node *tmp = cur->r;
			if (height(tmp->l) - height(tmp->r) == 1) {
				cur->r = left_rotate(tmp);
			}
			return right_rotate(cur);
		}
		update(cur);
		return cur;
	}
	node *insert(node *cur, int k) {
		if (cur == NULL) {
			cur = new node;
			cur->l = cur->r = NULL;
			cur->height = 1;
			cur->value = k;
			cur->size = 1;
			return balance(cur);
		} else {
			if (k < cur->value) {
				cur->l = insert(cur->l, k);
			} else if (k > cur->value) {
				cur->r = insert(cur->r, k);
			}
			return balance(cur);
		}
	}
	void insert(int k) {
		root = insert(root, k);
	}
	node *erase(node *cur, int k) {
		if (cur == NULL) return cur;
		if (cur->value == k) {
			if (cur->l == NULL || cur->r == NULL) {
				node *tmp = cur->l;
				if (tmp == NULL) tmp = cur->r;
				delete cur;
				return balance(tmp);
			} else {
				node *tmp = cur->r;
				while (tmp->l) tmp = tmp->l;
				cur->value = tmp->value;
				cur->r = erase(cur->r, tmp->value);
				return balance(cur);
			}
		} else if (cur->value > k) {
			cur->l = erase(cur->l, k);
		} else if (cur->value < k) {
			cur->r = erase(cur->r, k);
		}
		return balance(cur);
	}
	void erase(int k) {
		root = erase(root, k);
	}
	int rank(node *cur, int k) {
		if (cur == NULL) return 0;
		if (cur->value <= k)
			return size(cur->l) + 1 + rank(cur->r, k);
		else
			return rank(cur->l, k);
	}
	int rank(int k) {
		return rank(root, k);
	}
	int kth(node *cur, int k) {
		if (size(cur->l) >= k) return kth(cur->l, k);
		if (size(cur->l) + 1 == k) return cur->value;
		return kth(cur->r, k - size(cur->l) - 1);
	}
	int kth(int k) {
		return kth(root, k);
	}
};

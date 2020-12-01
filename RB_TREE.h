#pragma once
#include <cstddef>
#include<iostream>
using namespace std;

enum rbcolor { R, B };

class rbNode
{
public:
	rbcolor color;
	int key;
	rbNode* left;
	rbNode* right;
	rbNode* parent;

	rbNode(int k, rbcolor c, rbNode* l, rbNode* r, rbNode* p)
	{
		key = k;
		color = c;
		left = l;
		right = r;
		parent = p;
	}
};

class rb_tree
{
private:
	rbNode* root; int size;
	void preorder(rbNode* t);
	rbNode* search(int k, rbNode* temp);
	rbNode* find_max(rbNode* tree);
	rbNode* find_min(rbNode* tree);

	void L_rotate(rbNode*& root, rbNode* temp);
	void R_rotate(rbNode*& root, rbNode* temp);

	void insert(rbNode*& root, rbNode* node);
	void remove(rbNode*& root, rbNode* node);
	void re_build_1(rbNode*& root, rbNode* node);
	void re_build_2(rbNode*& root, rbNode* node, rbNode* pa);
public:
	rb_tree() { root = NULL; size = 0; } ~rb_tree() {};

	void preorder();
	rbNode* search(int k) { search(k, root); return NULL; }
	void find_max();
	void find_min();

	void insert(int k);
	void remove(int k);

	bool empty();

};

bool rb_tree::empty()
{
	if (size == 0)return true;
	else
		return false;
}

void rb_tree::preorder(rbNode* t)
{
	if (t != NULL)
	{
		cout << t->key;
		cout << "(";
		if (t->color == R)cout << "R";
		else cout << "B";
		cout << ") ";
		preorder(t->left);
		preorder(t->right);
	}
}
void rb_tree::preorder()
{
	preorder(root);
}

rbNode* rb_tree::search(int k, rbNode* t)
{
	if (t == NULL || t->key == k)
	{
		return t;
	}
	if (k < t->key)
	{
		return search(k, t->left);
	}
	else
		return search(k, t->right);
}

rbNode* rb_tree::find_min(rbNode* tree)
{
	if (tree == NULL)
		return NULL;

	while (tree->left != NULL)
		tree = tree->left;

	return tree;
}
void rb_tree::find_min()
{
	if (root == NULL)return;
	rbNode* temp = find_min(root);
	cout << temp->key << " ";

}

rbNode* rb_tree::find_max(rbNode* tree)
{
	if (tree == NULL)
		return NULL;

	while (tree->right != NULL)
		tree = tree->right;

	return tree;
}

void rb_tree::find_max()
{
	if (root == NULL)return;
	rbNode* temp = find_max(root);
	cout << temp->key;
}

void rb_tree::L_rotate(rbNode*& root, rbNode* temp)
{
	rbNode* to_rotate = temp->right;
	temp->right = to_rotate->left;

	if (to_rotate->left != NULL)
	{
		to_rotate->left->parent = temp;
	}

	to_rotate->parent = temp->parent;

	if (temp->parent == NULL)
	{
		root = to_rotate;
	}

	else
	{
		if (temp->parent->left == temp)
			temp->parent->left = to_rotate;
		else
			temp->parent->right = to_rotate;
	}

	to_rotate->left = temp;
	temp->parent = to_rotate;
}

void rb_tree::R_rotate(rbNode*& root, rbNode* temp)
{
	rbNode* to_rotate = temp->left;
	temp->left = to_rotate->right;

	if (to_rotate->right != NULL)
	{
		to_rotate->right->parent = temp;
	}

	to_rotate->parent = temp->parent;

	if (temp->parent == NULL)
	{
		root = to_rotate;
	}

	else
	{
		if (temp->parent->right == temp)
			temp->parent->right = to_rotate;
		else
			temp->parent->left = to_rotate;
	}

	to_rotate->right = temp;
	temp->parent = to_rotate;
}

void rb_tree::re_build_1(rbNode*& root, rbNode* node)
{
	rbNode* pa; rbNode* gpa;

	while ((pa = node->parent) && pa->color == R)
	{
		gpa = pa->parent;

		if (pa == gpa->left)
		{
			rbNode* uncle = gpa->right;
			if (uncle && uncle->color == R)
			{
				uncle->color = B;
				pa->color = B;
				gpa->color = R;
				node = gpa;
				continue;
			}

			if (node == pa->right)
			{
				rbNode* temp;
				L_rotate(root, pa);
				temp = pa;
				pa = node;
				node = temp;
			}
			pa->color = B;
			gpa->color = R;
			R_rotate(root, gpa);
		}

		else
		{
			rbNode* uncle = gpa->left;
			if (uncle && uncle->color == R)
			{
				uncle->color = B;
				pa->color = B;
				gpa->color = R;
				node = gpa;
				continue;
			}

			if (pa->left == node)
			{
				rbNode* temp;
				R_rotate(root, pa);
				temp = pa;
				pa = node;
				node = temp;
			}

			pa->color = B;
			gpa->color = R;
			L_rotate(root, gpa);
		}
	}
	root->color = B;
}

void rb_tree::insert(rbNode*& root, rbNode* node)
{
	rbNode* y = NULL; rbNode* x = root;
	while (x != NULL)
	{
		y = x;
		if (node->key < x->key)
		{
			x = x->left;
		}
		else
			x = x->right;
	}

	node->parent = y;

	if (y != NULL)
	{
		if (node->key < y->key)
			y->left = node;
		else
			y->right = node;
	}
	else
		root = node;
	node->color = R;
	++size;
	re_build_1(root, node);
}

void rb_tree::insert(int k)
{
	rbNode* temp = new rbNode(k, R, NULL, NULL, NULL);
	insert(root, temp);
}


void rb_tree::re_build_2(rbNode*& root, rbNode* node, rbNode* pa)
{
	if (size == 1)
	{
		root = NULL;
		return;
	}
	if (this->empty())
	{
		return;
	}
	rbNode* p;

	while (!node || node->color == B && node != root)
	{
		if (pa->left == node)//pa 是 nullptr
		{
			p = pa->right;
			if (p->color == R)
			{
				p->color = B;
				pa->color = R;
				L_rotate(root, pa);
				p = pa->right;
			}

			if ((!p->left || p->left->color == B) && (!p->right || p->right->color == B))
			{
				p->color = R;
				node = pa;
				pa = node->parent;
			}

			else
			{
				if (!p->right || p->right->color == B)
				{
					p->left->color = B;
					p->color = R;
					R_rotate(root, p);
					p = pa->right;
				}
				if (p == NULL)return;
				p->color = pa->color;
				pa->color = B;
				p->right->color = B;
				L_rotate(root, pa);
				node = root;
				break;

			}

		}
		else
		{
			p = pa->left;
			if (p->color == R)
			{
				p->color = B;
				pa->color = R;
				R_rotate(root, pa);
				p = pa->left;
			}
			if ((!p->left || p->left->color == B) && (!p->right || p->right->color == B))
			{
				p->color = R;
				node = pa;
				pa = node->parent;
			}
			else
			{
				if (!p->left || p->left->color == B)
				{
					p->right->color = B;
					p->color = R;
					L_rotate(root, p);
					p = pa->left;
				}
				if (p == NULL)return;
				p->color = pa->color;
				pa->color = B;
				p->left->color = B;
				R_rotate(root, pa);
				node = root;
				break;
			}
		}
	}
	if (node)
		node->color = B;
}

void rb_tree::remove(rbNode*& root, rbNode* node)
{
	rbNode* child; rbNode* pa;
	rbcolor co;

	if ((node->left != NULL) && (node->right != NULL))
	{
		rbNode* rp_node = node->right;
		while (rp_node->left != NULL)
			rp_node = rp_node->left;

		if (node->parent)
		{
			if (node->parent->left == node)
				node->parent->left = rp_node;
			else
				node->parent->right = rp_node;
		}
		else
		{
			root = rp_node;
		}

		child = rp_node->right;
		pa = rp_node->parent;
		co = rp_node->color;

		if (pa == node)
		{
			pa = rp_node;
		}
		else
		{
			if (child)
				child->parent = pa;

			pa->left = child;
			rp_node->right = node->right;
			node->right->parent = rp_node;
		}
		rp_node->parent = node->parent;
		rp_node->color = node->color;
		rp_node->left = node->left;
		node->left->parent = rp_node;
		if (co == B)
			re_build_2(root, child, pa);

		
		return;
	}


	if (node->left)
	{
		child = node->left;
	}
	else {
		child = node->right;
	}
	pa = node->parent;
	co = node->color;
	if (child)child->parent = pa;
	if (pa)
	{
		if (pa->left == node)pa->left = child;
		else pa->right = child;
	}
	else
		root = child;
	if (co == B)
		re_build_2(root, child, pa);

}

void rb_tree::remove(int k)
{

	rbNode* temp;
	if ((temp = search(k, root)) != NULL)
	{
		remove(root, temp);
		--size;
	}
}

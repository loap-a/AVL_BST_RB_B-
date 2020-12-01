#pragma once
#include <queue>
#include <algorithm>
#include<iostream>
#include<stack>
using namespace std;

struct avl_node {
	int val;

	avl_node* left;
	avl_node* right;
	avl_node* parent;
	int height;
	avl_node(int i, avl_node* l, avl_node* r,avl_node*p, int h) :
		val(i), left(l), right(r), height(h) ,parent(p){}
};

class avl {
private:
	avl_node* root;
	int size;
	avl_node* LL_rotate(avl_node* tree);
	avl_node* LR_rotate(avl_node* tree);
	avl_node* RR_rotate(avl_node* tree);
	avl_node* RL_rotate(avl_node* tree);
	avl_node* remove(avl_node* tree, avl_node* temp);
	avl_node* search(avl_node* temp, int k);
	avl_node* insert(avl_node* tree, int k);
	avl_node* find_houji(avl_node* temp);
	avl_node* find_qianqu(avl_node* temp);
	int height(avl_node* tree);
	void preorder(avl_node* tree);


public:
	avl() { root = NULL; size = 0; }

	void insert(int k);
	bool check();
	void remove(int k);
	bool search(int k);
	void printCengci(int n);
	void preorder();

	bool empty();
};
bool avl::empty()
{
	if (this->size == 0)return true;
	else
		return false;
}
void avl::preorder(avl_node* tree)
{
	if (tree)
	{		
		cout << tree->val << " ";
		preorder(tree->left);
		preorder(tree->right);
	}
}

void avl::preorder()
{
	preorder(root);
}

void avl::printCengci(int n)
{
 queue<avl_node*>queue_node;
queue_node.push(root);
avl_node* temp;
int i = 1;
while (!queue_node.empty())
{
	temp = queue_node.front();
	queue_node.pop();
	if (i == n) cout << temp->val;
	else
		cout << temp->val << " "; ++i;
	if (temp->left != NULL)
	{
		queue_node.push(temp->left);
	}
	if (temp->right != NULL)
	{
		queue_node.push(temp->right);
	}
 }
}
avl_node* avl::LL_rotate(avl_node*tree)
{
	avl_node* temp;
	temp = tree->left;
	if (temp == NULL) temp = tree;
	tree->left = temp->right;
	temp->right = tree;
	tree->height = ((height(tree->left) > height(tree->right)) ? height(tree->left) : height(tree->right)) + 1;
	temp->height = ((tree->height > height(temp->left)) ? tree->height : height(temp->left)) + 1;
	return temp;
}

avl_node* avl::LR_rotate(avl_node* tree)
{
	tree->left = RR_rotate(tree->left);
	return LL_rotate(tree);
}
avl_node* avl::RR_rotate(avl_node* tree)
{
	avl_node* temp = tree->right;
	if (temp == NULL)temp = tree;
	tree->right = temp->left;
	temp->left = tree;
	tree->height = ((height(tree->left) > height(tree->right)) ? height(tree->left) : height(tree->right)) + 1;
	temp->height = ((tree->height > height(temp->right)) ? tree->height : height(temp->right)) + 1;
	return temp;
}
avl_node* avl::RL_rotate(avl_node* tree)
{
	tree->right = LL_rotate(tree->right);
	return RR_rotate(tree);
}
avl_node* avl::insert(avl_node* tree, int k)
{
	/*
	if (tree == 0) {
		tree = new avl_node(k, 0, 0, 0, 0);
	}
	else if (k < tree->val) {
		tree->left = insert(tree->left,k);
		if (height(tree->left) - height(tree->right) == 2)
			if (k < tree->left->val)
				tree = LL_rotate(tree);
			else
				tree = LR_rotate(tree);
	}
	else if (k > tree->val) {
		tree->right = insert(tree->right,k);
		if (height(tree->right) - height(tree->left) == 2)
			if (k > tree->right->val)
				tree = RR_rotate(tree);
			else
				tree = RL_rotate(tree);
	}
	tree->height = ((height(tree->left) > height(tree->right)) ? height(tree->left) : height(tree->right)) + 1;
	return tree;
	*/
	if (root == NULL)
	{
		root = new avl_node(k, 0, 0, 0, 0);
		++size;
		return root;
	}
	avl_node* parent = NULL; avl_node* temp = root;
	while (temp)
	{
		if (temp->val < k)
		{
			parent = temp;
			temp = temp->right;
		}
		else if (temp->val > k)
		{
			parent = temp;
			temp = temp->left;
		}
		else
		{
			return NULL;
		}
	}
	temp = new avl_node(k, 0, 0, 0, 0);
	temp->parent = parent;

	if (parent->val > k)
		parent->left = temp;
	else
		parent->right = temp;

	while (parent)
	{
		if (temp == parent->left)
		{
			++parent->left->height;
		}
		else if (temp == parent->right)
		{
			++parent->right->height;
		}
		if (height(parent->left) - height(parent->right) == 2)
		{
			if (k < parent->val)
			{
				parent = LL_rotate(parent);
			}
			else
				parent = LR_rotate(parent);
			break;
		}
		
		if (height(parent->right) - height(parent->left) == 2)
		{
			if (k > parent->val)
				parent = RR_rotate(parent);
			else
				parent = RL_rotate(parent);
			break;
		}
		parent->height = max(height(parent->left), height(parent->right)) + 1;
	}
	++size;
	return temp;
}


avl_node* avl::remove(avl_node* tree, avl_node* temp)
{
	if (tree == NULL || temp == NULL)
		return NULL;


	if (tree->left!=NULL&&tree->left->val == temp->val)
	{
		if (tree->left->left == NULL && tree->left->right == NULL)
		{
			tree->left = NULL;
			tree->height = ((height(tree->left) > height(tree->right)) ? height(tree->left) : height(tree->right)) + 1;
			--size;
			return tree;
		}
	}
	if (tree->right!=NULL&&tree->right->val == temp->val)
	{
		if (tree->right->left == NULL && tree->right->right == NULL)
		{
			tree->right = NULL;
			tree->height = ((height(tree->left) > height(tree->right)) ? height(tree->left) : height(tree->right)) + 1;
			--size;
			return tree;
		}
	}


	if (temp->val < tree->val)
	{
		tree->left = remove(tree->left, temp);

		if (height(tree->right) - height(tree->left) == 2)
		{
			avl_node* to_rotate = tree->right;
			if (height(to_rotate->right) > height(to_rotate->left))
			{
				tree = RR_rotate(tree);
			}
			else
			{
				tree = RL_rotate(tree);
			}
		}
	}

	else if (temp->val > tree->val)
	{
		tree->right = remove(tree->right, temp);

		if (height(tree->left) - height(tree->right) == 2)
		{
			avl_node* to_rotate = tree->left;
			if (height(to_rotate->left) > height(to_rotate->right))
			{
				tree = LL_rotate(tree);
			}
			else
			{
				tree = LR_rotate(tree);
			}
		}
	}

	else
	{
		if (tree->left && tree->right)
		{
			if (height(tree->left) >= height(tree->right))
			{
				avl_node* to_delete = find_qianqu(tree);
				tree->val = to_delete->val;
				tree->left = remove(tree->left, to_delete);
				tree->height = ((height(tree->left) > height(tree->right)) ? height(tree->left) : height(tree->right)) + 1;
			}

			else
			{
				avl_node* to_delete = find_houji(tree);
				tree->val = to_delete->val;
				tree->right = remove(tree->right, to_delete);
				tree->height = ((height(tree->left) > height(tree->right)) ? height(tree->left) : height(tree->right)) + 1;
			}
		}
		else
		{
			if (tree->left != NULL || tree->right != NULL)
			{
				if (tree->left != NULL)	tree = tree->left;
				else tree = tree->right;
				tree->height = ((height(tree->left) > height(tree->right)) ? height(tree->left) : height(tree->right)) + 1;
			}
		}
	}
	tree->height = ((height(tree->left) > height(tree->right)) ? height(tree->left) : height(tree->right)) + 1;
	--size;
	return tree;
}
avl_node* avl::search(avl_node* temp, int k)
{
	while (temp != NULL && temp->val != k)
	{
		if (k < temp->val)
			temp = temp->left;
		else
			temp = temp->right;
	}
	return temp;
}
avl_node* avl::find_houji(avl_node* temp)
{
	if (temp == NULL)
		return NULL;

	temp = temp->right;
	while (temp->left!=NULL)
	{
		temp = temp->left;
	}
	return temp;
}
avl_node* avl::find_qianqu(avl_node* temp)
{
	if (temp == NULL)
		return NULL;
	temp = temp->left;
	while (temp->right!=NULL)
	{
		temp = temp->right;
	}
	return temp;
}

int avl::height(avl_node* tree)
{
	if (tree == NULL)
		return -1;
	else
		return tree->height;
}

inline void avl::insert(int k)
{
	root = insert(root, k);
}

inline bool avl::check()
{
	if (root == NULL) return true;

	queue<avl_node*> queue_tree;
	queue_tree.push(root);
	bool flag = false;
	while (!queue_tree.empty())
	{
		avl_node* front = queue_tree.front();
		queue_tree.pop();
		if (front->left != NULL)
		{
			if (flag) return false;
			queue_tree.push(front->left);
		}
		else
		{
			flag = true;
		}
		if (front->right != NULL)
		{
			if (flag) return false;
			queue_tree.push(front->right);
		}
		else
		{
			flag = true;
		}
	}
	return true;
}

inline void avl::remove(int k)
{
	avl_node* temp;
	
		temp = new avl_node(k, NULL, NULL,NULL, 0);
	
	
	root=remove(root, temp);
}

inline bool avl::search(int k)
{
	avl_node* temp = search(root, k);
	if (temp != NULL)
		return true;
	else
		return false;
}


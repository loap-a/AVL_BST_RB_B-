#pragma once
#include<iostream>
using namespace std;

class bs_node
{
public:
	int val;
	bs_node* left;
	bs_node* right;
	bs_node* parent;
	bs_node(int k) { val = k; left = NULL; right = NULL; parent = NULL; }
};

class binary_search_tree
{
private:
	int size;
	bs_node* root;
	void insert(bs_node*&tree,int k);
	bs_node* remove(bs_node*&tree,bs_node*temp);
    bs_node* search(bs_node*tree,int k);
	bs_node* find_qianqu(bs_node* tree);
	bs_node* find_houji(bs_node* tree);

	void preOrder(bs_node* tree);
public:
	binary_search_tree() { root = NULL; size = 0; }
	void insert(int k);
	void remove(int k);
	bool search(int k);
	void preOrder();
	void give_me_size() { cout << size << endl; }
	bool empty();
};

bool binary_search_tree::empty()
{
	if (size == 0)return true;
	else
		return false;
}
void binary_search_tree::preOrder(bs_node* tree)
{
	if (tree)
	{
		cout << tree->val << " ";
		preOrder(tree->left);
		preOrder(tree->right);
	}
}
void binary_search_tree::preOrder()
{
	preOrder(root);
}
void binary_search_tree::insert(int k)
{
	insert(root, k);	
}


bool binary_search_tree::search(int k)
{
	if (search(root, k) != NULL)
		return true;
	else
		return false;
}

void binary_search_tree::insert(bs_node*& tree, int e)
{
	
	bs_node* parent = NULL; bs_node* _root = root;
	
	while (_root)
	{
		parent = _root;
		if (e < _root->val)
			_root = _root->left;
		else if (e > _root->val)
			_root = _root->right;
		else
			return;
	}
	bs_node* temp = new bs_node(e);
	if (root)
	{
		if (e < parent->val)parent->left = temp;
		else parent->right = temp;
	}
	else
		root = temp;
	
	
	++size;
}

bs_node* binary_search_tree::find_houji(bs_node* tree)
{
	if (tree != NULL)
	{
		tree = tree->right;
		while (tree->left != NULL)
		{
			tree = tree->left;
		}
		return tree;
	}
}
bs_node* binary_search_tree::find_qianqu(bs_node* tree)
{
	if (tree != NULL)
	{
		tree = tree->left;
		while (tree->right != NULL)
		{
			tree = tree->left;
		}
		return tree;
	}
}

void binary_search_tree::remove(int k)
{
	
		bs_node* temp = new bs_node(k);
		remove(root, temp);
}
bs_node* binary_search_tree::remove(bs_node*& tree, bs_node* temp)
{
	/*
	if (tree == NULL || temp == NULL) return NULL;

	if (tree->left != NULL && tree->left->val == temp->val)
	{
		if (tree->left->left == NULL && tree->left->right == NULL)
		{
			tree->left = NULL;
			return tree;
		}
	}
	if (tree->right != NULL && tree->right->val == temp->val)
	{
		if (tree->right->left == NULL && tree->right->right == NULL)
		{
			tree->right = NULL;
			return tree;
		}
	}

	if (temp->val < tree->val)
	{
		tree->left = remove(tree->left, temp);
	}
	else if (temp->val > tree->val)
	{
		tree->right = remove(tree->right, temp);
	}
	else
	{
		if (tree->left && tree->right)
		{
			bs_node* to_delete = find_houji(tree);
			tree->val = to_delete->val;
			tree->right = remove(tree->right, to_delete);
		}
		if (tree->left || tree->right)
		{
			if (tree->left)
			{
				tree = tree->left;
			}
			else
				tree = tree->right;
		}
	}
	return tree;
	*/
	--size;
	bs_node* parent = NULL; bs_node* root = NULL;
	if ((temp->left == NULL) || (temp->right == NULL))
	{
		root = temp;
	}
	else
		root = find_houji(temp);

	if (root->left != NULL)
	{
		parent = root->left;
	}
	else parent = root->right;

	if (parent != NULL)
	{
		parent->parent = root->parent;
	}

	if (root->parent == NULL)
	{
		tree = parent;
	}
	else if (root == root->parent->left)
		root->parent->left = parent;
	else
		root->parent->right = parent;

	if (root != temp)
		temp->val = root->val;

	--size;
	return root;

}

bs_node* binary_search_tree::search(bs_node* tree, int k)
{
	while ((tree != NULL) && (tree->val != k))
	{
		if (k < tree->val)
		{
			tree = tree->left;
		}
		 if((tree!=NULL)&&k>tree->val)
			tree = tree->right;
		 if ((tree != NULL) && tree->val == k)
		 {
			 return tree;
	      }
	}
	return tree;
}
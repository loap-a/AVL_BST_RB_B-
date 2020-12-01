#pragma once
#include <iostream>
using namespace std;
struct B_node
{
	int key_count;
	int* key;
	B_node** child;
	bool leaf;
};

class BTree
{
private:

	B_node* root;
	int degree;
	int size;

	B_node* search(B_node* temp, int key);
	B_node* create_new_node();
	B_node* merge(B_node* pa, B_node* le, B_node* ri, int index);
	void split(B_node* pa, int index, B_node* ch);
	void insert(B_node* temp, int key);
	void eliminate_node(B_node* temp);
	void eliminate_tree(B_node* temp);
	void print(B_node* temp);
	int find_max(B_node* temp);
	int find_min(B_node* temp);
	bool remove(B_node* temp, int key);

public:
	BTree()
	{
		root = NULL; degree = 256; size = 0;
	}
	~BTree()
	{
		eliminate_tree(root);
		delete root;
	}
	void insertt(int k) { insert(k); ++size; }
	bool insert(int key);
	bool remove(int key);
	void search(int key) { search(root, key); }
	void print() { print(root); };
	void give_me_size() { cout << size; }


};

B_node* BTree::create_new_node()
{
	B_node* temp = new B_node();
	temp->key = new int[2 * degree];
	temp->child = new B_node*[2 * degree + 1];

	for (int i = 0; i < 2 * degree; i++)
	{
		temp->key[i] = 0;
		temp->child[i] = NULL;
	}
	temp->child[2 * degree] = NULL;

	return temp;
}

B_node* BTree::search(B_node* temp, int key)
{
	int i = 1;
	while (i <= temp->key_count && key > temp->key[i])
		i++;

	if (i < temp->key_count && key == temp->key[i])
		return temp->child[i];

	if (temp->leaf)
		return NULL;
	else
		return search(temp->child[i], key);
}

bool BTree::insert(int key)
{
	
	B_node* temp = root;
	if (temp == NULL)
	{
		temp = create_new_node();
		temp->leaf = true;
		temp->key_count = 0;
		root = temp;
		
	}

	if (temp != NULL && temp->key_count == (2 * degree - 1))
	{
		B_node* tempp = create_new_node(); 
		root = tempp;
		tempp->leaf = false;
		tempp->key_count = 0;
		tempp->child[1] = temp;
		split(tempp, 1, temp);
		insert(tempp, key);
		
	}
	else
	{
		insert(temp, key);
		
	}
	return true;
}

void BTree::split(B_node* pa, int index, B_node* ch)
{
	B_node* temp = create_new_node();
	temp->leaf = ch->leaf;
	temp->key_count = degree - 1;

	for (int j = 1; j < degree; j++)
		temp->key[j] = ch->key[j + degree];

	if (!ch->leaf)
		for (int j = 1; j <= degree; j++)
			temp->child[j] = ch->child[j + degree];

	ch->key_count = degree - 1;

	for (int j = pa->key_count + 1; j > index; j--)
		pa->child[j + 1] = pa->child[j];
	pa->child[index + 1] = temp;

	for (int j = pa->key_count; j >= index; j--)
		pa->key[j + 1] = pa->key[j];
	pa->key[index] = ch->key[degree];
	pa->key_count++;
}

void BTree::insert(B_node* temp, int key)
{
	int i = temp->key_count;

	if (temp->leaf)
	{
		while (i >= 1 && key < temp->key[i])
		{
			temp->key[i + 1] = temp->key[i];
			i--;
		}

		temp->key[i + 1] = key;
		temp->key_count++;
	}
	else
	{
		while (i >= 1 && key < temp->key[i])
			i--;
		i++;

		if (temp->child[i]->key_count == (2 * degree - 1))
		{
			split(temp, i, temp->child[i]);

			if (key > temp->key[i])
				i++;
		}

		insert(temp->child[i], key);
	}
}

bool BTree::remove(int key)
{
	return remove(root, key);
}

bool BTree::remove(B_node* temp, int key)
{
	int i = 1;

	while (i <= temp->key_count && key > temp->key[i])
		i++;

	if (temp->leaf)
	{
		if (i <= temp->key_count && key == temp->key[i])
		{
			for (int j = i; j < temp->key_count; j++)
				temp->key[j] = temp->key[j + 1];
			temp->key_count--;

			return true;
		}
		else
		{
			return false;
		}
	}

	if (i <= temp->key_count && key == temp->key[i])
	{
		if (temp->child[i]->key_count >= degree)
		{
			key = find_max(temp->child[i]);
			temp->key[i] = key;

			return remove(temp->child[i], key);
		}
		else if (temp->child[i + 1]->key_count >= degree)
		{
			key = find_min(temp->child[i + 1]);
			temp->key[i] = key;

			return remove(temp->child[i + 1], key);
		}
		else
		{
			B_node* ch = merge(temp, temp->child[i], temp->child[i + 1], i);

			return remove(ch, key);
		}
	}
	else if (temp->child[i]->key_count == degree - 1)
	{
		if (i > 1 && temp->child[i - 1]->key_count >= degree)
		{
			B_node* mid_node = temp->child[i];
			B_node* front_node = temp->child[i - 1];

			int nPreNodeKeyCount = front_node->key_count;

			for (int j = mid_node->key_count + 1; j > 1; j--)
				mid_node->key[j] = mid_node->key[j - 1];
			mid_node->key[1] = temp->key[i - 1];

			for (int j = mid_node->key_count + 2; j > 1; j--)
				mid_node->child[j] = mid_node->child[j - 1];
			mid_node->child[1] = front_node->child[nPreNodeKeyCount + 1];
			mid_node->key_count++;

			temp->key[i - 1] = front_node->key[nPreNodeKeyCount];

			front_node->key[nPreNodeKeyCount] = 0;
			front_node->key[nPreNodeKeyCount + 1] = NULL;
			front_node->key_count--;

			return remove(mid_node, key);
		}
		else if (i <= temp->key_count && temp->child[i + 1]->key_count >= degree)
		{
			B_node* mid_node = temp->child[i];
			B_node* front_node = temp->child[i + 1];

			int next_key_count = front_node->key_count;
			int mid_key_count = mid_node->key_count;

			mid_node->key[mid_key_count + 1] = temp->key[i];
			mid_node->child[mid_key_count + 2] = front_node->child[1];
			mid_node->key_count++;

			temp->key[i] = front_node->key[1];

			for (int j = 1; j < next_key_count; j++)
				front_node->key[j] = front_node->key[j + 1];
			for (int j = 1; j <= next_key_count; j++)
				front_node->child[j] = front_node->child[j + 1];
			front_node->key_count--;

			return remove(mid_node, key);
		}
		else
		{
			if (i > temp->key_count)
				i--;

			B_node* ch = merge(temp, temp->child[i], temp->child[i + 1], i);

			return remove(ch, key);
		}
	}

	return remove(temp->child[i], key);
}

B_node* BTree::merge(B_node* pa, B_node* le, B_node* ri, int index)
{
	for (int i = 1; i < degree; i++)
		le->key[degree + i] = ri->key[i];
	le->key[degree] = pa->key[index];

	for (int i = 1; i <= degree; i++)
		le->child[degree + i] = ri->child[i];
	le->key_count = 2 * degree - 1;

	for (int i = index; i < pa->key_count; i++)
		pa->key[i] = pa->key[i + 1];

	for (int i = index + 1; i <= pa->key_count; i++)
		pa->child[i] = pa->child[i + 1];
	pa->key_count--;

	eliminate_node(ri);

	if (pa->key_count == 0)
	{
		eliminate_node(root);
		root = le;
	}

	return le;
}

void BTree::eliminate_node(B_node* temp)
{
	delete[] temp->key;
	delete[] temp->child;
	delete temp;
}

int BTree::find_max(B_node* temp)
{
	while (!temp->leaf)
	{
		temp = temp->child[temp->key_count + 1];
	}

	return temp->key[temp->key_count];
}

int BTree::find_min(B_node* temp)
{
	while (!temp->leaf)
	{
		temp = temp->child[1];
	}

	return temp->key[1];
}

void BTree::eliminate_tree(B_node* temp)
{
	if (temp->leaf)
	{
		delete[] temp->key;
		delete[] temp->child;
	}
	else
	{
		for (int i = 1; i <= temp->key_count + 1; i++)
		{
			eliminate_tree(temp->child[i]);
			delete temp->child[i];
		}

		delete[] temp->key;
		delete[] temp->child;
	}
}

void BTree::print(B_node* temp)
{
	if (temp->leaf)
	{
		for (int i = 1; i <= temp->key_count; i++)
		{
		  cout << temp->key[i] << " ";
		}
	}
	else
	{
		for (int i = 1; i <= temp->key_count + 1; i++)
			print(temp->child[i]);

		for (int i = 1; i <= temp->key_count; i++)
		{
		  cout << temp->key[i] << " ";
		}
		cout <<endl;
	}
}
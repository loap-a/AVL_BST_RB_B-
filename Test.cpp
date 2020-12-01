#include<NORMAL.h>
#include<RB_TREE.h>
#include<AVL_TREE.h>
#include<iostream>
#include<vector>
#include<random>
#include<B-TREE.h>
#include<time.h>
#include<fstream>
using namespace std;


int main()
{
	vector<binary_search_tree*> binary_tree(51, new binary_search_tree());
	vector<avl*> avl_tree(51, new avl());
	vector<rb_tree*>RB_tree(51, new rb_tree());
	vector<BTree*> B_tree(51, new BTree());
	vector<vector<double>>insert_time(5,vector<double>(0));
	vector<vector<double>>search_time(5, vector<double>(0));
	vector<vector<double>>delete_time(5, vector<double>(0));
	vector<int>test_num; vector<int>copy_num;
	clock_t search_1, search_2, insert_1, insert_2, delete_1, delete_2;
	int N = 10000;
	for (int i = 1; i <= 50; ++i)
	{
		test_num.clear();
		for (int j = 1; j <= N; ++j)
		{
			test_num.push_back(rand());		
		}
		sort(test_num.begin(), test_num.end());


		insert_1 = clock(); 
		for (int j = 1; j <= N; ++j)
		{
		   //binary_tree[i]->insert(test_num[j-1]);
			
		}
		insert_2 = clock();
		insert_time[1].push_back((double)((double)insert_2 - (double)insert_1) * 1.0 / CLOCKS_PER_SEC * 1000);

		insert_1 = clock();
		for (int j = 1; j <= N; ++j)
		{
			//avl_tree[i]->insert(test_num[j - 1]);
		}
		insert_2 = clock();
		insert_time[2].push_back((double)((double)insert_2 - (double)insert_1) * 1.0 / CLOCKS_PER_SEC * 1000);

		insert_1 = clock();
		for (int j = 1; j <= N; ++j)
		{
			//RB_tree[i]->insert(test_num[j - 1]);
		}
		insert_2 = clock();
		insert_time[3].push_back((double)((double)insert_2 - (double)insert_1) * 1.0 / CLOCKS_PER_SEC * 1000);

		insert_1 = clock();
		for (int j = 1; j <= N; ++j)
		{
			//B_tree[i]->insertt(test_num[j - 1]);
		}
		insert_2 = clock();
		insert_time[4].push_back((double)((double)insert_2 - (double)insert_1) * 1.0 / CLOCKS_PER_SEC * 1000);


		
		/// //////////////////////////////////////////////
	
		search_1 = clock();
		for (int j = 10000 * (i / 2); j < 10000 * (i / 2) + 10000; ++j)
		{
			int temp = rand();
			//binary_tree[i]->search(temp);
			
		}
		search_2 = clock();
		search_time[1].push_back((double)((double)search_2 - (double)search_1) * 1.0 / CLOCKS_PER_SEC * 1000);

		delete_1 = clock();
		for (int j = 0;j<N; ++j)
		{
		   // binary_tree[i]->remove(test_num[rand()%N]);
		}
		delete_2 = clock(); 
		delete_time[1].push_back((double)((double)delete_2 - (double)delete_1) * 1.0 / CLOCKS_PER_SEC * 1000);
		
		/// ///////////////////////////////////////////////////

		search_1 = clock();
		for (int j = 10000*(i/2); j < 10000*(i/2)+10000; ++j)
		{
			int temp = rand();
			//avl_tree[i]->search(temp);
		}
		search_2 = clock();
		search_time[2].push_back((double)((double)search_2 - (double)search_1) * 1.0 / CLOCKS_PER_SEC * 1000);

		delete_1 = clock();
		for (int j = 0;j<N; ++j)
		{
			//avl_tree[i]->remove(test_num[rand()%N]);
			
		}
		delete_2 = clock();
		delete_time[2].push_back((double)((double)delete_2 - (double)delete_1) * 1.0 / CLOCKS_PER_SEC * 1000);

		///////////////////////////////////////////////////////

		
		search_1 = clock();
		for (int j = 10000 * (i / 2); j < 10000 * (i / 2) + 10000; ++j)
		{
			int temp = rand();
			//RB_tree[i]->search(temp);

		}
		search_2 = clock();
		search_time[3].push_back((double)((double)search_2 - (double)search_1) * 1.0 / CLOCKS_PER_SEC * 1000);

		delete_1 = clock();
		for (int j = 0;j<N; ++j)
		{
			//RB_tree[i]->remove(test_num[rand()%N]);
		}
		delete_2 = clock();
		delete_time[3].push_back((double)((double)delete_2 - (double)delete_1) * 1.0 / CLOCKS_PER_SEC * 1000);
		
		/// //////////////////////////////////////////////////
	
		
		search_1 = clock();
		for (int j = 10000 * (i / 2); j < 10000 * (i / 2) + 10000; ++j)
		{
			int temp = rand();
		//	B_tree[i]->search(temp);
		}
		search_2 = clock();
		search_time[4].push_back((double)((double)search_2 - (double)search_1) * 1.0 / CLOCKS_PER_SEC * 1000);

		delete_1 = clock();
		for (int j = 0;j<N; ++j)
		{
		//	B_tree[i]->remove(test_num[rand()%N]);
		}
		delete_2 = clock();
		delete_time[4].push_back((double)((double)delete_2 - (double)delete_1) * 1.0 / CLOCKS_PER_SEC * 1000);
       	
	
		/// ///////////////////////////////////////////////////

		 cout<<"N = "<<N<<endl;
	/*
		 cout << "普通二叉搜索树 insert_time " << insert_time[1][i - 1] << "  search_time = " << search_time[1][i - 1] << "  delete_time  = " << delete_time[1][i - 1] << endl;
		 
		 cout << "AVL平衡搜索树  insert_time " << insert_time[2][i - 1] << "  search_time = " << search_time[2][i - 1] << "  delete_time  = " << delete_time[2][i - 1] << endl;
		 
		 cout << "红黑树         insert_time " << insert_time[3][i - 1] << "  search_time = " << search_time[3][i - 1] << "  delete_time  = " << delete_time[3][i - 1] << endl;
		 
		 cout << "512阶B-树      insert_time " << insert_time[4][i - 1] << "  search_time = " << search_time[4][i - 1] << "  delete_time  = " << delete_time[4][i - 1] << endl;
		 
		 */
		 cout << endl;
		N = 10000 * (i+1);

	}
	int count=50;
	
	ofstream insert_time_bst("insert_time_bst.txt");
	for (int j = 0; j < count; ++j)
	{
		//insert_time_bst << insert_time[1][j]<<endl;
	}
	insert_time_bst.close();

	ofstream search_time_bst("search_time_bst.txt");
	for (int j = 0; j < count; ++j)
	{
		//search_time_bst << search_time[1][j] << endl;
	}
	search_time_bst.close();

	ofstream delete_time_bst("delete_time_bst.txt");
	for (int j = 0; j < count; ++j)
	{
		//delete_time_bst << delete_time[1][j] << endl;
	}
	delete_time_bst.close();

	//////////////////////////////////////////

	ofstream insert_time_avl("insert_time_avl.txt");
	for (int j = 0; j < count; ++j)
	{
		//insert_time_avl << insert_time[2][j] << endl;
	}
	insert_time_avl.close();

	ofstream search_time_avl("search_time_avl.txt");
	for (int j = 0; j < count; ++j)
	{
		//search_time_avl << search_time[2][j] << endl;
	}
	search_time_avl.close();

	ofstream delete_time_avl("delete_time_avl.txt");
	for (int j = 0; j < count; ++j)
	{
	//	delete_time_avl << delete_time[2][j] << endl;
	}
	delete_time_avl.close();
////////////////////////////////////////////////////////

	ofstream insert_time_rb("insert_time_rb.txt");
	for (int j = 0; j < count; ++j)
	{
		//insert_time_rb << insert_time[3][j] << endl;
	}
	insert_time_rb.close();

	ofstream search_time_rb("search_time_rb.txt");
	for (int j = 0; j < count; ++j)
	{
		//search_time_rb << search_time[3][j] << endl;
	}
	search_time_rb.close();

	ofstream delete_time_rb("delete_time_rb.txt");
	for (int j = 0; j < count; ++j)
	{
		//delete_time_rb << delete_time[3][j] << endl;
	}
	delete_time_rb.close();
//////////////////////////////////////////////////

	ofstream insert_time_B("insert_time_B.txt");
	for (int j = 0; j < count; ++j)
	{
		//insert_time_B << insert_time[4][j] << endl;
	}
	insert_time_B.close();

	ofstream search_time_B("search_time_B.txt");
	for (int j = 0; j < count; ++j)
	{
		//search_time_B << search_time[4][j] << endl;
	}
	search_time_B.close();

	ofstream delete_time_B("delete_time_B.txt");
	for (int j = 0; j < count; ++j)
	{
		//delete_time_B << delete_time[4][j] << endl;
	}
	delete_time_B.close();
	///////////////////////////////////////////////////
	return 0;
}
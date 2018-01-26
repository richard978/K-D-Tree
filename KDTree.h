#ifndef __KD_TREE_H
#define __KD_TREE_H

#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<deque>
#include <climits> 
#include <map>
#include <fstream>
using namespace std;

class KDTree {
public:
	struct Node{
		float mid;
		float dimen;
		Node* left;
		Node* right;
		vector<float> value;
		Node(float m, float d, vector<float> v, Node* l=NULL, Node* r=NULL)
			:mid(m), dimen(d), left(l), right(r), value(v){}
		Node(float m, float d, float v[], Node* l=NULL, Node* r=NULL)
			:mid(m), dimen(d), left(l), right(r){
			for(int i=0; i<51; ++i)
				value.push_back(v[i]);
		}
	};
	
	struct fileNode{
		float mid;
		float dimen;
		float value[51];
		int pos;
		fileNode(float m, float d, vector<float> v, int p):mid(m), dimen(d), pos(p){
			for(int i=0; i<51; ++i)
				value[i] = v[i];
		}
		fileNode(){
		}
	};
	
	vector<vector<float> > matrix;
	Node* root;
	float dist;
	stack<Node*> searchPath;
	priority_queue<Node*> PsearchPath;
	int count;
	FILE *filePtr;
	
	KDTree();
	~KDTree();

	int countNode(Node *root);
	
	bool buildTree(
		int n,
		int d,
		float** data);

	void _buildTree(int d, Node* &nodes, vector<vector<float> > list);

	int search(
		int d,
		float* query);

	int _search(vector<float> query, Node* tree, int d);

	bool storeTree(
		const char* index_path);
		
	void _storeTree(const Node *ptr, int pos);

	bool restoreTree(
		const char* index_path);

	int getDimen(vector<vector<float> > v, int n);

	void split(Node* &nodes, int dimen, vector<vector<float> > list, vector<vector<float> > &leftlist, vector<vector<float> > &rightlist, int d);
};

#endif

#include <iostream>

#include "KDTree.h"
//#include "RPTree.h" 
#include "Utility.h"
#include "KDTree.cpp"
//#include "RPTree.cpp" 

#define MNIST

#ifdef MNIST
char dataset[L] = "Mnist";
int n = 60000, d = 50;
int qn = 1000;
#endif

#ifdef Netflix
char dataset[L] = "Netflix";
int n = 17770, d = 50;
int qn = 1000;
#endif

int main() {
	char data_path[L], query_path[L];
	char index_path[L], output_path1[L], output_path2[L];
	float** data = NULL;
	float** query = NULL;

	sprintf(data_path, "%s/src/dataset.txt", dataset);
	sprintf(query_path, "%s/src/query.txt", dataset);
	sprintf(index_path, "%s/index", dataset);
	sprintf(output_path1, "%s/dst/KDTree_answer2.txt", dataset);
	//sprintf(output_path2, "%s/dst/RPTree_answer.txt", dataset);

	if (!read_data(n, d, data, data_path)) {
		return 1;
	}
	
	KDTree kd_Tree1;  //Detect k-d tree
	//kd_Tree1.buildTree(n, d, data);
	//kd_Tree1.storeTree(index_path);
	kd_Tree1.restoreTree(index_path);
	
	if (!read_data(qn, d, query, query_path));
	FILE* fout = fopen(output_path1, "w");
	if (!fout) {
		printf("can't open %s!\n", output_path1);
		return 1;
	}
	
	/*for (int i = 0; i < qn; i++) {
		int index = kd_Tree1.search(d, query[i]);
		cout << index << " ";
	}*/
	
	KDTree kd_Tree2;
	kd_Tree2.restoreTree(index_path);
	clock_t startTime, endTime;
	startTime = clock();
	for (int i = 0; i < qn; i++) {
	int index = kd_Tree2.search(d, query[i]);
	fprintf(fout, "%d\n", index);
	}
	endTime = clock();
	cout<<"Query time: "<<(double)(endTime-startTime)/CLOCKS_PER_SEC<<"s"<<endl;
	fclose(fout);

	/*RPTree rp_Tree1;
	rp_Tree1.buildTree(n, d, data);
	rp_Tree1.storeTree(index_path);

	if (!read_data(qn, d, query, query_path));
	fout = fopen(output_path2, "w");
	if (!fout) {
	printf("can't open %s!\n", output_path2);
	return 1;
	}

	RPTree rp_Tree2;
	rp_Tree2.restoreTree(index_path);
	for (int i = 0; i < qn; i++) {
	int index = rp_Tree2.search(d, query[i]);
	fprintf(fout, "%d\n", index);
	}
	fclose(fout);
	
	for (int i = 0; i < n; i++) {
		if (data[i] != NULL)
			delete[] data[i];
	}

	for (int i = 0; i < qn; i++) {
		if (query[i] != NULL)
			delete[] query[i];
	}*/
	return 0;
}

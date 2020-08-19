#include <iostream>
#include "FSTree.h"
#include "DirNode.h"
#include <string>

using namespace std;

void print(DirNode *node, string dir);

int main(int argc, char const *argv[])
{
	if (argc != 2)
		return 1;
	FSTree tree(argv[1]);
	DirNode node(argv[1]);
	DirNode *root = tree.getRoot();
	string dir = root->getName();


	print(tree.getRoot(), dir);



	return 0;
}

void print(DirNode *node, string dir)
{

	cout << dir << endl;
	if (node->isEmpty())
		return;
	for (int i = 0; i < node->numFiles(); i++) {
		cout << dir << "/" << node->getFile(i) << endl;
	}

	for (int i = 0; i < node->numSubDirs(); i++) {
		print(node->getSubDir(i), (dir + "/" + node->getSubDir(i)->getName()));
	}	

}
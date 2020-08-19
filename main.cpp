#include <iostream>
#include <string>
#include <vector>
#include "Index.h"
#include <algorithm>
#include <functional>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char const *argv[])
{
   	if (argc != 3) {
        cout << "usage: ./gerp input_directory output_directory" << endl;
        return 1;
    }
    else {
        Index i;
        i.init(argv[2]);
        FSTree tree(argv[1]);
        DirNode node(argv[1]);
		DirNode *root = tree.getRoot();
		string dir = root->getName();
        i.traversal(tree.getRoot(), dir);
        i.input_command(); 
    }
    return 0;
}
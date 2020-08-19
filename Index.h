#ifndef INDEX_H
#define INDEX_H
#include <iostream>
#include "FSTree.h"
#include "DirNode.h"
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <ostream>
#include <fstream>

using namespace std;

class Index{
public:
        Index();
        ~Index();
       void input_command();
       void traversal(DirNode *node, string dir);
       void init(string filename);

private:
        struct Word {
            string og_word;
            string lower_case;
            int findex;
            short line;
            size_t hashcode;

            Word(string newOg, string newLower, int newFindex, short newLine, size_t newHashcode)
            :og_word(newOg), lower_case(newLower), findex(newFindex),line(newLine), hashcode(newHashcode) {}
        };

        void index_file(string filename);
        void insert_word(string word, string lower, int f_index, short line_num);
        void insert_word(Word w);
        void lower_query(string query);
        void print_query(Word w);
        void og_query(string query);
        void newFile(string filename);
        string clean_string(string to_clean);
        fstream& go_to_line(fstream& file, unsigned line);
        void expand();
        


        vector<Word>* hashtable;
        int curr;
        int capacity;
        hash<string> hash; // short for hash slinging slasher
        bool end;
        ofstream outfile;
        vector<string> filename_vector;
        int filename_index;


};




#endif
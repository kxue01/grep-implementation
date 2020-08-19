#include <iostream>
#include <string>
#include <vector>
#include "Index.h"
#include <algorithm>
#include <functional>
#include <fstream>
#include <sstream>
#include <ostream>
#include <limits>

using namespace std;

const int init_capacity = 100000;
const double load_factor = 1.1;

// Constructor
Index::Index()
{   
    hashtable = new vector<Word>[init_capacity];
    curr = 0;
    capacity = init_capacity;
    end = false;
    filename_index = 0;
}

// Destructor
Index::~Index()
{
    delete [] hashtable;
}

// Function: traversal
// Input: a dirnode representing the root dir, and a string
// Returns: nothing
// Does: recursivly goes through the file directory and indexes each
//       word within each file. The current path is added to dir
//       after each recursion to ensure that the current path is correct
void Index::traversal(DirNode *node, string dir)
{
    if (node->isEmpty())
        return;
    for (int i = 0; i < node->numFiles(); i++) {
        index_file(dir + "/" + node->getFile(i));
    }
    for (int i = 0; i < node->numSubDirs(); i++) {
        traversal(node->getSubDir(i), (dir + "/" + node->getSubDir(i)->getName()));
    }
}

// Function: index_file
// Input: a filename
// Returns: nothing
// Does: opens the file and indexes every single word in the file
void Index::index_file(string filename)
{
    double temp = curr / capacity;
    if (temp > load_factor) {
        expand();
    }
    ifstream infile;
    infile.open(filename.c_str());
    if (!infile.is_open()){
        cerr << "Could not open file\n";
        return;
    } 
    string line;

    int line_num = 0;
    filename_vector.push_back(filename);
    int findex = filename_index;

    while (getline(infile,line)) {
        stringstream ss(line);
        vector<string> tokens;
        string word;
        line_num++;

        while (ss >> word) {
            string clean = clean_string(word);
            string lower = clean;
            transform(lower.begin(),lower.end(), lower.begin(), ::tolower);
            insert_word(clean, lower, findex, line_num);
        }
    }
    infile.close();
    filename_index++;
}

            
// Function: insert_word
// Input: word:word in original case, lower: word in lower case,
//        f_index: the index of which the filepath is found at
//        line_num: line number of the word
// Returns: nothing
// Does: inserts a word into the hash table
void Index::insert_word(string word, string lower, int f_index, short line_num)
{
    size_t hashed = hash(lower);
    int index = hashed % capacity;
    hashtable[index].emplace_back(word,lower,f_index,line_num, hashed);
    curr++;
}

// Function: insert_word
// Input: a Word struct
// Returns: nothing
// Does: inserts a word into the hash table, used for expand purposes
void Index::insert_word(Word w)
{
    int index = w.hashcode % capacity;
    hashtable[index].push_back(w);
    curr++;
}

// Function: lower_quert
// Input: a string to be queried
// Returns: nothing
// Does: performs case insensitive query by hashing the query word
//       and searches for the word within the hash table
void Index::lower_query(string query)
{
    transform(query.begin(),query.end(), query.begin(), ::tolower);
    size_t hashed = hash(query);
    int index = hashed % capacity;
    bool found = false;
    for (unsigned i = 0; i < hashtable[index].size(); i++) {
        if (hashtable[index].at(i).lower_case == query) {
            found = true;
            if (i == 0)
                print_query(hashtable[index].at(i));
            else if (!(hashtable[index].at(i - 1).lower_case == query && hashtable[index].at(i - 1).line == hashtable[index].at(i).line))
                print_query(hashtable[index].at(i));
        }
    }
    if (found == false) {
        outfile << "query not found" << endl;
    }
}

// Function: og_quert
// Input: a string to be queried
// Returns: nothing
// Does: performs case sensitive query by hashing the query word
//       and searches for the word within the hash table
void Index::og_query(string query)
{
    string lower = query;
    transform(lower.begin(),lower.end(), lower.begin(), ::tolower);
    size_t hashed = hash(lower);
    int index = hashed % capacity;
    bool found = false;
    for (unsigned i = 0; i < hashtable[index].size(); i++) {
        if (hashtable[index].at(i).og_word == query) {
            found = true;
            if (i == 0)
                print_query(hashtable[index].at(i));
            else if (!(hashtable[index].at(i - 1).og_word == query && hashtable[index].at(i - 1).line == hashtable[index].at(i).line))
                print_query(hashtable[index].at(i));
        }
    }
    if (found == false) {
        outfile << "query not found" << endl;
    }

}

// Function: print_query
// Input: a Word struct, w that is to be printed
// Returns: nothing
// Does: prints a found word according to spec
void Index::print_query(Word w)
{   
    string path = filename_vector.at(w.findex);
    ifstream infile;
    infile.open(path.c_str());
    if (!infile.is_open()){
        cerr << "Could not open file\n";
        return;
    } 
    string buffer;
    string line_wanted;
    for (int i = 1; i < w.line; i++) {
        getline(infile,buffer);
        }
    getline(infile,line_wanted);
    
    outfile << path << ":" << w.line << ": " << line_wanted <<endl;
    infile.close();
}

// Function: input_command
// Input: nothing
// Returns: nothing
// Does: takes in command from the user and calls functions 
//       that performs user command


void Index::input_command()
{
    while (end == false) {
        string line;
        cout << "Query? "; 
        getline(cin, line);
        cout << endl;
        string buffer;
        stringstream ss(line);
        vector<string> tokens;

        while (ss >> buffer) 
            tokens.push_back(buffer);
        if (tokens[0] == "@i" or tokens[0] == "@insensitive") {
            for (unsigned i = 1; i < tokens.size(); i++) {
                lower_query(clean_string(tokens[i]));
            }
        }
        else if (tokens[0] == "@q" or tokens[0] == "@quit") {
            outfile.close();
            cout << "Goodbye! Thank you and have a niceday" << endl;
            end = true;
        }
        else if (tokens[0] == "@f")
        {
            newFile(tokens[1]);
        }
        else {
            for (unsigned i = 0; i < tokens.size(); i++) {
                og_query(clean_string(tokens[i]));
            }
        }
    }

}

// Function: newFile
// Input: a string filename
// Returns: nothing
// Does: called when a new output file is used
//       closes the current file and opens a new one
void Index::newFile(string filename)
{
    outfile.close();
    outfile.open(filename.c_str());
}

// Function: init
// Input: a string filename
// Returns: nothing
// Does: used at initialization
//       opens a new output file
void Index::init(string filename)
{
    outfile.open(filename.c_str());
}

// Function: expand
// Input: nothing
// Returns: nothing
// Does: expands the array when the ratio of curr/capacity exceeds loadfactor

void Index::expand()
{
    curr = 0;
    int old_capa = capacity;
    capacity = capacity * 2.5;
    vector<Word>* temp;
    temp = new vector<Word>[capacity];
    vector<Word>* old = hashtable;
    hashtable = temp;
    for (int i = 0; i < old_capa; i++) {
        for (unsigned j = 0; j < old[i].size() ; j++) {
            insert_word(old[i].at(j));
        }
    }
    delete [] old;

}

// Function: clean_string
// Input: a string to be cleaned
// Returns: string that is cleaned
// Does: strips all leading and trailing non-alphanumeric characters 
string Index::clean_string(string to_clean)
{
    int j = 0;
    while (!isalnum(to_clean[j])) {
        j++;
    }
    int k = (to_clean.length() - 1);
    while(!isalnum(to_clean[k])) {
        k--;
    } 
    string final = "";
    for(int i = j; i < (k + 1); i++){
        final += to_clean[i];
    }
    return final;
}

// Function: go_to_line
// Input: pointer to a file
// Returns: pointer to a file, with first line being the wanted line
// Does: ignores all lines until the line wanted, then returns the file
//       pointer;
fstream& Index::go_to_line(fstream& file, unsigned line)
{
    file.seekg(ios::beg);
    for (unsigned i = 0; i < line - 1; i++){
        file.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return file;
}
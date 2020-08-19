#include <string>
#include <iostream>

using namespace std;

int main()
{
	string input = "";
	cin >> input;
	int j = 0;
	while (!isalnum(input[j])) {
		j++;
	}

	int k = (input.length() - 1);
	while(!isalnum(input[k])) {
		k--;
	} 

	string final = "";
	for(int i = j; i < (k + 1); i++){
		final += input[i];
	}


	string str = final;
	cout << final << endl;
	return 0;

}
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
using namespace std;

int main() {
	int numofgroup;
	std::cin >> numofgroup;
	vector < vector<int>>  array_int(numofgroup);
	for (int i = 0; i < numofgroup; ++i) {
		int sizeofarray;
		cin >> sizeofarray;
		string temp1;
		getline(cin, temp1); // �������ֺ�Ļ��з�
		int temp;
		while (sizeofarray--) {
			cin >> temp;
			array_int[i].push_back(temp);
		}
		getline(cin, temp1); // ������ǰ���������Ļ��з�
	}
	std::cout << array_int[0][1] << std::endl;
	return 0;

}

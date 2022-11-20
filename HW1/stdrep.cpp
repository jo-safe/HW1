#include "stdrep.h"

List<string> splitString(string source, string separator) {
	List<string> result(true);
	string tempS = "";
	string tempSS = "";
	int j = 0;
	bool flag = false;
	for (int i = 0; i < source.length(); i++) {
		if (j == separator.length()) {
			result.add(tempS);
			j = 0;
			tempS = source[i];
			tempSS = "";
			flag = true;
		}
		else
			if (source[i] == separator[j]) {
				tempSS += source[i];
				j++;
			}
			else {
				j = 0;
				tempS += tempSS + source[i];
				tempSS = "";
			}
	}
	if (tempS != "")
		result.add(tempS);
	return result;
}

string getSubstring(string line, int index1, int index2) {
	string result = "";
	if (index2 == -1) index2 = line.length();
	for (int i = 0; i < index2; i++)
		if (i >= index1)
			result += line[i];

	return result;
}

int getIntLen(int number) {
	if (number == 0) return 1;
	int iter = 0;
	while (number != 0) {
		number /= 10;
		iter++;
	}
	return iter;
}

string multiplicateString(string line, int n) {
	string result = "";
	for (int i = 0; i < n; i++) {
		result += line;
	}
	return result;
}


#include "main.h"



List<Supply> readData(string path) {
	List<Supply> result;
	fstream file(path, ios_base::in);
	string temp;
	while (getline(file, temp))
		result.add(Supply(temp));
	file.close();

	return result;
}

void saveData(string path, List<Supply> data) {
	fstream file(path, ios_base::out);
	for (int i = 0; i < data.getLength(); i++)
		file << data[i].getAsString();
}

void operateRequest(int param, int data)
{
}

int main() {

	return 0;
}
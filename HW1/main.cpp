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

void operateRequest(int param, List<Supply> &data) {
	switch (param) {
	case M_OPEN_FILE:
	{
		string path;
		cout << "Type path to the file you want to open: ";
		cin >> path;
		data = readData(path);
		cout << "Data is read successfully\n";
		return;
	} break;
	case M_SAVE_FILE:
	{
		string path;
		cout << "Type the path you want to save data to: ";
		cin >> path;
		saveData(path, data);
		cout << "Data is saved successfully.\n";
	} break;
	case M_SHOW_DATA:
	{
		char maxTagLen = 3;
		char maxProducerLen = 8;
		char maxModelLen = 5;
		char maxTypeLen = 4;
		char maxPriceLen = 5;

		for (int i = 0; i < data.getLength(); i++) {
			maxTagLen = maxTagLen < to_string(data[i].getTag()).length() ?
				to_string(data[i].getTag()).length() : maxTagLen;
			maxProducerLen = maxProducerLen < data[i].getProducer().length() ?
				data[i].getProducer().length() : maxProducerLen;
			maxModelLen = maxModelLen < data[i].getModel().length() ?
				data[i].getModel().length() : maxModelLen;
			maxTypeLen = maxTypeLen < data[i].getType().length() ?
				data[i].getType().length() : maxTypeLen;
			maxPriceLen = maxPriceLen < to_string(data[i].getPrice()).length() ?
				to_string(data[i].getPrice()).length() : maxPriceLen;
		}

		maxTagLen++;
		maxProducerLen++;
		maxModelLen++;
		maxTypeLen++;
		maxPriceLen++;

		for (int i = 0; i < data.getLength(); i++)
			cout << "| " + to_string(data[i].getTag()) + MpS(" ", maxTagLen - to_string(data[i].getTag()).length()) +
				"| " + data[i].getProducer() + MpS(" ", maxProducerLen - data[i].getProducer().length()) +
				"| " + data[i].getModel() + MpS(" ", maxModelLen - data[i].getModel().length()) +
				"| " + (data[i].isInStock() ? "In stock     " : "Not in stock ") +
				"| " + data[i].getType() + MpS(" ", maxTypeLen - data[i].getType().length()) +
				"| " + to_string(data[i].getPrice()) + MpS(" ", maxPriceLen - to_string(data[i].getPrice()).length()) + "\n";
	} break;
	}
}

int main() {

	return 0;
}
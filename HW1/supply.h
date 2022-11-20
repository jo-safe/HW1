#pragma once
#include "header.h"

class Supply {
private:
	unsigned int tag_;
	string producer_;
	string model_;
	bool existance_;
	unsigned char type_;
	double price_;
public:
	Supply(unsigned int, string, string, bool, unsigned char, float);
	Supply(string);
	Supply();

	string getAsString();
	bool operator==(Supply& left);

	void setTag(unsigned int tag) { tag_ = tag; };
	void setExistance(bool existance) { existance_ = existance; }
	void setPrice(float price) { price_ = price; };

	unsigned int getTag() { return tag_; }
	string getProducer() { return producer_; }
	string getModel() { return model_; }
	bool isExist() { return existance_; }
	unsigned char getType() { return type_; }
	double getPrice() { return price_; }
};
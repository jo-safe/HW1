#pragma once
#include "header.h"

class Supply {
private:
	unsigned int tag_;
	string producer_;
	string model_;
	bool avalability_;
	string type_;
	double price_;
public:
	Supply(unsigned int, string, string, bool, string, float);
	Supply(string);
	Supply();

	string getAsString();
	bool operator==(Supply& left);

	void setTag(unsigned int tag) { tag_ = tag; };
	void setAvalability(bool isInStock) { avalability_ = isInStock; }
	void setPrice(float price) { price_ = price; };

	unsigned int getTag() { return tag_; }
	string getProducer() { return producer_; }
	string getModel() { return model_; }
	bool isInStock() { return avalability_; }
	string getType() { return type_; }
	double getPrice() { return price_; }
};
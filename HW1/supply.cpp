#include "supply.h"

Supply::Supply(unsigned int tag, string producer, string model, bool avalability, string type, float price)
{
	tag_ = tag;
	producer_ = producer;
	model_ = model;
	avalability_ = avalability;
	type_ = type;
	price_ = price;
}

Supply::Supply(string line)
{
	List<string> line_ = splitString(line, ";");
	tag_ = stoi(line_[0]);
	producer_ = line_[1];
	model_ = line_[2];
	avalability_ = stoi(line_[3]);
	type_ = line[4];
	price_ = atof(line_[5].c_str());
}

Supply::Supply()
{
	tag_ = -1;
	producer_ = "";
	model_ = "";
	avalability_ = false;
	type_ = '\0';
	price_ = 0.;
}

string Supply::getAsString()
{
	string temp;
	sprintf(&temp[0], "%d;%s;%s;%d;%s;%f;", tag_, producer_.c_str(), model_.c_str(), (int)avalability_, type_.c_str(), price_);
	return temp;
}

bool Supply::operator==(Supply& left)
{
	return tag_ == left.tag_ && 
		producer_ == left.producer_ && 
		model_ == left.model_ && 
		avalability_ == left.avalability_ &&
		type_ == left.type_ && 
		price_ == left.price_;
}


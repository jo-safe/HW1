#pragma once
#include <stdexcept>
#include <cstdarg>
#include <string>
using namespace std;

// �����, �������� ���������� �� �������� ������: 
//		- �������� ���� Type;
//      - ����� ���������� ��������;
//		- ����� ��������������� ��������.
template<class Type>
class ListItem {
public:
	Type value_;				// ��������.
	ListItem<Type>* next_;		// ��������� �� ��������� ������� (�� ��������� ����� nullptr).
	ListItem<Type>* previous_;	// ��������� �� �������������� ������� (�� ��������� ����� nullptr).

	// �����������, ������������ ��� ���� ������� ������ (���� �������� �� ���������� � �����������, ��� ���������������� ���������� �� ���������).
	ListItem<Type>(Type value = Type(), ListItem<Type>* previous = nullptr, ListItem<Type>* next = nullptr) {
		value_ = value;
		previous_ = previous;
		next_ = next;
	}
};


// �����, ����������� ������ � ���������� ������ ���� Type.
// ������ � ���� ������ ������� � ���������� ��������� ���� ListItem, 
// ������� � ���� ������� ������ ������ � ������ �������� ������ � ���������� ��������� � ������.
// ��������� ��� ������������� �������� ������ �� �������.
template<class Type>
class List {
private:
	int nItems_;		// ���������� ��������� � ������.
	ListItem<Type>* first_;	// ��������� �� ������ ������� ������.
	ListItem<Type>* last_;	// ��������� �� ��������� ������� ������.
	bool repitability_;		// "�������������". ����������, ����� �� ����������� ��� ������������ ��������.

public:
	// �����������, ��������� ������ ������.
	List<Type>(bool repitability = false) {
		nItems_ = 0;
		first_ = nullptr;
		last_ = nullptr;
		repitability_ = repitability;
	}

	// �����������, ����������� �������� �������� ������ � �� ����������.
	List<Type>(int n, Type item, ...) {
		nItems_ = 0;
		va_list arglist;
		va_start(arglist, n);
		for (int i = 0; i < n; i++)
			add(va_arg(arglist, Type));
		va_end(arglist);
	}

	// �����������, ����������� ��������� �� ������ ������� ������� ��������� � �� ����������.
	List<Type>(int n, Type& items) {
		nItems_ = 0;
		for (int i = 0; i < n; i++)
			add(items[i]);
	}

	// �����������, ����������� ������ � ��������� �������� �������.
	List<Type>(Type* first, Type* last) {
		nItems_ = 0;
		while (first != last + 1) {
			add(*first++);
		}
	}

	// �������� ������� � �������� ������ �� �������.
	Type& operator[](int index) {
		ListItem<Type>* result = first_;	// ������� �������� �� ������� �������� �� �������� � �������� index
		for (int i = 1; i <= index; i++) {
			if (result == nullptr)
				throw out_of_range::out_of_range("Index is out of list range.");
			result = result->next_;
		}
		return result->value_;				// � ���������� ������ ��� ���������� ������ �� ��������� �������� ������.
	}
	// ������� ���������� � ������ �������� �� ��������� ���� Type.
	// ���������� ������ ������������ ��������.
	// ���� ������� ��� ����������, � ������ �� �������� �����������, ������������ ������ ������������� ��������.
	int add(Type value = Type()) {
		if (isExist(value) && !repitability_) {
			ListItem<Type>* pointer = first_;
			for (int i = 0; pointer != nullptr; i++) {
				if (pointer->value_ == value)
					return i;
				pointer = pointer->next_;
			}
		}
		// ������� ���������� ������� ������� �� ���������� ��������� � ������.
		if (nItems_ == 0) {
			// ���� ����������� ������� �������� ������ ��������� � ������, �� ��������� �� ������ � ��������� �������
			// ����� ������� ����� ������ � ���� �� �������.
			first_ = new ListItem<Type>(value);
			last_ = first_;
		}
		else {
			// ����� ����������� ������� ������������ � ����� ������ � ���������������� ���������������� ����������.
			last_->next_ = new ListItem<Type>(value);
			last_->next_->previous_ = last_;
			last_ = last_->next_;
		}

		nItems_++;	// ��� ��� �����, ���������� ��������� � ������ �� ���������� ������� �������������.
		return nItems_ - 1;
	}

	// ���������, ���������� �� � ������ ������� �� ��������� item.
	bool isExist(Type item) {
		if (nItems_ == 1)
			if (first_->value_ == item)
				return true;
			else
				return false;
		if (isEmpty())
			return false;
		ListItem<Type>* _pointer = first_;
		do {
			if (item == _pointer->value_)
				return true;
			_pointer = _pointer->next_;
		} while (_pointer != nullptr);
		return false;
	}
	// ��������� ������ �� �������.
	bool isEmpty() { return nItems_ == 0; }

	// ������ ��� �������� ������ � ��������� index_1 � index_2 �������
	// (std::swap() � ���� ������� �� �����������).
	void swap(int index_1, int index_2) {
		Type value_1 = operator[](index_1);
		Type value_2 = operator[](index_2);
		operator[](index_1).value = value_2;
		operator[](index_2).value = value_1;
	}

	// ������� ������� �� ������ �� ������� � ����������� ������.
	void removeI(int index) {
		ListItem<Type>* item = first_;
		for (int i = 1; i <= index; i++) {
			item = item->next_;
		}
		ListItem<Type>* next = item->next_;
		ListItem<Type>* previous = item->previous_;
		delete item;
		next->previous_ = previous;
		previous->next_ = next;
		nItems_--;
	}

	// ������� �� ������ ��� �������� �� ��������� value.
	void remove(Type value) {
		ListItem<Type>* pointer = first_;
		while (pointer != last_->next_) {
			if (pointer->value_ == value) {
				ListItem<Type>* _next = pointer->next_;
				ListItem<Type>* _previous = pointer->previous_;
				delete pointer;
				if (_next == nullptr) {
					last_ = _previous;
					last_->next_ = nullptr;
				}
				else if (_previous == nullptr) {
					first_ = _next;
					first_->previous_ = nullptr;
				}
				else {
					_next->previous_ = _previous;
					_previous->next_ = _next;
				}
				nItems_--;
				if (!repitability_)
					return;
			}
			pointer = pointer->next_;
		}
		throw invalid_argument::invalid_argument("Item with such value is not existed.");
	}

	// ����������� �������� ��������� ������ � ������������ ������ ���� Type.
	Type* getAsArray() {
		Type* result = new Type[this->getLength()];
		for (int i = 0; i < this->getLength(); i++)
			result[i] = operator[](i);
		return result;
	}

	// ��������� ���� ���������� ��������, ������ �������������.
	void removeDoubles() {
		ListItem<Type>* pointer1, pointer2;
		for (pointer1; pointer1 != nullptr; pointer1 = pointer1->next_)
			for (pointer2 = pointer1->next_; pointer2 != nullptr; pointer2 = pointer2->next_)
				if (pointer1->value_ == pointer2->value_) {
					ListItem<Type>* next = pointer2->next_;
					ListItem<Type>* previous = pointer2->previous_;
					delete pointer2;
					next->previous_ = previous;
					previous->next_ = next;
					pointer2 = next;
				}
	}

	int getLength() { return nItems_; }
	bool isRepitable() { return repitability_; }


	// ���������� ������ ������� � ������, �������� �������, ������� (defPointer) ���������� ��������� �������� (requiredValue).
	template<class Val>
	static Type find(List<Type>* list, Val(*defPointer)(Type), Val requiredValue) {
		for (ListItem<Type>* pointer = list->first_; pointer != nullptr; pointer = pointer->next_)
			if ((*defPointer)(pointer->value_) == requiredValue)
				return pointer->value_;
		return Type();			// ���� �� ������� �� ������ ��������, ������������ �������� �� ���������.
	}

	// ���������� ������ ���������, �������� ������ �� �������, ������� (defPointer) ���������� ��������� �������� (requiredValue).
	template<class Val>
	static List<Type> findAll(List<Type>* list, Val(*defPointer)(Type), Val requiredValue) {
		List<Type> result;
		for (ListItem<Type>* pointer = list->first_; pointer != nullptr; pointer = pointer->next_)
			if ((*defPointer)(pointer->value_) == requiredValue)
				result.add(pointer->value_);
		return result;			// ���� �������� �� �������, ������������ ������ ������.
	}

	// ���������, ���������� �� � ������ �������, ��������������� ��������� defPointer(item) = requiredValue.
	template<class Val>
	static bool isExist(List<Type>* list, Val(*defPointer)(Type), Val requiredValue) {
		List<Type> result;
		for (ListItem<Type>* pointer = list->first_; pointer != nullptr; pointer = pointer->next_)
			if ((*defPointer)(pointer->value_) == requiredValue)
				return true;
		return false;
	}
};
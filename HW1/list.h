#pragma once
#include <stdexcept>
#include <cstdarg>
#include <string>
using namespace std;

// Класс, хранящий информацию об элементе списка: 
//		- значение типа Type;
//      - адрес следующего элемента;
//		- адрес предшествующего элемента.
template<class Type>
class ListItem {
public:
	Type value_;				// Значение.
	ListItem<Type>* next_;		// Указатель на следующий элемент (по умолчанию равен nullptr).
	ListItem<Type>* previous_;	// Указатель на предшествующий элемент (по умолчанию равен nullptr).

	// Конструктор, определяющий три поля объекта класса (если значения не передаются в конструктор, они инициализируются значениями по умолчанию).
	ListItem<Type>(Type value = Type(), ListItem<Type>* previous = nullptr, ListItem<Type>* next = nullptr) {
		value_ = value;
		previous_ = previous;
		next_ = next;
	}
};


// Класс, реализующий работу с элементами списка типа Type.
// Хранит в себе адреса первого и последнего элементов типа ListItem, 
// которые в свою очередь хранят данные о каждом элементе списка и количество элементов в списке.
// Требуется для автоматизации процесса работы со списком.
template<class Type>
class List {
private:
	int nItems_;		// Количество элементов в списке.
	ListItem<Type>* first_;	// Указатель на первый элемент списка.
	ListItem<Type>* last_;	// Указатель на последний элемент списка.
	bool repitability_;		// "Повторяемость". Определяет, будут ли добавляться уже существующие элементы.

public:
	// Конструктор, создающий пустой список.
	List<Type>(bool repitability = false) {
		nItems_ = 0;
		first_ = nullptr;
		last_ = nullptr;
		repitability_ = repitability;
	}

	// Конструктор, принимающий элементы будущего списка и их количество.
	List<Type>(int n, Type item, ...) {
		nItems_ = 0;
		va_list arglist;
		va_start(arglist, n);
		for (int i = 0; i < n; i++)
			add(va_arg(arglist, Type));
		va_end(arglist);
	}

	// Конструктор, принимающий указатель на первый элемент массива элементов и их количество.
	List<Type>(int n, Type& items) {
		nItems_ = 0;
		for (int i = 0; i < n; i++)
			add(items[i]);
	}

	// Конструктор, принимающий первый и последний элементы массива.
	List<Type>(Type* first, Type* last) {
		nItems_ = 0;
		while (first != last + 1) {
			add(*first++);
		}
	}

	// Оператор доступа к элементу списка по индексу.
	Type& operator[](int index) {
		ListItem<Type>* result = first_;	// Функция проходит от первого элемента до элемента с индексом index
		for (int i = 1; i <= index; i++) {
			if (result == nullptr)
				throw out_of_range::out_of_range("Index is out of list range.");
			result = result->next_;
		}
		return result->value_;				// и возвращает ссылку для безопасной работы со значением элемента списка.
	}
	// Функция добавления в список элемента со значением типа Type.
	// Возвращает индекс добавленного элемента.
	// Если элемент уже существует, а список не является повторяемым, возвращается индекс существующего элемента.
	int add(Type value = Type()) {
		if (isExist(value) && !repitability_) {
			ListItem<Type>* pointer = first_;
			for (int i = 0; pointer != nullptr; i++) {
				if (pointer->value_ == value)
					return i;
				pointer = pointer->next_;
			}
		}
		// Процесс выполнения функции зависит от количества элементов в списке.
		if (nItems_ == 0) {
			// Если добавляемый элемент является первым элементом в списке, то указатели на первый и последний элемент
			// будут хранить адрес одного и того же объекта.
			first_ = new ListItem<Type>(value);
			last_ = first_;
		}
		else {
			// Иначе добавляемый элемент встраивается в конец списка с соответствующими преобразованиями указателей.
			last_->next_ = new ListItem<Type>(value);
			last_->next_->previous_ = last_;
			last_ = last_->next_;
		}

		nItems_++;	// Так или иначе, количество элементов в списке по завершению функции увеличивается.
		return nItems_ - 1;
	}

	// Проверяет, содержится ли в списке элемент со значением item.
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
	// Проверяет список на пустоту.
	bool isEmpty() { return nItems_ == 0; }

	// Меняет два элемента списка с индексами index_1 и index_2 местами
	// (std::swap() с этой работой не справляется).
	void swap(int index_1, int index_2) {
		Type value_1 = operator[](index_1);
		Type value_2 = operator[](index_2);
		operator[](index_1).value = value_2;
		operator[](index_2).value = value_1;
	}

	// Удаляет элемент из списка по индексу и освобождает память.
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

	// Удаляет из списка все элементы со значением value.
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

	// Преобразует значения элементов списка в динамический массив типа Type.
	Type* getAsArray() {
		Type* result = new Type[this->getLength()];
		for (int i = 0; i < this->getLength(); i++)
			result[i] = operator[](i);
		return result;
	}

	// Оставляет лишь уникальные значения, удаляя дублирующиеся.
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


	// Возвращает первый элемент в списке, принимая который, функция (defPointer) возвращает ожидаемое значение (requiredValue).
	template<class Val>
	static Type find(List<Type>* list, Val(*defPointer)(Type), Val requiredValue) {
		for (ListItem<Type>* pointer = list->first_; pointer != nullptr; pointer = pointer->next_)
			if ((*defPointer)(pointer->value_) == requiredValue)
				return pointer->value_;
		return Type();			// Если не найдено ни одного элемента, возвращается значение по умолчанию.
	}

	// Возвращает список элементов, принимая каждый из которых, функция (defPointer) возвращает ожидаемое значение (requiredValue).
	template<class Val>
	static List<Type> findAll(List<Type>* list, Val(*defPointer)(Type), Val requiredValue) {
		List<Type> result;
		for (ListItem<Type>* pointer = list->first_; pointer != nullptr; pointer = pointer->next_)
			if ((*defPointer)(pointer->value_) == requiredValue)
				result.add(pointer->value_);
		return result;			// Если элементы не найдены, возвращается пустой список.
	}

	// Проверяет, существует ли в списке элемент, удовлетворяющий равенству defPointer(item) = requiredValue.
	template<class Val>
	static bool isExist(List<Type>* list, Val(*defPointer)(Type), Val requiredValue) {
		List<Type> result;
		for (ListItem<Type>* pointer = list->first_; pointer != nullptr; pointer = pointer->next_)
			if ((*defPointer)(pointer->value_) == requiredValue)
				return true;
		return false;
	}
};
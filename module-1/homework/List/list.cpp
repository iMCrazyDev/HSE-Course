#include "list.h"
#include <iostream>

void task::list::__init__()
{
	head = nullptr;
	tail = head;
	_size = 0;
}

task::list::list() {
	__init__();
}

task::list::list(const list& other) : list() {
	operator=(other);
}

task::list::list(size_t count, const int& value) : list() {
	_size = count;
	while (count--) {
		push_back(value);
	}
}

task::list::~list() {
	clear();
}

task::list& task::list::operator=(const list& other) {
	clear();
	
	task::list::Node* it = other.head;
	while (it != other.tail) {
		push_back(it->value);
		it = it->next;
	}

	return *this;
}

int& task::list::front() {
	int nul = 0;
	return head == nullptr ? nul : head->value;
}

const int& task::list::front() const {
	int nul = 0;
	return head == nullptr ? nul : head->value;
}

int& task::list::back() {
	int nul = 0;
	return tail == nullptr ? nul : tail->prev->value;
}

const int& task::list::back() const {
	int nul = 0;
	return tail == nullptr ? nul : tail->prev->value;
}

bool task::list::empty() const {
	return _size == 0;
}

size_t task::list::size() const {
	return _size;
}

void task::list::clear() {
	Node* current_node = head;

	while (current_node != nullptr) {
 		Node* next = current_node->next;
		delete current_node;
		current_node = next;
	}

	_size = 0;
	head = nullptr;
	tail = nullptr;
}

void task::list::push_back(const int& value) {
	_size++;

	if (head == nullptr) { 
		__push_first__(value);
		return; 
	}

	tail->value = value;
	tail = new Node(tail,nullptr,0);
	tail->prev->next = tail;
}

void task::list::__push_first__(const int& value) {
	head = new Node();
	head->value = value;
	tail = new Node(head, nullptr, 0);
	head->next = tail;
}

void task::list::push_front(const int& value) {
	_size++;

	if (head == nullptr) {
		__push_first__(value);
		return;
	}

	head = new Node(nullptr,head,value);
	head->next->prev = head;
}

void task::list::pop_back() {
	if (tail == nullptr) 
		return;

	__remove_node_(tail->prev);
}

void task::list::pop_front() {
	if (head == nullptr) return;
	__remove_node_(head);
}

void task::list::resize(size_t count) {
	while (_size > count) pop_back();
	while (_size < count) push_back(0);
}

void task::list::swap(list& other) {
	std::swap(other.head, head);
	std::swap(other.tail, tail);
	std::swap(other._size, _size);
}

void task::list::__remove_node_(Node* nd)
{
	_size--;
	if (nd->prev != nullptr)
	{
		nd->prev->next = nd->next;
	}
	else head = nd->next;
	if (head == tail) {
		delete head; head = nullptr; tail = nullptr;
	}
	else nd->next->prev = nd->prev;

	delete nd;
}

void task::list::remove(const int& _value) {
	if (head == nullptr) {
		return;
	}
	
	int value = _value;
	Node* node = head;
	while (node != tail)
	{
		if (node->value == value) {
			Node* next = node->next;
			__remove_node_(node);
			node = next;
			if (!_size) break;
		}
		else node = node->next;
	}
}

void task::list::unique() {
	if (head == nullptr) return;
	sort();

	Node* node = head->next;
	while (node != tail) {
		if (node->value == node->prev->value)
		{
			Node* next = node->next;
			__remove_node_(node);
			node = next;
		}
		else node = node->next;
	}
}

void task::list::sort() {
	if (head == nullptr) return;

	size_t changes;
	Node* node;
	do
	{
		changes = 0;
		node = head;
		while (node->next != tail) {
			if (node->value > node->next->value)
			{
				std::swap(node->value, node->next->value);
				changes++;
			}
			node = node->next;
		}
	} while (changes > 0);
}
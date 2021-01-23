#include <iostream>

using namespace std;

template<typename T>
class SharedPtr {
	T* address;
	size_t* count;
public:
	SharedPtr() :address(nullptr), count(nullptr) {}
	SharedPtr(T* address) :address(address), count(new size_t(1)) {
	}
	SharedPtr(const SharedPtr& other) :address(other.address), count(other.count) {
		(*count)++;
	}
	SharedPtr& operator=(T* object) {
		if (count != nullptr) {
			(*count)--;
			if (count == 0) {
				delete address;
				delete count;
			}
		}
		count = new size_t(1);
		address = object;
		return *this;
	}
	SharedPtr& operator=(const SharedPtr& other) {
		if (count != nullptr) {
			(*count)--;
			if (*count == 0) {
				delete address;
				delete count;
			}
		}
		count = other.count;
		address = other.address;
		(*count)++;
		return *this;
	}
	~SharedPtr() {
		if (count != nullptr) {
			(*count)--;
			if (*count == 0) {
				delete address;
				delete count;
			}
		}
	}

	T* get()const {
		return address;
	}
	T* operator->()const {
		return address;
	}
	T& operator*()const {
		return *address;
	}
};



class Student {
public:
	string name;
	int age;
	Student(const string& name, const int& age) {
		this->name = name;
		this->age = age;
	}

	void show() {
		cout << " Name: " << name;
		cout << " Age: " << age;
	}
	friend ostream& operator<<(ostream& out, Student& other);
};

ostream& operator<<(ostream& out, Student& other)
{
	out << other.name << " ";
	out << other.age;

	return out;
}




void main() {

	SharedPtr<Student>s1(new Student("John", 21));
	SharedPtr<Student>s2 = s1;
	cout << "s1: " << (*s1).name << " " << (*s1).age << endl;
	cout << "s1 address: " << s1.get() << endl;
	cout << "s2: " << (*s2).name << " " << (*s2).age << endl;
	cout << "s2 address: " << s2.get() << endl << endl;

	shared_ptr<Student>sh(new Student("Johnatan", 21));
	shared_ptr<Student>sh2(new Student("Jack", 41));
	shared_ptr<Student>sh3 = sh2;
	cout << "shared_ptr<Student>sh: " << *sh << endl;
	cout << "shared_ptr<Student>sh address: " << sh << endl;
	cout << "shared_ptr<Student>sh2: " << *sh2 << endl;
	cout << "shared_ptr<Student>sh2 address: " << sh2 << endl;
	cout << "====================================" << endl;
	cout << "shared_ptr<Student>sh3 = sh2" << endl;
	cout << "====================================" << endl;
	cout << "shared_ptr<Student>sh3: " << *sh3 << endl;
	cout << "shared_ptr<Student>sh3 address: " << sh3 << endl << endl;

	unique_ptr<int>u(new int(21));
	unique_ptr<int>u2(new int(51));
	cout << "unique_ptr<int>u: " << *u << endl;
	cout << "unique_ptr<int>u address: " << u << endl;
	cout << "unique_ptr<int>u2: " << *u2 << endl;
	cout << "unique_ptr<int>u2 address: " << u2 << endl << endl;

	unique_ptr<Student>u1(new Student("Jane", 21));
	cout << "unique_ptr<Student>u1: " << *u1 << endl;
	cout << "unique_ptr<Student>u1 address: " << u1 << endl;



}
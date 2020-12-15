#include<iostream>
#include<memory>

class MyClass
{
public:
	int x;
	MyClass(int x_);
	~MyClass();

private:

};

MyClass::MyClass(int x_) : x(x_)
{
	std::cout << "Object MyClass created\n";
}
MyClass::~MyClass()
{
	std::cout << "Object MyClass destroyed\n";
}

void delete_MyClass(MyClass* obj)
{
	std::cout << "invoke function delete_MyClass\n";
	delete obj;
}

//class AnotherClass
//{
//public:
//	AnotherClass(std::shared_ptr<MyClass> obj_);
//	~AnotherClass();
//	void function() { std::cout << "function from AnotherClass\n"; }
//
//private:
//	std::shared_ptr<MyClass> obj;
//};
//
//AnotherClass::AnotherClass(std::shared_ptr<MyClass> obj_) : obj(obj_)
//{
//	std::cout << "Object AnotherClass created\n";
//}
//AnotherClass::~AnotherClass()
//{
//	std::cout << "Object AnotherClass created\n";
//}
//
//AnotherClass anotherFunction()
//{
//	return AnotherClass(std::make_shared<MyClass>());
//}

int main()
{
	//std::shared_ptr<MyClass> ptr;
	//ptr = std::make_shared<MyClass>();//same as <new> but for shared_ptr
	//std::cout << ptr << std::endl;
	//ptr = nullptr;
	//std::cout << ptr << std::endl;

	//anotherFunction().function();

	int i = 5;
	std::shared_ptr<int>  ptr, ptr1;
	ptr = std::make_shared<int>(i);
	ptr1 = ptr;
	std::cout << "ptr.use_count()= " << ptr.use_count() << std::endl;
	std::cout << "ptr1.use_count()= " << ptr1.use_count() << std::endl;
	std::shared_ptr< MyClass> a;
	a = std::make_shared<MyClass>(i);
	std::shared_ptr< int> b(a, &a->x);
	std::cout << "a.use_count()= " << a.use_count() << " " << a->x << std::endl;
	std::cout << "b.use_count()= " << b.use_count() << " " << *b << std::endl;

	a = nullptr;
	b = nullptr;
	std::shared_ptr<MyClass> c(new MyClass(i), delete_MyClass);
	std::cout << "c.use_count()= " << c.use_count() << " " << c->x << std::endl;
	c = nullptr;

	std::shared_ptr<int> intArray(new int[10], std::default_delete<int[]>(), std::allocator<int[]>());


	return 0;
}
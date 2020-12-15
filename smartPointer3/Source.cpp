#include<iostream>
#include<memory>
struct B;

struct A
{
	std::weak_ptr<B> b;
	A() { std::cout << "Invoke constructor A\n"; }
	~A() { std::cout << "Invoke destructor ~A\n"; }
};
struct B
{
	std::shared_ptr<A> a;
	B() { std::cout << "Invoke constructor B\n"; }
	~B() { std::cout << "Invoke destructor ~B\n"; }
};

struct C
{
	int x, val1, val2;
	int getX() { return x; }
	C() { std::cout << "Invoke constructor C\n"; }
	~C() { std::cout << "Invoke destructor ~C\n"; }

	int getVal3() const { return val3; }
private:
	static int val3;
};
int C::val3 = 0;
std::unique_ptr<C> function()
{
	return std::unique_ptr<C>(new C);
}

void useAB()
{
	auto a = std::make_shared<A>();
	auto b = std::make_shared<B>();
	a->b = b;
	b->a = a;
}

int main()
{
	//1
	//useAB();

	//2
	//std::shared_ptr<C> c(new C);
	//std::cout << "c.use_count() = " << c.use_count() << std::endl;

	//std::weak_ptr<C> b(c);
	////lock временно превращает weak в shared
	//std::cout << "b.use_count() = " << b.use_count() << " " << b.lock()->getX() << std::endl;

	//c.reset();

	//3
	/*std::shared_ptr<C> a, b, c1;
	std::shared_ptr<int> c(a, &a->val1), d(a, &a->val2);
	a = std::make_shared<C>();
	b = a;

	c1 = std::shared_ptr<C>(new C);
	std::cout << std::boolalpha;
	std::cout << "a < b = " << (a < b) << "\na.owner_before(b) = " << a.owner_before(b)
		<< "\nowner_less(a, b) = " << std::owner_less<std::shared_ptr<C>>()(a, b) << std::endl;

	std::cout << "c < d = " << (c < d) << "\nc.owner_before(d) = " << c.owner_before(d)
		<< "\nowner_less(c, d) = " << std::owner_less<std::shared_ptr<int>>()(c, d) << std::endl;

	std::cout << "a < c1 = " << (a < c1) << "\na.owner_before(c1) = " << a.owner_before(c1)
		<< "\nowner_less(a, c1) = " << std::owner_less<std::shared_ptr<C>>()(a, c1) << std::endl;

	std::cout << "c1 < a = " << (c1 < a) << "\nc1.owner_before(a) = " << c1.owner_before(a)
		<< "\nowner_less(c1, a) = " << std::owner_less<std::shared_ptr<C>>()(c1, a) << std::endl;*/

	//4
	std::unique_ptr<C>a(function());
	std::cout << a->val1 << std::endl;

	// NO
	//std::unique_ptr<C> b(a);

	// YES
	//std::unique_ptr<C> b(std::move(a));
	std::unique_ptr<C> b = std::move(a);

	//5 static variables;
	C obj;
	std::cout << obj.getVal3() << std::endl;

	return 0;
}
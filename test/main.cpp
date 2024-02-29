#include<iostream>
#include<memory>

int main() {
	int a{ 5 };

	a += a / 5;

	std::cout << a << std::endl;

	return 0;
}
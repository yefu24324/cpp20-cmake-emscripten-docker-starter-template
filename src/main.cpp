#include <iostream>

// This is C++20 only
#include <span>

int main(int, char**) {
	std::cout << "Hello, C++ 20!" << std::endl;

	std::cout << "Testing span: (expects 2,3,4,5)" << std::endl;
	constexpr int buffer[]{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	std::span slice = { buffer + 2, 4 };
	for (int value : slice) {
		std::cout << " - " << value << std::endl;
	}

	return 0;
}

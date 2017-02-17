#include <iostream>

class Vector {
public:
	int x;
	Vector(int _x) {
		x = _x;
		std::cout << x << "\n";
	}
	~Vector() {
		std::cout << x << "\n";
	}
};

/*int main() {
	Vector a(1), b(2);
}*/
#include <iostream>
#include <string>

using namespace std;

template <class T>
void print (T p) {
	cout << p << endl;
}

int main() {
	int i;

	print("Hello World");
	cin >> i;
	print(i);
	cin >> i;
	return 0;
}


#include <iostream>

using namespace std;

int main(){
	uint totalValue = 1;
	for(uint i = 1; i <= 10; i++){
		totalValue *= i;
		cout << "Print new number " << totalValue << endl;
	}
	// cout << "Hello World! Updated another time!" << endl;
	return 0;
}

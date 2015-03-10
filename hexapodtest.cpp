#include "hexapod.h"
#include <iostream>

using namespace std;

int main(){
	
	Hexapod * a = new Hexapod;

	a->update_end_effector(1,1,1,2,2,2);

	Vector3 position = a->get_pos();

	cout << "length: " << position.length() << endl;

	return 0;
}
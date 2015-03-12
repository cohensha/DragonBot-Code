#include "hexapod.h"
#include <iostream>

using namespace std;

int main(){
	
	Hexapod * a = new Hexapod;

	Vector3 position = a->get_pos();
	cout << "initial length: " << position.length() << endl;
	cout << " " << endl;

	a->update_end_effector(3,1,4,2,2,2);
	Vector3 position1 = a->get_pos();
	cout << "length: " << position1.length() << endl;
	cout << " " << endl;

	a->update_ik(1,1,1,2,2,2);
	Vector3 rpy = a->get_rpy();
	cout << "x value of rpy: " << rpy.getitem(0.0) << endl;

	return 0;
}
#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3 {
	public:
		Vector3(double x, double y, double z);
		~Vector3();
		Vector3 add(Vector3 b); //is b a vector3 or an array?
		Vector3 sub(Vector3 b);
		Vector3 mul(Vector3 b);
		Vector3 mul(double b);
		Vector3 div(double b);
		double dot(Vector3 b);
		Vector3 cross(Vector3 b);
		void normalize();
		double length();
		double* val();
		double getitem(int n);
		void setitem(int n, double v);
		string repr();
		Vector3 neg();
		void rotate(double axis, double angle);
	private:
		double a[3];

};

#endif
#ifndef VECTOR3_H
#define VECTOR3_H
#include <string>

class Vector3 {
	public:
		Vector3(double x, double y, double z);
		~Vector3();
		//takes a vector3 to add, returns a new vector3
		Vector3 add(Vector3 b);
		Vector3 operator+(Vector3 b);
		//takes a vector3 to subtract, returns a new vector3
		Vector3 sub(Vector3 b);
		Vector3 operator-(Vector3 b);
		//takes a vector3 to multiply, returns a new vector3
		Vector3 mul(Vector3 b);
		Vector3 operator*(Vector3 b);
		//takes a double to multiply, returns a new vector3
		Vector3 mul(double b);
		Vector3 operator*(double b);
		//takes a double to divide, returns a new vector3
		Vector3 div(double b);
		Vector3 operator/(double b);
		//takes a Vector3 to dot with, returns a double
		double dot(Vector3 b);
		//takes a vector3 to cross with, returns a Vector3
		Vector3 cross(Vector3 b);
		//normalizes the vector3
		void normalize();
		//computes and returns the length
		double length();
		//returns the array of the Vector3
		double* val();
		//returns a value at position n of the Vector3
		double getitem(int n);
		double operator[](int n);
		//changes the value at position b of the Vector3 to n
		void setitem(int n, double v);
		//returns a string of the Vector3
		std::string repr();
		//returns a negative version of the Vector3
		Vector3 neg();
		//rotates the vector3
		void rotate(Vector3 axis, double angle);
	private:
		//Vector3 is constructed as an array of leng 3
		double a[3];

};

#endif
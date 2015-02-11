#include "vector3.h"
#include <cmath>
#include <string>
#include <sstream>


Vector3::Vector3(double x[3]) {
	a[0]=x[0];
	a[1]=x[1];
	a[2]=x[2];
}

Vector3::~Vector3() {
	//do we need a deconstructor?
}

Vector3 Vector3::add(Vector3 b) {
	double temp[3]={a[0]+b.a[0],a[1]+b.a[1],a[2]+b.a[2]};
	return Vector3(temp);
}

Vector3 Vector3::sub(Vector3 b) {
	double temp[3]={a[0]-b.a[0],a[1]-b.a[1],a[2]-b.a[2]};
	return Vector3(temp);
}

Vector3 Vector3::mul(Vector3 b) {
	double temp[3]={a[0]*b.a[0],a[1]*b.a[1],a[2]*b.a[2]};
	return Vector3(temp);
}

Vector3 Vector3::mul(double b) {
	double temp[3]={a[0]*b,a[1]*b,a[2]*b};
	return Vector3(temp);
}

Vector3 Vector3::div(double b) {
	double temp[3]={a[0]/b,a[1]/b,a[2]/b};
	return Vector3(temp);
}

double Vector3::dot(Vector3 b) {
	return ( (a[0]*b.a[0]) + (a[1]*b.a[1]) + (a[2]*b.a[2]) );
}

Vector3 Vector3::cross(Vector3 b) {
	double nx = (a[1]*b.a[2])-(a[2]*b.a[1]);
    double ny = (a[2]*b.a[0])-(a[0]*b.a[2]);
    double nz = (a[0]*b.a[1])-(a[1]*b.a[0]);
    double temp[3]={nx,ny,nz};
	return Vector3(temp);
}

void Vector3::normalize() {
	double vector_len = sqrt(pow(a[0],2)+pow(a[1],2)+pow(a[2],2));
	double inv_len;
	if (vector_len==0) {
		inv_len=0;
	}
	else {
		inv_len=1.0/vector_len;
	}
	a[0]=a[0]*inv_len;
	a[1]=a[1]*inv_len;
	a[2]=a[2]*inv_len;
	return;
}

double Vector3::length() {
	return sqrt(pow(a[0],2)+pow(a[1],2)+pow(a[2],2));
}

double* Vector3::val() {
	return a;
}

double Vector3::getitem(int n) {
	return a[n];
}

void Vector3::setitem(int n, double v) {
	a[n]=v;
	return;
}

std::string Vector3::repr(){
	std::stringstream s;
	double scale = 0.01;//round to nearest one-hundreth
	double value1 = floor(a[0]/scale + 0.5) * scale;
	double value2 = floor(a[1]/scale + 0.5) * scale;
	double value3 = floor(a[2]/scale + 0.5) * scale;
	s <<"[ " << value1 <<" , "<<value2<<" , "<<value3<<" ]";
	return s.str();
}

Vector3 Vector3::neg() {
	double temp[3]={-a[0],-a[1], -a[2]};
	return Vector3(temp);
}

void Vector3::rotate(double axis[], double angle) {
	double sa=sin(angle);
	double ca=cos(angle);
	double x=a[0];
	double y=a[1];
	double z=a[2];

	//normalize axis
	Vector3 axis2= Vector3(axis);
	axis2.normalize();

	//rotation matrix
	double m[9]={0};
	m[ 0 ] = ca + (1 - ca) * axis2.a[0] * axis2.a[0];
    m[ 1 ] = (1 - ca) * axis2.a[0] * axis2.a[1] - sa * axis2.a[2];
    m[ 2 ] = (1 - ca) * axis2.a[2] * axis2.a[0] + sa * axis2.a[1];
    m[ 3 ] = (1 - ca) * axis2.a[0] * axis2.a[1] + sa * axis2.a[2];
    m[ 4 ] = ca + (1 - ca) * axis2.a[1] * axis2.a[1];
    m[ 5 ] = (1 - ca) * axis2.a[1] * axis2.a[2] - sa * axis2.a[0];
    m[ 6 ] = (1 - ca) * axis2.a[2] * axis2.a[0] - sa * axis2.a[1];
    m[ 7 ] = (1 - ca) * axis2.a[1] * axis2.a[2] + sa * axis2.a[0];
    m[ 8 ] = ca + (1 - ca) * axis2.a[2] * axis2.a[2];

    a[0] = m[0] * x + m[1] * y + m[2] * z;
    a[1] = m[3] * x + m[4] * y + m[5] * z;
    a[2] = m[6] * x + m[7] * y + m[8] * z;
    return;
}



#include "vector3.h"

Vector3::Vector3(double x[3]) {
	a[0]=x[0];
	a[1]=x[1];
	a[2]=x[2];
}

Vector3 Vector3::add(Vector3 b) {
	return Vector3([a[0]+b[0],a[1]+b[1],a[2]+b[2]]);
	//will vector3 still be alive when returned?
}

Vector3 Vector3::sub(Vector3 b) {
	return Vector3([a[0]-b.a[0],a[1]-b.a[1],a[2]-b.a[2]]);
	//will vector3 still be alive when returned?
}

Vector3 Vector3::mul(Vector3 b) {
	return Vector3([a[0]*b.a[0],a[1]*b.a[1],a[2]*b.a[2]]);
	//will vector3 still be alive when returned?
}

Vector3 Vector3::mul(double b) {
	return Vector3([a[0]*b,a[1]*b,a[2]*b]);
}

Vector3 Vector3::div(double b) {
	return Vector3([a[0]/b,a[1]/b,a[2]/b]);
}

double Vector3::dot(double b) {
	return ( (a[0]*b.a[0]) + (a[1]*b.a[1]) + (a[2]*b.a[2]) );
}

Vector3 Vector3::cross(Vector3 b) {
	double nx = (a[1]*b.a[2])-(a[2]*b.a[1]);
    double ny = (a[2]*b.a[0])-(a[0]*b.a[2]);
    double nz = (a[0]*b.a[1])-(a[1]*b.a[0]);
	return Vector3([nx,ny,nz]);
}

Vector3 Vector3::normalize() {
	double vector_len = sqrt(pow(a[0],2)+pow(a[1],2)+pow(a[2],2));
	double inv_len;
	if (vector_len==0) {
		inv_len=0;
	}
	else {
		inv_len=1.0/vector_len;
	a[0]=a[0]*inv_len;
	a[1]=a[1]*inv_len;
	a[2]=a[2]*inv_len;
	}
}
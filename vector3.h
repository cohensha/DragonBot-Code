//put include stuff here

class Vector3 {
	public:
		Vector3(double x, double y, double z);
		~Vector3();
		Vector3 add(Vector3 b); //what is b?
		Vector3 sub(Vector3 b);
		Vector3 mul(Vector3 b);
		Vector3 mul(double b);
		Vector3 div(double b);
		Vector3 dot(Vector3 b);
		Vector3 cross(Vector3 b);
		Vector3 normalize();
		double length();
		Vector3 val();
		double getitem(int n);
		void setitem(int n, double v);
		string repr();
		Vector3 neg();
		Vector3 rotate(double axis, double angle);
	private:
		double a[3];


}
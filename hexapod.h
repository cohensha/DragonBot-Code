#ifndef HEXAPOD_H
#define HEXAPOD_H

class Hexapod{

public: 
	//constructor
	Hexapod();
	//destructor
	~Hexapod();

	//updater
	void update_end_effector( double& x,double& y,
		double& z,double&  u, double& v, double& w);

	//build shoulders
	void build_shoulders();

	//update wrists
	void update_wrists();

	void pdate_ik(self, double& x, double&y, double& z,
		double& u, double& v, double& w);

	void update_shoulders();

	Hexapod * get_rpy();

	Hexapod * get_pos();

	
        


private:

	//variables
	double wrists[6];
	double shoulders[6];
	double elbows[6];
	double shoulder_to_elbow [6];
    double self.ee_pos;
    double self.ee_rpy;
    double self.ee_up;
    double self.ee_fw;
    double self.ee_left;
    double self.angles [6];
    double self.rel_z;

    double el;
    double wr;
    double aa;
    double cc;
    double bb;
    double self.rel_z
}
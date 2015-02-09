#ifndef HEXAPOD_H
#define HEXAPOD_H

class Hexapod{

public: 
	//constructor
	Hexapod();
	//destructor
	~Hexapod();

	//updater
	void update_end_effector(, x,y,z,u,v,w);


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
}
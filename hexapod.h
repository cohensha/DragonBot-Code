#ifndef HEXAPOD_H
#define HEXAPOD_H
#include "vector3.h"

//measurements based on computer model of robot
double BICEP_LENGTH = 5.000;
double FOREARM_LENGTH =16.750;
double SWITCH_ANGLE = 19.690;
//top center to wrist hole: X7.635 Y+/-0.553 Z0.87
double T2W_X = 7.635;
double T2W_Y = 0.553;
double T2W_Z = -0.870;
//base center to shoulder hole: X8.093 Y+/-2.15 Z7.831
double B2S_X = 8.093;
double B2S_Y = 2.150;
double B2S_Z = 6.618;

//some experimentally determined limits on in/out distance (distance along motor shaft direction)
double MAX_IN = 4.46;
double MAX_OUT = 4.25;
double POS_STEP = 0.1;
double RPY_STEP = 1;

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
    double ee_pos;
    double ee_rpy;
    double ee_up;
    double ee_fw;
    double ee_left;
    double angles [6];
    double rel_z;

    double el;
    double wr;
    double aa;
    double cc;
    double bb;
    double rel_z
}
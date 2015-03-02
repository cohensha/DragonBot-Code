#ifndef HEXAPOD_H
#define HEXAPOD_H
#include "vector3.h"

class Hexapod {

public: 
	//constructor
	Hexapod();
	//destructor
	~Hexapod();

	//updater
	void update_end_effector( double x,double y,
		double z,double u, double v, double w);

	//build shoulders
	void build_shoulders();

	//update wrists
	void update_wrists();

	void update_ik(double x, double y, double z,
		double u, double v, double w);

	void update_shoulders();

	Vector3 get_rpy();

	Vector3 get_pos();

	//need to write
	Vector3 deepcopy();

	//void best_effort_ik(char pos1, double val1, char pos2='n', double val2=0, char pos3='n', double val3=0,
                        //char pos4='n', double val4=0, char pos5='n', double val5=0, char pos6='n', double val6=0);

	bool check_ik(char pos1, double val1, char pos2, double val2, char pos3, double val3,
                        char pos4, double val4, char pos5, double val5, char pos6, double val6);

private:

	//variables
	Vector3 wrists[6];
	Vector3 shoulders[6];
	Vector3 elbows[6];
	Vector3 shoulder_to_elbow [6];
    Vector3 ee_pos;
    Vector3 ee_rpy;
    Vector3 ee_up;
    Vector3 ee_fw;
    Vector3 ee_left;
    double angles [6];

    Vector3 el;
    Vector3 wr;
    double aa;
    double cc;
    double bb;
    double rel_z;
};

#endif
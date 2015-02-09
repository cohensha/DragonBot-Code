#include "hexapod.h"


Hexapod::Hexapod (){
	wrists = {0,0,0,0,0,0};
	shoulders = {0,0,0,0,0,0};
	elbows = {0,0,0,0,0,0};
	shoulder_to_elbow = {0,0,0,0,0,0};
    self.ee_pos = 0.0;
    self.ee_rpy = 0.0;
    self.ee_up = 0.0;
   	self.ee_fw = 0.0;
    self.ee_left = 0.0;
    self.angles = 0.0;
    self.rel_z = 0.0;

    update_end_effector(0,0,0,0,0,0);
    build_shoulders();
    update_wrists();


    el = elbows[0];
    wr = wrists[0];
    aa = el[1]-wr[1];
    cc = FOREARM_LENGTH;
    bb = sqrt(cc*cc-aa*aa);
    self.rel_z = bb+B2S_Z-T2W_Z;

     update_ik(0,0,0,0,0,0);
}

Hexapod::~Hexapod();

void Hexapod ::update_end_effector( double x,double y,double z,
		double u, double v, double w){

	
}


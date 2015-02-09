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
}
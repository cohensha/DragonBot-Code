#include "hexapod.h"
#include <cmath>

Hexapod::Hexapod () {
    //i think wrists, shoulders, elbows, etc are arrays of Vector3...
    for (int i=0; i<6; i++) {
        wrists[i]=Vector3();
        shoulders[i]=Vector3();
        elbows[i]=Vector3();
        shoulder_to_elbow[i]=Vector3();
    }
    /*for (int i=0; i<6; i++) {
        shoulders[i]=Vector3();
    }
    for (int i=0; i<6; i++) {
        elbows[i]=Vector3();
    }
    for (int i=0; i<6; i++) {
        shoulder_to_elbow[i]=Vector3();
    }*/
	//shoulders = {0,0,0,0,0,0};
	//elbows = {0,0,0,0,0,0};
	//shoulder_to_elbow = {0,0,0,0,0,0};
    ee_pos = Vector3(0.0,0.0,0.0);
    ee_rpy = Vector3(0.0,0.0,0.0);
    ee_up = Vector3(0.0,0.0,0.0);
   	ee_fw = Vector3(0.0,0.0,0.0);
    ee_left = Vector3(0.0,0.0,0.0);
    for (int i=0; i<6;i++) {
        angles[i]=0.0;
    }
    //angles = {0.0};
    rel_z = 0.0;

    update_end_effector(0,0,0,0,0,0);
    build_shoulders();
    update_wrists();


    el = elbows[0];
    wr = wrists[0];
    aa = el[1]-wr[1];
    cc = FOREARM_LENGTH;
    bb = sqrt(cc*cc-aa*aa);
    rel_z = bb+B2S_Z-T2W_Z;

    //update_ik(0,0,0,0,0,0);
}

Hexapod::~Hexapod() {
    //
}

void Hexapod::update_end_effector( double x,double y,double z,
		double u, double v, double w){
        //update end effector position
        double pi=atan(1)*4;
        ee_pos= Vector3(x,y,z);
        ee_rpy= Vector3(u*pi/180,v*pi/180,z*pi/180);
        ee_up = Vector3(0,0,1);
        ee_fw = Vector3(1,0,0);
        ee_left= Vector3(0,1,0);

        //roll
        Vector3 axis=Vector3(1,0,0);
        ee_up.rotate(axis,ee_rpy[0]);
        ee_fw.rotate(axis,ee_rpy[0]);
        ee_left.rotate(axis,ee_rpy[0]);

        //pitch
        axis = Vector3(0,1,0);
        ee_up.rotate(axis, ee_rpy[1]);
        ee_fw.rotate(axis, ee_rpy[1]);
        ee_left.rotate(axis, ee_rpy[1]);

        //yaw
        axis = Vector3(0,0,1);
        ee_up.rotate(axis, ee_rpy[2]);
        ee_fw.rotate(axis, ee_rpy[2]);
        ee_left.rotate(axis, ee_rpy[2]);

}

void Hexapod::build_shoulders() {
    //get shoulder and elbow initial positions
    double pi=atan(1)*4;
    for (int i=0; i<3; i++) {
        double c=cos(i*pi*2/3.0);
        double s=sin(i*pi*2/3.0);

        Vector3 n=ee_fw; //what type is ee_fw?
        Vector3 o=ee_up.cross(ee_fw);
        o.normalize();

        Vector3 n1=n*c + o*s;
        Vector3 o1=(n*-s + (o*c));

        shoulders[i*2+0]=n1*B2S_X - o1*B2S_Y + ee_up*B2S_Z;
        shoulders[i*2+1]=n1*B2S_X - o1*B2S_Y + ee_up*B2S_Z;

        elbows[i*2+0] = n1*B2S_X - o1*(B2S_Y+BICEP_LENGTH) + ee_up*B2S_Z;
        elbows[i*2+1] = n1*B2S_X + o1*(B2S_Y+BICEP_LENGTH) + ee_up*B2S_Z;

        shoulder_to_elbow[i*2+0] = o1.neg();
        shoulder_to_elbow[i*2+1] = o1;
    }
}

void Hexapod::update_wrists() {
    //update wrist positions
    double pi=atan(1)*4;
    for (int i=0; i<3; i++) {
        double c = cos(i*pi*2/3.0);
        double s = sin(i*pi*2/3.0);

        Vector3 n = ee_fw;
        Vector3 o = ee_up.cross(ee_fw);
        o.normalize();

        Vector3 n1 = n*c + o*s;
        Vector3 o1 = n*-s + o*c;

        wrists[i*2+0] = ee_pos + n1*T2W_X - o1*T2W_Y + ee_up*T2W_Z;
        wrists[i*2+1] = ee_pos + n1*T2W_X + o1*T2W_Y + ee_up*T2W_Z;
    }
}

void Hexapod::update_ik(double& x, double& y, double& z, 
        double& u, double& v, double& w) {
        //print "Updating IK for pose: " + str(x) + " " + str(y) + " " + str(z) + " " + str(u) + " " + str(v) + " " + str(w)
        z = z+rel_z;
        update_end_effector(x,y,z,u,v,w);
        update_wrists();
        update_shoulders();
}

/* i'm not sure if I did this function right
need to check over the types for each variable

void Hexapod::update_shoulders() {
    for (int i=0; i<6; i++) {
        Vector3 ortho = Vector3(cos((i/2)*2*pi/3.0),sin((i/2)*2*pi/3.0), 0);
        Vector3 w = wrists[i]-shoulders[i];
        double a = w.dot(ortho);

        Vector3 wop = w - (ortho*a);

        double b = sqrt(FOREARM_LENGTH*FOREARM_LENGTH-a*a);
            
        double r1 = b;
        double r0 = BICEP_LENGTH;
        double d = wop.length();

        a = (r0*r0 - r1*r1 + d*d)/(2*d);

        wop = wop/d;

        Vector3 temp = shoulders[i]+(wop*a);

        double hh = sqrt(r0*r0-a*a);

        Vector3 r = ortho.cross(wop);

        if (i%2 == 0) {
            self.elbows[i]=temp + r*hh;
        }

        else {
            self.elbows[i]=temp - r*hh;
        }

        temp = elbows[i]-shoulders[i];
        double y = -temp[2];
        temp[2] = 0; //will this actually change it to 0?
        double x = temp.length();

        if (shoulder_to_elbow[i].dot(temp) < 0) {
            x = -x;
        }
        angles[i] = degrees(atan2(-y,x));
    }
}
*/

/*Vector3 Hexapod::get_rpy() { //what is the return type?
    return ee_rpy; //will this give a deep copy?
}
*/

/* haven't converted this one to c++ yet
def get_pos(self):
    ret = copy.deepcopy(self.ee_pos)
    ret[2] = ret[2]-self.rel_z
    return ret
*/

/*bool Hexapod::check_ik(double x=None,double y =None, double z=None,
    double u=None, double v=None,double w=None) {
    Vector3 old_pos=get_pos(); //what is the type for old_pos?
    Vector3 old_rpy=get_rpy();

    if (x==None) {
        x=old_pos[0];
    }
    if (y==None) {
        y=old_pos[1];
    }
    if (z==None) {
        z=old_pos[2];
    }
    if (u==None) {
        u=old_rpy[0];
    }
    if (v==None) {
        v=old_rpy[1];
    }
    if (w==None) {
        w=old_rpy[2];
    }

    bool success=true;

    how to convert this to c++?
        try:
            self.update_ik(x,y,z,u,v,w)
        except ValueError:
            success = False
    

    for (int i=0; i<6; i++) {
        Vector3 ua=elbows[i]-shoulders[i];
        Vector3 la=wrists[i]-elbows[i];
        z=Vector3(0,0,1);
        if (i%2 == 0) {
            Vector3 n=z.cross(ua);
        }
        else {
            Vector3 n=ua.cross(z);
        }
        n.normalize();
        double c=n.dot(la);
        if (c<0 && abs(c) > MAX_IN) {
            success=false;
        }
        if (c>0 && c> MAX_OUT) {
            success=false;
        }
    }

    if (!success) {
        update_ik(old_pos[0], old_pos[1], old_pos[2], 
            old_rpy[0],old_rpy[1], old_rpy[2]);
    }
    return success;
}

return type? Hexapod:: best_effort(double x=None,double y=None,double z=None,
 double u=None,double v=None,double w=None) {
    Vector3 old_pos=get_pos();
    Vector3 old_rpy=get_rpy();

    if (x==None) {
        x=old_pos[0];
    }
    if (y==None) {
        y=old_pos[1];
    }
    if (z==None) {
        z=old_pos[2];
    }
    if (u==None) {
        u=old_rpy[0];
    }
    if (v==None) {
        v=old_rpy[1];
    }
    if (w==None) {
        w=old_rpy[2];
    }
    
    bool success=check_ik(x,y,z,u,v,w);
    while (!success) {
        Vector3 goal_pos=Vector3(x,y,z);
        Vector3 goal_rpy=Vector3(u,v,w);

        Vector3 zero_pos=Vector3(0,0,0);
        Vector3 zero_rpy=Vector3(0,0,0);

        Vector3 step_pos=zero_pos-goal_pos;
        Vector3 step_rpy=zero_pos-goal_rpy;

        step_pos.normalize();
        step_pos=step_pos*POS_STEP;
        step_rpy.normalize();
        step_rpy=step_rpy+step_rpy;

        Vector3 new_goal_pos=goal_pos_step_pos;
        Vector3 new_goal_rpy=goal_rpy+step_rpy;

        x=new_goal+pos[0];
        y = new_goal_pos[1];
        z = new_goal_pos[2];

        u = new_goal_rpy[0];
        v = new_goal_rpy[1];
        w = new_goal_rpy[2];

        success=self.check_ik(x,y,z,u,v,w);
    }
    if (!success) {
        cout << "Nearest valid pose: " + new_goal_rpy.repr() + new_goal_rpy.repr() << endl;
    }

    how to return x,y,z,u,v,w?
}
*/






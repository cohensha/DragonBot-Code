#include "hexapod.h"
#include "vector3.h"
#include "gtest/gtest.h"

class HexaTest : public testing::Test {
protected:

};


TEST_F(HexaTest, Nominal_Check_IK) {
	Hexapod h=Hexapod();
	EXPECT_EQ(h.check_ik('x',0,'y',0,'z',0,'u',0,'v',0,'w',0), true);
	EXPECT_EQ(h.check_ik('x',-3,'y',-3,'z',-3,'u',-3,'v',-3,'w',-3), true);
	EXPECT_EQ(h.check_ik('x',-5,'y',-5,'z',-5,'u',-5,'v',-5,'w',-5), false);
	EXPECT_EQ(h.check_ik('x',4,'y',4,'z',4,'u',4,'v',4,'w',4), false);
}

TEST_F(HexaTest, Less_Arg_Check_IK) {
	Hexapod h=Hexapod();
	EXPECT_EQ(h.check_ik('x',0,'w',0), true);
	EXPECT_EQ(h.check_ik('x',-3,'u',-3,'v',-3,'w',-3), true);
	EXPECT_EQ(h.check_ik('x',-5,'y',-5,'z',-5,'u',-5), false);
	EXPECT_EQ(h.check_ik('x',4,'y',4,'z',4,'u',4), false);
}

TEST_F(HexaTest, Off_Nominal_Best_IK) {
	Hexapod h=Hexapod();
	double x[6];
	h.best_effort_ik(x,'x',-4,'y',-4,'z',-4,'u',-4,'v',-4,'w',-4);
	EXPECT_EQ(x[0],-3.422649730810373);
	EXPECT_EQ(x[1],-3.422649730810373);
	EXPECT_EQ(x[2],-3.422649730810373);
	EXPECT_EQ(x[3],-0.5358983848622456);
	EXPECT_EQ(x[4],-0.5358983848622456);
	EXPECT_EQ(x[5],-0.5358983848622456);

	h.best_effort_ik(x,'x',10,'y',10,'z',10,'u',10,'v',10,'w',10);
	EXPECT_EQ(x[0],2.898591688967633);
	EXPECT_EQ(x[1],2.898591688967633);
	EXPECT_EQ(x[2],2.898591688967633);
	EXPECT_EQ(x[3],0.1850454237763578);
	EXPECT_EQ(x[4],0.1850454237763578);
	EXPECT_EQ(x[5],0.1850454237763578);
}

TEST_F(HexaTest, Nominal_Best_IK) {
	Hexapod h=Hexapod();
	double x[6];
	h.best_effort_ik(x,'x',0,'y',0,'z',0,'u',0,'v',0,'w',0);
	EXPECT_EQ(x[0],0);
	EXPECT_EQ(x[1],0);
	EXPECT_EQ(x[2],0);
	EXPECT_EQ(x[3],0);
	EXPECT_EQ(x[4],0);
	EXPECT_EQ(x[5],0);

	h.best_effort_ik(x,'x',2,'y',2,'z',2,'u',2,'v',2,'w',2);
	EXPECT_EQ(x[0],2);
	EXPECT_EQ(x[1],2);
	EXPECT_EQ(x[2],2);
	EXPECT_EQ(x[3],2);
	EXPECT_EQ(x[4],2);
	EXPECT_EQ(x[5],2);
}

//TODO: check angles!
TEST_F(HexaTest, Angle_Check) {

	//initial angles should start at 0
	Hexapod h = Hexapod();
	double x[6];
	h.get_angles(x);
	EXPECT_EQ(x[0], 0.0);
	EXPECT_EQ(x[1], 0.0);
	EXPECT_EQ(x[2], 0.0);
	EXPECT_EQ(x[3], 0.0);
	EXPECT_EQ(x[4], 0.0);
	EXPECT_EQ(x[5], 0.0);

	h.best_effort_ik(x,'x',1,'y',1,'z',1,'u',1,'v',1,'w',1);
	h.update_shoulders();
	h.get_angles(x);
	EXPECT_EQ(x[0], );
	EXPECT_EQ(x[1], atan2(-1,1)*180/pi);
	EXPECT_EQ(x[2], atan2(-1,1)*180/pi);
	EXPECT_EQ(x[3], atan2(-1,1)*180/pi);
	EXPECT_EQ(x[4], atan2(-1,1)*180/pi);
	EXPECT_EQ(x[5], atan2(-1,1)*180/pi);
}






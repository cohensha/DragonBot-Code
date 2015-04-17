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

TEST_F(HexaTest, Nominal_Best_IK) {
	Hexapod h=Hexapod();
	double x[6];
	h.best_effort_ik(x,'x',-4,'y',-4,'z',-4,'u',-4,'v',-4,'w',-4);
	EXPECT_EQ(x[0],-3.422649730810373);
	EXPECT_EQ(x[1],-3.422649730810373);
	EXPECT_EQ(x[2],-3.422649730810373);
	EXPECT_EQ(x[3],-0.5358983848622456);
	EXPECT_EQ(x[4],-0.5358983848622456);
	EXPECT_EQ(x[5],-0.5358983848622456);
}







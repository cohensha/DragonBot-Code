# In this Makefile we'll introduce the concepts of Makefile automatic variables
# Make will simply substitute these variables with the corresponding string
# $< - first dependency
# $^ - all dependencies
# $@ - target name (whatever's before colon)

# Let's declare some variables
CC       = g++
CPPFLAGS = -Wall -g
BIN_DIR  = bin
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

all: hexatest
	-@echo "--- All Built!---"

hexatest: vector3.cpp hexapod1.cpp hexa_gtest.cpp
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

clean:
	-@rm hexatest
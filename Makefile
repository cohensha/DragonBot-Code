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

all: $(BIN_DIR)/hexapod1.o
	-@echo "--- All Built!---"

# $< is an auto variable that means "first dependency", which is fib.cpp in this case
# $@ is an auto variable that means "target name", which is $(BIN_DIR)/fib.o in this case
$(BIN_DIR)/vector3.o: vector3.h vector3.cpp $(BIN_DIR)/.dirstamp	
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/hexapod1.o: hexapod1.cpp hexapod.h vector3.h vector3.cpp $(BIN_DIR)/.dirstamp	
	$(CC) $(CPPFLAGS) -c $< -o $@

# $^ is an auto variable that means "all dependencies",
#   which are test.cpp and $(BIN_DIR)/fib.o in this case
# IMPORTANT: $(GTEST_LL) needs to come *after* the source files
hexatest: vector3.cpp hexapod1.cpp hexa_gtest.cpp
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

# Rule to ensure the $(BIN_DIR) directory exist or it'll create it.
# $@ is an auto variable that means "target name", which is $(BIN_DIR)/.dirstamp in this case
$(BIN_DIR)/.dirstamp:
	-@mkdir -p $(BIN_DIR)
	-@touch $@

.PHONY: clean tests

tests: $(BIN_DIR)/HexaTest
	-@$(BIN_DIR)/HExaTest
	-@echo "--- All Tested!---"

clean:
	-@rm -rf $(BIN_DIR)
	-@echo "--- All Clean!---"
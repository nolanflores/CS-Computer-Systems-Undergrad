# To build the regular test program, just run `make`.

# To build the test program that creates a linked list of doubles by using
# a linked_list class template from the extra credit, run `make test_double`.
# But first, you'll need to create test_double.cpp (it should be identical
# to test.cpp, but it should create a linked list of doubles instead of ints).

CXX = g++ -g
DEP_FLAGS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.d
EXE = test
EXE_EC = test_double

SRC_DIR = .
SRC = $(shell find $(SRC_DIR) \! -regex ".*test_double\.cpp" -regex ".*\.cpp")
SRC_EC = $(shell find $(SRC_DIR) \! -regex ".*test\.cpp" -regex ".*\.cpp")

OBJ_DIR = .obj
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
OBJ_EC = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_EC))

DEP_DIR = .deps
DEP = $(patsubst $(SRC_DIR)/%.cpp,$(DEP_DIR)/%.d,$(SRC))
DEP_EC = $(patsubst $(SRC_DIR)/%.cpp,$(DEP_DIR)/%.d,$(SRC_EC))

$(EXE): $(OBJ)
	$(CXX) -o $@ $^

$(EXE_EC): $(OBJ_EC)
	$(CXX) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(DEP_DIR)/%.d $(OBJ_DIR)/%.o.sentinel $(DEP_DIR)/%.d.sentinel
	$(CXX) $(DEP_FLAGS) -I . -c -o $@ $<

$(OBJ_DIR)/%.sentinel:
	@mkdir -p ${@D}
	@touch $@

$(DEP_DIR)/%.sentinel:
	@mkdir -p ${@D}
	@touch $@

$(DEP):

$(DEP_EC):

include $(wildcard $(DEP))

include $(wildcard $(DEP_EC))

clean:
	rm -rf $(OBJ_DIR) $(DEP_DIR) $(EXE) $(EXE_EC)

.PHONY: clean

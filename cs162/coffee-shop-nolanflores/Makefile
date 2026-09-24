# This is a very fancy makefile. Don't touch it. It works like magic, even if
# you add more .cpp files and .hpp files to this project. It also
# auto-generates dependency lists as a side effect of compilation, so you'll
# basically never need to run `make clean`. The `clean` target is still there
# in case you want to use it, though.

CXX = g++ -g
DEP_FLAGS = -MT $@ -MMD -MP -MF $(DEP_DIR)/$*.d
EXE = start_shop

SRC_DIR = .
SRC = $(shell find $(SRC_DIR) -mindepth 1 -maxdepth 1 -regex ".*\.cpp")

OBJ_DIR = .obj
OBJ = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

DEP_DIR = .deps
DEP = $(patsubst $(SRC_DIR)/%.cpp,$(DEP_DIR)/%.d,$(SRC))

$(EXE): $(OBJ)
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

include $(wildcard $(DEP))

clean:
	rm -rf $(OBJ_DIR) $(DEP_DIR) $(EXE)

# This target is strictly for building and running
# the Big 3 testing script. You can execute it via
# `make test` from the terminal. It will build the tests
# from source, run them through valgrind, and then delete
# them.
test: __tests__/testbig3.cpp shop.cpp menu.cpp order.cpp coffee.cpp
	@g++ -g -o .test_big_3 $^ -I./
	- @valgrind ./.test_big_3
	@rm -f ./.test_big_3
	@echo
	@echo "IMPORTANT: The above output should say \"in use at exit: 0 bytes in 0 blocks\". If it doesn't say this, then you have a memory leak, and you'll lose some points."
	@echo "Possible causes of memory leaks include, but are not limited to:"
	@echo "- Improperly implemented or nonexistent destructor(s) for classes whose objects own pointers to dynamic memory"
	@echo "- shop::add_order or menu::add_coffee fail to delete old arrays after allocating new, bigger ones"
	@echo "- Assignment operator overloads fail to delete old, pre-existing dynamic memory before allocating new dynamic memory"
	@echo
	@echo "IMPORTANT: The above output should NOT print out any memory errors, such as double frees, use of uninitialized values, invalid reads, etc. If it does, you'll lose some points."
	@echo "- Double frees are caused by deleting dynamic memory twice. To avoid this, make sure to reassign pointers to nullptr after deleting the dynamic memory that they point to, and make sure to check that a pointer is NOT equal to nullptr before using the delete operator on it."
	@echo "- Use of uninitialized values is caused by (as you might guess) using values that have not yet been initialized. Recall that primitives and pointers are uninitialized upon declaration, so you should make sure that all primitive values and pointers in your entire program (including member variables of objects) get initialized before you attempt to use them in any other way."
	@echo "- Invalid reads are usually caused by accessing data through an invalid pointer, such as dereferencing a null pointer or an uninitialized pointer (see above; pointers, like primitive types, must be initialized before you can use them, and you should make sure that you never dereference [nor use the delete operator on] a pointer whose value is equal to nullptr)"

.PHONY: clean test

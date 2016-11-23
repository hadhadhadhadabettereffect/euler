CC := g++
CXXFLAGS := -c -Wall -std=c++17
PROB_DIR := problems
INCL_DIR := include
INCL := -I $(PROB_DIR) -I $(INCL_DIR)
BUILD_DIR := build
FILE_PREFIX := problem_
PROB_FILES := $(wildcard $(PROB_DIR)/$(FILE_PREFIX)*.h)

.PHONY: all
all:
	@echo "#ifndef ACTIVE_PROBLEMS_H" > $(INCL_DIR)/active_problems.h
	@echo "#define ACTIVE_PROBLEMS_H" >> $(INCL_DIR)/active_problems.h
	@for I in $(notdir $(PROB_FILES)); do \
		echo "#include \"$$I\"" >> $(INCL_DIR)/active_problems.h; \
	done
	@echo "#endif" >> $(INCL_DIR)/active_problems.h
	@$(MAKE) --no-print-directory main

main: $(BUILD_DIR)/main.o
	@$(CC) $(BUILD_DIR)/main.o -o $(BUILD_DIR)/main
	@$(BUILD_DIR)/main

$(BUILD_DIR)/main.o: main.cpp $(PROB_FILES) clean
	@$(CC) $(CXXFLAGS) $(INCL) -c $< -o $@

%: probs $(PROB_DIR)/$(FILE_PREFIX)%.h
	@:

.PHONY: probs
probs:
	@echo "#ifndef ACTIVE_PROBLEMS_H" > $(INCL_DIR)/active_problems.h
	@echo "#define ACTIVE_PROBLEMS_H" >> $(INCL_DIR)/active_problems.h
	@for I in $(MAKECMDGOALS); do \
		echo "#include \"$(FILE_PREFIX)$$I.h\"" >> $(INCL_DIR)/active_problems.h; \
	done
	@echo "#endif" >> $(INCL_DIR)/active_problems.h
	@$(MAKE) --no-print-directory main

.PHONY: clean
clean:
	@rm -f $(BUILD_DIR)/*.o

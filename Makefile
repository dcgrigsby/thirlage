CC=clang
SRC_DIR=./src
BUILD_DIR=./build
DOC_DIR=./doc

OBJS=$(shell find $(SRC_DIR) -name '*.c'|sed 's:$(SRC_DIR)/\(.*\).c:$(BUILD_DIR)/\1.o:')
DEPS=$(OBJS:.o=.d)

# both thirlage.c and tests.c have a main(), so use set to exclude the other when building

thirlage: $(OBJS)
	$(CC) $(shell echo $(OBJS) |sed 's:$(BUILD_DIR)/tests.o::') -o $@
	
tests:
	$(CC) $(shell echo $(OBJS) |sed 's:$(BUILD_DIR)/thirlage.o::') -o $@
	
doc: doxygen.conf
	(cat doxygen.conf; echo "OUTPUT_DIRECTORY=$(DOC_DIR)") | doxygen -

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) -I src -MMD -MP -c $< -o $@

-include $(DEPS)

.PHONY: clean-doc clean-build

clean-doc:
	rm -fr $(DOC_DIR)

clean-build:
	rm -fr $(BUILD_DIR)

clean-thirlage:
	rm -rf thirlage

clean-tests:
	rm -rf tests

clean: clean-doc clean-build clean-tests clean-thirlage





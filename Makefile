CC=clang

TARGET_EXEC ?= thirlage

BUILD_DIR ?= ./build
DOC_DIR ?= ./doc
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(INC_FLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean

doc: doxygen.conf
	$(RM) -r $(DOC_DIR)
	doxygen doxygen.conf

clean-doc:
	$(RM) -r $(DOC_DIR)

clean-build:
	$(RM) -r $(BUILD_DIR)

clean: clean-doc clean-build

-include $(DEPS)

MKDIR_P ?= mkdir -p


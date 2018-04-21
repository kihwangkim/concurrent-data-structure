TARGET ?= a.out
SRC_DIRS ?= .

CXXFLAGS = -g -Wall -std=c++11
#CXXFLAGS = -g -Wall -std=c++11 -DGL

#CXXFLAGS ?= $(INC_FLAGS) -MMD -MP -lpthread

SRCS := $(shell find $(SRC_DIRS) -name "*.cpp" -or -name "*.c" -or -name "*.s")
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))


$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LOADLIBES) $(LDLIBS) -lpthread


.PHONY: run
run: clean $(TARGET)
	./$(TARGET)

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)

-include $(DEPS)

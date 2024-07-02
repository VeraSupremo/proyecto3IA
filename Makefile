CXX= g++
CXXFLAGS = -g -Wall -Wextra -O3

OBJS = State.o MNK.o 


TARGET = MNK

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LIBS)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
:w

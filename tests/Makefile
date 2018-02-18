CC =g++
CFLAGS = -std=c++11 -Wall -g
BIN = main
SUBDIR = $(shell ls -d */)
ROOTSRC = $(wildcard *.cpp)
ROOTOBJ = $(ROOTSRC:%.cpp=%.o)
SUBSRC = $(shell find $(SUBDIR) - name '*.cpp')
SUBOBJ = $(SUBSRC:%.cpp=%.o)


$(BIN):$(ROOTOBJ) $(SUBOBJ)
    $(CC) $(CFLAGS) -o $(BIN) $(ROOTOBJ) $(SUBOBJ)

%o:%.cpp
    $(CC) $(CFLAGS) -c $< -0 $@

clean:
    rm -f $(BIN) $(ROOTOBJ) $(SUBOBJ)

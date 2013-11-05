CXX		= g++
CXXFLAGS= -g -Wall -pedantic
LFLAGS	=
OBJS	= NumbersTheoryTest.o NumbersTheory.o
TARGET	= NumbersTheoryTest.exe

$(TARGET) : $(OBJS)
	$(CXX) $(LFLAGS) $^ -o $@

NumbersTheoryTest.o: NumbersTheoryTest.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

NumbersTheory.o: NumbersTheory.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	del $(OBJS) $(TARGET)
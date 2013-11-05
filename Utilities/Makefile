CC      = g++
CFLAGS	= -Wall -pedantic

NumbersTheoryTest.exe: NumbersTheoryTest.o NumbersTheory.o
	$(CC) -o $@ $^

NumbersTheoryTest.o: NumbersTheoryTest.cpp
	$(CC) -c $(CFLAGS) $<
	
NumbersTheory.o: NumbersTheory.cpp
	$(CC) -c $(CFLAGS) $<

clean:
	del *.o NumbersTheoryTest.exe
objs = main.o DES.o functions.o keygen.o util.o

Program: $(objs)
	g++ -o DES.out $(objs)

main.o: DES.h main.cpp
	g++ -c main.cpp

DES.o: tables.h functions.h DES.h DES.cpp
	g++ -c DES.cpp

functions.o: util.h keygen.h tables.h functions.h functions.cpp
	g++ -c functions.cpp

keygen.o: tables.h util.h keygen.h keygen.cpp
	g++ -c keygen.cpp

util.o: util.h util.cpp
	g++ -c util.cpp

clean:
	rm $(objs)

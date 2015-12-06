#makefile

#normal flags
#compiler
CC = g++

#flags
CFLAGS =  -w -std=c++11 -fmax-errors=100

#normal libs
LIBS = -pthread

#compile project
all: bin/main.o
	rm -f log.txt
	$(CC) ./bin/*.o $(CFLAGS) -o ./release/geneticTraining $(LIBS)

clean:
	rm -r -f ./bin/
	mkdir bin
	rm -r -f ./release/
	mkdir release

bin/main.o: ./source/main.cpp genetic_core io_mananger libs
	$(CC) -c ./source/main.cpp $(CFLAGS) -o ./bin/main.o $(LIBS)

genetic_core: bin/GeneticCore.o bin/Specimen.o
io_mananger: bin/IOMananger.o bin/IOBasetypes.o bin/IOEntities.o
libs: bin/json.o

#GeneticCore
bin/GeneticCore.o: ./source/src/GeneticCore.cpp ./source/header/GeneticCore.hpp
	$(CC) -c ./source/src/GeneticCore.cpp $(CFLAGS) -o ./bin/GeneticCore.o $(LIBS)

bin/Specimen.o: ./source/src/Specimen.cpp ./source/header/Specimen.hpp
	$(CC) -c ./source/src/Specimen.cpp $(CFLAGS) -o ./bin/Specimen.o $(LIBS)

#IOMananger
bin/IOMananger.o: ./source/src/IOMananger.cpp ./source/header/IOMananger.hpp
	$(CC) -c ./source/src/IOMananger.cpp $(CFLAGS) -o ./bin/IOMananger.o $(LIBS)

bin/IOBasetypes.o: ./source/src/Output/BaseTypes.cpp ./source/header/Output/BaseTypes.hpp
	$(CC) -c ./source/src/Output/BaseTypes.cpp $(CFLAGS) -o ./bin/IOBasetypes.o $(LIBS)

bin/IOEntities.o: ./source/src/Output/Entities.cpp ./source/header/Output/Entities.hpp
	$(CC) -c ./source/src/Output/Entities.cpp $(CFLAGS) -o ./bin/IOEntities.o $(LIBS)

#LIBS
#compile json third-party lib
bin/json.o: ./source/libs/jsonParser/json.h ./source/libs/jsonParser/jsoncpp.cpp
	$(CC) -c ./source/libs/jsonParser/jsoncpp.cpp $(CFLAGS) -o ./bin/json.o


##############################################################
#Testes de execução autmatica
##############################################################
#test libs
LIB_TEST = -lcppunit

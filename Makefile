#our extremely very simple make file
#This makes sure that all lines have the_world
all: big_int_world

#this makes sure big_int_world depends on all the other files
big_int_world:  main.o big_int.o super_array.o addition.o multiplication.o subtraction.o division.o
	g++  main.o big_int.o super_array.o addition.o multiplication.o subtraction.o division.o -o big_int_world -std=c++11

#this builds main
main.o: main.cpp
	g++ -c main.cpp -std=c++11

big_int.o: big_int.cpp
	g++ -c big_int.cpp -std=c++11

super_array.o: super_array.cpp
	g++ -c super_array.cpp -std=c++11

addition.o: addition.cpp
	g++ -c addition.cpp -std=c++11

multiplication.o: multiplication.cpp
	g++ -c multiplication.cpp -std=c++11

subtraction.o: subtraction.cpp
	g++ -c subtraction.cpp -std=c++11

division.o: division.cpp
	g++ -c division.cpp -std=c++11

%: %.cc
	g++ -std=c++11 $< -o $@

%: %.c
	gcc $< -o $@

#this removes all the .o files as well as big_int_world
clean:
	rm *.o big_int_world
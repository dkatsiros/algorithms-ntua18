all:poleodomia particles second

poleodomia: poleodomia.o
	g++ -o poleodomia poleodomia.o
poleodomia.o: poleodomia.cpp
	g++ -c poleodomia.cpp


particles: particles.o
	g++ -o particles particles.o
particles.o: particles.cpp
	g++ -c particles.cpp

second: second.o
	g++ -o second second.o
second.o: second.cpp
	g++ -c second.cpp

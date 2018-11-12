all:poleodomia particles

poleodomia: poleodomia.o
	g++ -o poleodomia poleodomia.o
poleodomia.o: poleodomia.cpp
	g++ -c poleodomia.cpp


particles: particles.o
	g++ -o particles particles.o
particles.o: particles.cpp
	g++ -c particles.cpp

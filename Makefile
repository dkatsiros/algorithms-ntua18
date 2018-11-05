all:poleodomia

poleodomia: poleodomia.o
	g++ -o poleodomia poleodomia.o
poleodomia.o: poleodomia.cpp
	g++ -c poleodomia.cpp

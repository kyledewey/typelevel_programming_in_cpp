all: peano lists map exp
	echo all made

clean:
	rm peano lists map exp

peano: peano.h peano.cpp
	clang++ -std=c++11 peano.cpp -o peano

lists: peano.h lists.h lists.cpp
	clang++ -std=c++11 lists.cpp -o lists

map: map.h map.cpp
	clang++ -std=c++11 map.cpp -o map

exp: peano.h map.h exp.cpp
	clang++ -std=c++11 exp.cpp -o exp

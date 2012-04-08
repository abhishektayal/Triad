all: manager.o client.o sha1.o marshalling.o timers/timers.o timers/tools.o
	g++  -g  -lnsl -lsocket -lresolv -o projc client.o manager.o sha1.o marshalling.o timers/timers.o timers/tools.o 






sha1.o: sha1.c sha1.h
	g++ -c -g sha1.c
	
marshalling.o: marshalling.cpp marshalling.h timers/timers.cc timers/timers.hh timers/tools.cc timers/tools.hh
	g++ -c -g marshalling.cpp	
	

	
client.o: client.cpp sha1.c sha1.h marshalling.cpp marshalling.h 
	g++ -c -g client.cpp	
	
manager.o: manager.cpp manager.h client.cpp 
	g++ -c -g manager.cpp
		

clean:
	rm -rf *.o projb
	
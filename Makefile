ps3patcher: tmain.o pbase.o patcher.o
	g++ -o ps3patcher tmain.o pbase.o patcher.o
tmain.o: tmain.cc pbase.h
	cc -c tmain.cc -std=c++11
pbase.o: pbase.cc pbase.h
	cc -c pbase.cc -std=c++11
patcher.o: patcher.cc patcher.h pbase.h
	cc -c patcher.cc -std=c++11
clean:
	rm *.o

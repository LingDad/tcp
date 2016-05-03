server_main : tcp_server.o server_main.cpp
	g++ -g tcp_server.o server_main.cpp -o server_main

tcp_server.o : tcp_server.cpp tcp_server.h
	g++ -c tcp_server.cpp -o tcp_server.o

clean : 
	rm server_main tcp_server.o
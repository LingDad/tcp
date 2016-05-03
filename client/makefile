client_main : tcp_client.o client_main.cpp
	g++ -g tcp_client.o client_main.cpp -o client_main

tcp_client.o : tcp_client.cpp tcp_client.h
	g++ -c tcp_client.cpp -o tcp_client.o

clean : 
	rm client_main tcp_client.o
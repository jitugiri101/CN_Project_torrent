client: server_share_get.cpp gensha.h hdr_for_gen.h
	g++ -Wall -o tracker server_share_get.cpp gensha.cpp hdr_for_gen.cpp -lssl -lcrypto	
server: client_share_get.cpp gensha.h hdr_for_gen.h
	g++ -Wall -o client client_share_get.cpp genhsa.cpp hdr_for_gen.cpp -lssl -lcrypto
server2: tracker_2.cpp gensha.h hdr_for_gen.h
	g++ -Wall -o tracker2 tracker_2.cpp gensha.cpp hdr_for_gen.cpp -lssl -lcrypto

CC = g++
CFLAGS = -std=c++11


Led_StdOut: Led_Application.cpp
	$(CC) $(CFLAGS) $^ -o $@
	

clean:
	rm -f Led_StdOut



	




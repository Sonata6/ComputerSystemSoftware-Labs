cc = gcc

FLAGS = -c -W -Wall -Wextra -xc -std=c11 -ggdb -g3

all : main.o pharmacy.o
	$(cc) main.o pharmacy.o -o all
	    
main.o: main.c
	$(cc) $(FLAGS) main.c	  
		
pharmacy.o: pharmacy.c
	$(cc) $(FLAGS) pharmacy.c		
		
clean:
	rm -rf *.o hello		 

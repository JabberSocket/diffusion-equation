boil:
	gcc -Wall -g -I /usr/local/Cellar/argp-standalone/1.3/include -L /usr/local/Cellar/argp-standalone/1.3/lib -largp boil.c -o boil 

clean:
	rm boil simmer

# -*- Makefile -*-

run: hw2
	./hw2 syslog2500.log bubble
	./hw2 syslog2500.log merge
	./hw2 syslog2500.log quick
	./hw2 syslog5000.log bubble
	./hw2 syslog5000.log merge
	./hw2 syslog5000.log quick
	./hw2 syslog10k.log bubble
	./hw2 syslog10k.log merge
	./hw2 syslog10k.log quick
	./hw2 syslog20k.log bubble
	./hw2 syslog20k.log merge
	./hw2 syslog20k.log quick
	./hw2 syslog50k.log bubble
	./hw2 syslog50k.log merge
	./hw2 syslog50k.log quick
	./hw2 syslog200k.log merge
	./hw2 syslog200k.log quick
	./hw2 syslog1Ma.log merge
	./hw2 syslog1Mb.log merge
	./hw2 syslog1Mc.log merge
	./hw2 syslog1Mb.log quick
	./hw2 syslog200k.log bubble
	./hw2 syslog1Ma.log bubble
	./hw2 syslog1Ma.log quick
	./hw2 syslog1Mb.log bubble
	./hw2 syslog1Mc.log bubble
	./hw2 syslog1Mc.log quick
	

hw2: hw2.c
	gcc hw2.c -o hw2
	
clean:
	rm -f *.o hw2

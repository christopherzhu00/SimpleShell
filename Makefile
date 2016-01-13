OPTIMIZE = -O2

CC = gcc
CFLAGS = $(OPTIMIZE) -g

default: simpsh

simpsh: simpsh.c
	$(CC) $(CFLAGS) simpsh.c -o $@

check:
	test.sh
	
dist: $(DISTDIR).tar.gz

$(DISTDIR).tar.gz: $(DIST_SOURCES) check-dist
		rm -fr $(DISTDIR)
		tar -czf $@.tmp --transform='s,^,$(DISTDIR)/,' $(DIST_SOURCES)
		./check-dist $(DISTDIR)
		mv $@.tmp $@

clean:
	rm -f *.o simpsh
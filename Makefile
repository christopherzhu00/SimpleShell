OPTIMIZE = -O2

CC = gcc
CFLAGS = $(OPTIMIZE) -g -Wall -Wextra -Wno-unused
DIST_SOURCES = simpsh.c Makefile test.sh README check-dist
DISTDIR = lab1-ZacharyBordofskyChrisZhu

default: simpsh

simpsh: simpsh.c
	$(CC) $(CFLAGS) simpsh.c -o $@

check:
	./test.sh

dist: $(DISTDIR).tar.gz

$(DISTDIR).tar.gz: $(DIST_SOURCES) check-dist
		rm -fr $(DISTDIR)
		tar -czf $@.tmp --transform='s,^,$(DISTDIR)/,' $(DIST_SOURCES)
		./check-dist $(DISTDIR)
		mv $@.tmp $@

clean:
	rm -f *.tmp *~ *.o *.tar.gz simpsh
	rm -fr $(DISTDIR)
	
.PHONY: all dist check $(TEST_BASES) clean
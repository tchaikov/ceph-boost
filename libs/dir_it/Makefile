##
##  Raphael Bossek <bossekr@debian.org> for the Debian GNU/Linux distribution
##  $Id: Makefile,v 1.1 2002/02/16 22:12:36 steve Exp $

default: build

DIRIT_SONAME_VERSION = 1.21



archive:
	mkdir -p archive
	cd archive; unzip ../dir_it.zip; patch -p1 < ../dir_it.patch; chmod a+x configure

build:	archive
	cd archive; ./configure; $(MAKE)

clean:
	rm -rf archive

.PHONY: build install deinstall examples test clean

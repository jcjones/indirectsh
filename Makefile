all: indirectshd

indirectshd: 
	cd daemon; ${MAKE}

clean: 
	rm -f indirectshd
	cd daemon; ${MAKE} clean



all:
	gcc -fPIC -DPIC -shared -rdynamic -o pam_printpw.so pam_printpw.c

clean:
	rm -f *.so

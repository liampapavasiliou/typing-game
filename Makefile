build:
	gcc -o typetest -lcurses typetest.c
	sudo cp typetest /bin/typetest
run:
	make build
	./typetest 1

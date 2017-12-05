
solver = p.cpp
out = ./p.out
override CFLAGS += -o p.out -std=c++14 -I.

run: compile input.txt
	$(out) < input.txt
out_file: compile input.txt
	$(out) < input.txt > ans.txt

compile: $(solver)
	g++ $(CFLAGS) $(solver)

init: initc++.txt
	cat initc++.txt > p.cpp

gen:
	bash generate.sh p.cpp

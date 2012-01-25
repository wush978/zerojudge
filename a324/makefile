all : a324.exe

a324.exe : a324.cpp
	g++ a324.cpp -o a324.exe -g -O0
	
test : 
	./a324.exe < test-input.txt
	
clean :
	rm a324.exe

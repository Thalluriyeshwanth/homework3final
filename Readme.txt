Compile:

	make

Execute as:

	./search -S projects
	./search -f .c 3 projects
	./search -s 1024 projects
	./search -t d projects
	./search -t f projects
	./search -S -s 1024 -f .c 3 -t f projects
	./search -s 1024 -e "ls -l" projects
	./search -f docx 3 -E "tar cvf docx.tar" projects
	./search -s 1024 -f jpg 3 -e "wc -l" projects


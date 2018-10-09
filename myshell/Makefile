mssh:	shell.c ./tokenize/makeArgs.o ./utils/myUtils.o ./utils/fileUtils.o ./process/process.o ./pipes/pipes.o ./linkedlist/linkedList.o ./linkedlist/listUtils.o ./command/myCommand.o ./alias/myAlias.o
	gcc -g shell.c ./tokenize/makeArgs.o ./utils/myUtils.o ./utils/fileUtils.o ./process/process.o ./pipes/pipes.o ./linkedlist/linkedList.o ./linkedlist/listUtils.o ./command/myCommand.o ./alias/myAlias.o -o mssh

makeArgs.o:	./tokenize/makeArgs.c ./tokenize/makeArgs.h
	gcc -g -c ./tokenize/makeArgs.c

myUtils.o:	./utils/myUtils.o ./utils/myUtils.h
	gcc -g -c ./utils/myUtils.c

fileUtils.o:	./utils/fileUtils.c ./utils/fileUtils.h
	gcc -g -c ./utils/fileUtils.c

process.o:	./process/process.c ./process/process.h
	gcc -g -c ./process/process.c	

pipes.o:	./pipes/pipes.c ./pipes/pipes.h
	gcc -g -c ./pipes/pipes.c

linkedList.o:	./linkedlist/linkedList.c ./linkedlist/linkedList.h
	gcc -g -c ./linkedlist/linkedList.c

listUtils.o:	./linkedlist/listUtils.c ./linkedlist/listUtils.h
	gcc -g -c ./linkedlist/listUtils.c

myCommand.o:	./command/myCommand.c ./command/myCommand.h
	gcc -g -c ./command/myCommand.c

myAlias.o:	./alias/myAlias.c ./alias/myAlias.h
	gcc -g -c ./alias/myAlias.c

clean:
	rm ./pipes/pipes.o	
	rm ./utils/myUtils.o
	rm ./utils/fileUtils.o
	rm ./process/process.o
	rm ./tokenize/makeArgs.o
	rm ./linkedlist/linkedList.o
	rm ./linkedlist/listUtils.o
	rm ./command/myCommand.o
	rm ./alias/myAlias.o
	rm mssh


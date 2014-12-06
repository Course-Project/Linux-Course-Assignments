default: 2.fork 2.vfork 3.wait-block 3.wait-noblock 4.shell

2.fork: 2.fork.c
	gcc -o 2.fork 2.fork.c -std=gnu99

2.vfork: 2.vfork.c
	gcc -o 2.vfork 2.vfork.c -std=gnu99

3.wait-block: 3.wait-block.c
	gcc -o 3.wait-block 3.wait-block.c -std=gnu99

3.wait-noblock: 3.wait-noblock.c
	gcc -o 3.wait-noblock 3.wait-noblock.c -std=gnu99

4.shell: 4.shell.c
	gcc -o 4.shell 4.shell.c -std=gnu99

clean:
	rm 2.fork 2.vfork 3.wait-block 3.wait-noblock 4.shell
FILELIST = signal_handler signal_real_normal

default: $(FILELIST)

signal_handler: signal_handler.c
	gcc -o signal_handler signal_handler.c -std=gnu99

signal_real_normal: signal_real_normal.c
	gcc -o signal_real_normal signal_real_normal.c -std=gnu99

clean:
	rm $(FILELIST)
all_sources= main.c bmp.c gif.c
all_objs = $(all_sources:.c=.o)

my_project : $(all_objs)
	gcc -o my_project $^ -lm 

%.o : %.c format.h
	gcc -c $<

source_file.o:$(all_sources)
	gcc -c $^
clean :
	rm  my_project *.o


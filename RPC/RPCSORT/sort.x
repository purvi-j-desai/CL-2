#define MAX 25

struct input {
       float a[MAX];
};

struct output {
       float a[MAX];
};

program SORTPROG {
	version SORTVERSION {
		struct output sort(struct input) = 1;
	} = 1; 
} = 222222;
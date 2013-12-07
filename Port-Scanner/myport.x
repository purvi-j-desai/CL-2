struct input {
       char myhost[50];
       int start;
       int end;
};

struct output {
       int total;
       int openports[100];
};

program portscanner {
	version portver {
		struct output getstatus(struct input) = 1;
	} = 1;
} = 222222;
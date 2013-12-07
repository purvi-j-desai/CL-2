struct input {
       int m;
       int n;
};

program IDLE{
	version IDLEVERSION{
		float getusage() = 1;
		int add(struct input) = 2;
	} = 1;
} = 222222;
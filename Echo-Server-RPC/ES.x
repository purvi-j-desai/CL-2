struct input {
       char text[256];
};

program ES {
	version ESV {
		void serverprocess(struct input) = 1;
	} = 1;
} = 222222;
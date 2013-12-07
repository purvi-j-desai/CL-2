struct InputInfo {
	int a; 
	int b;
	int c;
};

struct OutputInfo {
	int result;
};

program TEST_PROGRAM {
	version TEST_VERSION {
		struct OutputInfo addnums(struct InputInfo) = 1;
	} = 1;
} = 22222222;

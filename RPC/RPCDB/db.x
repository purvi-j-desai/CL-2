struct rec {
       int rno;
       char name[50];
       int m;
};

program DBPROGRAM {
	version DBPROGVERSION {
		int insert(struct rec) = 1;
		int delete(struct rec) = 2;
		int update(struct rec) = 3;
		struct rec show(int rno) = 4;
	} = 4;
} = 22222222;
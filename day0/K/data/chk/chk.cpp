//You can include .h file like testlib.h here
#include <bits/stdc++.h>

#include "bigint.h"

using namespace NBigint;

FILE *inFile;
FILE *outFile;
FILE *ansFile;
FILE *scoreFile;
FILE *infoFile;
double score;
bool swap_flag;

void ret(double result, const char* info){
	if(swap_flag)
		fprintf(infoFile, "%s\n", info);	//Arbiter only allow to read EXACTLY one line info, no less and no more, and must BEFORE score
	fprintf(scoreFile, "%.6f\n", result * score);
	if(!swap_flag)
		fprintf(infoFile, "%s\n", info);
	exit(0);
}

int main(int argc, char **argv){
	// printf("argc %d\n", argc);
	//You'd better not change this swith block
	switch(argc){
		case 0:		//LOJ
			inFile = fopen("input", "r");
			outFile = fopen("user_out", "r");
			ansFile = fopen("answer", "r");
			scoreFile = stdout;
			infoFile = stderr;
			score = 100;
			break;
		case 4:		//Arbiter
			inFile = fopen(argv[1], "r");
			outFile = fopen(argv[2], "r");
			ansFile = fopen(argv[3], "r");
			scoreFile = infoFile = fopen("/tmp/_eval.score", "w");
			score = 10;
			swap_flag = true;
			break;
		case 5:
			if(strcmp(argv[4], "THUOJ") == 0){	//Tsinghua OJ(OJ for DSA course)
				inFile = fopen(argv[1], "r");
				outFile = fopen(argv[3], "r");
				ansFile = fopen(argv[2], "r");
				scoreFile = stdout;
				infoFile = stdout;
				score = 100;
			}else{								//Tsinsen OJ
				inFile = fopen(argv[1], "r");
				outFile = fopen(argv[2], "r");
				ansFile = fopen(argv[3], "r");
				scoreFile = fopen(argv[4], "w");
				infoFile = fopen("tmp", "w");		//Tsinsen doesn't use this file
				score = 1;
			}
			break;
		case 7:		//Lemon and TUOJ
			inFile = fopen(argv[1], "r");

			outFile = fopen(argv[2], "r");
			ansFile = fopen(argv[3], "r");
			FILE *fs = fopen(argv[4], "r");
			if(fs)
				fscanf(fs, "%lf", &score);		//Current TUOJ
			else
				sscanf(argv[4], "%lf", &score);	//Lemon and future TUOJ
			scoreFile = fopen(argv[5], "w");
			infoFile = fopen(argv[6], "w");
			break;
	}

	int T;
	fscanf(inFile, "%d", &T);
	// printf("%d\n", T);
	char out[MAXL + 10];

	for (int t = 1; t <= T; t++) {
		Bigint a, b, c, n;
		a.read(inFile);
		b.read(inFile);
		c.read(inFile);
		char out[MAXL + 10], ans[MAXL + 10];
		fgets(out, MAXL + 2, outFile);
		int out_len = strlen(out);
		if (out[out_len - 1] != '\n') ret(0, (string("invalid output at case ") + to_string(t)).c_str());
		out[--out_len] = 0;

		fscanf(ansFile, "%s", ans);
		if (strcmp(ans, "-1") == 0) {
			if (strcmp(out, "-1") != 0) ret(0, (string("wrong answer at case ") + to_string(t)).c_str());
			continue;
		}

		n.update(out, out_len);
		auto x = a * n + b;
		auto d = gcd(x, c);
		if (!d.is1()) ret(0, (string("wrong answer at case ") + to_string(t)).c_str());
	}
	ret(1, "accepted");
	return 0;
}

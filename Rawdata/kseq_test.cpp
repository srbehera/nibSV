#include <zlib.h>
#include <stdio.h>
#include "kseq.h"
KSEQ_INIT(gzFile, gzread)
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <fstream>
using namespace std;
#include <vector>

int main(int argc, char *argv[])
{
	gzFile fp;
	kseq_t *seq;
	int l;
        srand (time(NULL));
	if (argc == 1) {
		fprintf(stderr, "Usage: %s <in.seq>\n", argv[0]);
		return 1;
	}
        vector<string> VS;
	fp = gzopen(argv[1], "r");
	seq = kseq_init(fp);
	while ((l = kseq_read(seq)) >= 0) {
                string seqn(seq->seq.s);
                int len = seqn.length();
                int flag = 0;
                int count = 0;
                while(true){
                  count++;
                  if(len < 10000 || count == 100) break;
                  int rp = rand() % (len - 10000) + 1;
                  string subseq = seqn.substr(rp, 10000); 
                  if(subseq.find("N") == std::string::npos){
                    VS.push_back(subseq);
                    flag = 1;
                  }
                  if(flag == 1) break;
                }
                if(VS.size() == 5) break;
		//printf("seq: %s\n", seq->seq.s);
	}
        
	printf("return value: %d\n", l);
	kseq_destroy(seq);
	gzclose(fp);

        for(int i=0; i<VS.size(); i++){
          string fname = "testNib_seq_" + to_string(i) + ".fa";
          ofstream MyFile(fname);
          MyFile << VS.at(i);
          MyFile.close();          
        }
	return 0;
}

#ifndef H_GTUOS
#define H_GTUOS

#include <cmath>

#define MAX_ADDR pow(2,16)-1 /*max address*/

#define BYTE_LEN 16

#include "8080emuCPP.h"
#include <fstream>


class GTUOS{
	public:
		uint64_t handleCall(const CPU8080 & cpu, FILE* out);
                const int getCycles(void){return CycleCount;};
        private:
            int CycleCount;
};

#endif

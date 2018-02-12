#include <iostream>
#include "8080emuCPP.h"
#include "gtuos.h"

int main (int argc, char**argv)
{
    int additionalCycle = 0;
    FILE* output; /*open the file*/
    output = fopen("exe.mem", "w");
    
    if(output == NULL){
        std::cerr<<"File couldn't created!\n";
        exit(0);
    }
	if (argc != 3){
		std::cerr << "Usage: prog exeFile debugOption\n";
		exit(1); 
	}
	int DEBUG = atoi(argv[2]);

	CPU8080 theCPU;
	GTUOS	theOS;

	theCPU.ReadFileIntoMemoryAt(argv[1], 0x0000);	

        /*if debug is 2, wait for ENTER to show steps*/
        if(DEBUG == 2){
            do	
	{
                if(std::cin.get()){ /*take the ENTER from keyboard*/
		additionalCycle += theCPU.Emulate8080p(DEBUG);
		if(theCPU.isSystemCall()){
                    std::cout<<"System Call:";
			theOS.handleCall(theCPU, output);
                }
                }
	}	while (!theCPU.isHalted())
        ;
        
        }
        else{do	
	{
		additionalCycle += theCPU.Emulate8080p(DEBUG); /*add to the cycles*/
		if(theCPU.isSystemCall())
			theOS.handleCall(theCPU, output);
	}	while (!theCPU.isHalted())
        ;}
        /*Print out total number of cycles*/
        std::cout<<"\nTotal Number of Cycles : "<<theOS.getCycles()+additionalCycle<<std::endl;
        fclose(output); /**/
	return 0;
}


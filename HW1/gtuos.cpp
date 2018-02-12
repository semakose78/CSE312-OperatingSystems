#include <iostream>
#include "8080emuCPP.h"
#include "gtuos.h"
#include <iomanip>

uint64_t GTUOS::handleCall(const CPU8080 & cpu, FILE* out){
	//std::cout <<  "Unimplemented OS call";
	//throw -1;
        int key;
        std::string keyString;
        int i = (100*(cpu.state->b) + (cpu.state->c));
        int j=0;
        uint16_t addr = 0;
        CycleCount = 0;
        
        switch(cpu.state->a){
            /*if it's the PRINT_B call*/
            case 1 : 
                std::cout<<"PRINT_B\nValue of B "<<unsigned(cpu.state->b)<<std::endl;
                CycleCount = CycleCount+10;
            break;
            /*if it's the PRINT_MEM call*/
            case 2 :
                std::cout<<"PRINT_MEM\nContents of Memory\n";
                for(int k=0; k<unsigned(cpu.state->d)+1; ++k){
                    std::cout<<(unsigned int)cpu.memory[i]<<std::endl;
                    i=i+2;
                }
                CycleCount = CycleCount+10;
                break;
            /*if it's the READ_B call*/
            case 3 :
                std::cout<<"READ_B\n";
                std::cin>>key;
                cpu.state->b = key;
                CycleCount = CycleCount+10;
                break;
            /*if it's the READ_MEM call*/
            case 4:
                std::cout<<"READ_MEM\n";
                std::cin>>key;
                cpu.memory[i] = key;
                CycleCount = CycleCount+10;
                break;
            /*if it's the PRINT_STR call*/
            case 5:
                std::cout<<"PRINT_STR\nString from the Memory : ";
                while(((unsigned char)cpu.memory[i]) != '\0'){
                    std::cout<<(unsigned char)cpu.memory[i];
                    ++i;
                }
                std::cout<<"\n";
                i = (100*(cpu.state->b) + (cpu.state->c));
                CycleCount = CycleCount+100;
                break;
            /*if it's the READ_STR call*/
            case 6:
                
                std::cout<<"READ_STR\n";
                std::cin>>keyString;
                while(keyString[j] != '\0'){
                    cpu.memory[i] = keyString[j];
                    ++j;
                    ++i;
                }
                i = (100*(cpu.state->b) + (cpu.state->c));
                CycleCount = CycleCount+100;
                break;
        }
        /*Print all of the memory contents to the exe.mem*/
        i = 0;
        for(uint16_t k=0x0000; k<0xFFFF; ++k){
            fprintf(out, "%04hhx ", addr);
            for(int temp=0; temp<BYTE_LEN; ++temp){
                fprintf(out, "%.2hhx ", cpu.memory[i]);
                i=i+1;
                if(i>MAX_ADDR) /*break if i arrives to max address*/
                    break;
            }
            if(i>MAX_ADDR) /*break if i arrives to max address*/
                break;
        fprintf(out, "\n");
        addr = addr+BYTE_LEN; /*increment the address*/
        }
	return 0;
}

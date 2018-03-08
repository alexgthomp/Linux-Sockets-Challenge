#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<iostream>

using namespace std;

int getLine(char *inputbuffer, int startLocation);
void formatData(char *buffer, char *returnBuffer);

const int inputSize = 500;
const int allowedLineSize = 79;

int main (int argc, char *argv[]){
    
    
    int mainSocket, newSocket;
    struct sockaddr_in connectionAddr;
    char buffer[inputSize] = {0},  returnBuffer[inputSize*2] = {0};
    int addr_size = sizeof connectionAddr;
    

    //Socket Initilization
    connectionAddr.sin_family = AF_INET;
    connectionAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    connectionAddr.sin_port = htons(8080);
    memset(connectionAddr.sin_zero, '\0', sizeof connectionAddr.sin_zero);
    mainSocket = socket(AF_INET, SOCK_STREAM, 0);
    bind(mainSocket, (struct sockaddr *) &connectionAddr, sizeof(connectionAddr));
    
   //continually wait for clients
   while(1){
        listen(mainSocket,10);
        newSocket = accept(mainSocket, (struct sockaddr *) &connectionAddr, (socklen_t*) &addr_size);
        
        if(newSocket == -1){
            printf("Socket Connection Error");
            return 1;
        }

       recv(newSocket, buffer, inputSize, 0);
       
       formatData(buffer,returnBuffer);
       
       send(newSocket , returnBuffer , inputSize*2 , 0 );
       
       close(newSocket);
        
   }
    return 0;
}


void formatData(char *buffer, char *returnBuffer){
    int userIntputLength = string(buffer).length();
    int currentStartLocation = 0, currentEndLocation = 0, returnBufferLocation = 0, lineLength = 0;
    
    while(userIntputLength > currentEndLocation){
        
        currentStartLocation = currentEndLocation;
        
        if(getLine(buffer, currentStartLocation) > 0) //handles if word is longer than allowedLineSize or not
        {
            currentEndLocation = getLine(buffer, currentStartLocation); //gets location of last space
            lineLength = currentEndLocation-currentStartLocation; //calculats the length of new line
            strncpy(returnBuffer + returnBufferLocation, buffer+ currentStartLocation , lineLength); //copies line to returnBuffer
            returnBufferLocation = returnBufferLocation + lineLength;//updates current location of returnBuffer
            currentEndLocation += 1; //adjusts next line to start after space
        }
        else{
            //splits a word longer that allowedLineSize for next line
            currentEndLocation += allowedLineSize;
            strncpy(returnBuffer + returnBufferLocation, buffer+ currentStartLocation , allowedLineSize);
            returnBufferLocation = returnBufferLocation + allowedLineSize;
        }
        
        returnBuffer[returnBufferLocation] = '\n'; //adds line break after line
        returnBufferLocation += 1; //adjusts returnbufferlocation for next line
        
    }
}


//gets end location of last full word
int getLine(char *inputbuffer, int startLocation){
    int searchLocation = startLocation+allowedLineSize+1;
    int length = string(inputbuffer).length();
    if(length - startLocation < allowedLineSize){ //checks if the next line is longer than allowedLineSize
        return length+1;
    }
    
    while(startLocation < searchLocation){
        if(inputbuffer[searchLocation] == ' '){
            return searchLocation; //returns location of last space before allowedLineSize
        }
        searchLocation --;
        if(startLocation == searchLocation){ //returns -1 if word is longer than allowedLineSize
            return -1;
        }
    }
        
    return searchLocation;
}



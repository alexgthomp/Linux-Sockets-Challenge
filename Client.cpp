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

const int inputSize = 500;

int main (int argc, char *argv[]){
    
    struct sockaddr_in connectionAddr;
    char buffer[inputSize*2] = {0}, sendString[inputSize] = {0};
    int addr_size = sizeof connectionAddr;
    
    //gets input
    cout << "Input: ";
    cin.getline(sendString,inputSize+1);
    
    //Socket Initilization
    connectionAddr.sin_family = AF_INET;
    connectionAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    connectionAddr.sin_port = htons(8080);
    memset(connectionAddr.sin_zero, '\0', sizeof connectionAddr.sin_zero);
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    
    if(clientSocket == -1){
        printf("Socket Error");
        return 1;
    }
    if(connect(clientSocket, (struct sockaddr *) &connectionAddr, addr_size)){
        cout << "connection failed" << endl;
        return 1;
    }
    
    //perform Communication
    send(clientSocket , sendString , inputSize , 0 );
    recv(clientSocket, buffer, inputSize*2, 0);
    
    cout << "Output: " << endl;
    cout << buffer << endl;
    
    close(clientSocket);
    
}


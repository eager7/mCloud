#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h> //usleep
#include <time.h>
#include "block_server.h"

#define checkError(ret) do{if(-1==ret){printf("[%d]err:%s\n", __LINE__, strerror(errno));exit(1);}}while(0)

unsigned char auSendData[13] = {0};
	
int main(int argc, char const *argv[])
{
	printf("this is tcp demo\n");
    int iTime = 0;
	int iSocketFd = socket(AF_INET, SOCK_STREAM, 0);
	checkError(iSocketFd);

	int re = 1;
	checkError(setsockopt(iSocketFd, SOL_SOCKET, SO_REUSEADDR, &re, sizeof(re)));

	struct sockaddr_in server_addr;  
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;  
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);        /*receive any address*/
    server_addr.sin_port = htons(7878);
    checkError(bind(iSocketFd, (struct sockaddr*)&server_addr, sizeof(server_addr)));

    checkError(listen(iSocketFd, 5));

    int iSockClient;
	struct sockaddr_in client_addr;
	memset(&client_addr, 0, sizeof(client_addr));
	socklen_t client_len = sizeof(client_addr);

reconnect:
	iSockClient = accept(iSocketFd, (struct sockaddr*)&client_addr, &client_len);
	checkError(iSockClient);	
	printf("client ipaddr:%s\n", inet_ntoa(client_addr.sin_addr));

	const char *aSend = "This is tcp server";
	unsigned char aRecv[2048] = {0};	
    while(1)
    {
    	printf("wait client data...\n");
    	int irecv = (int)recv(iSockClient, aRecv, sizeof(aRecv), 0);
		if(-1 == irecv){
			printf("recv err:%s\n", strerror(errno));
			if(errno == EAGAIN){
				usleep(100);
				continue;
			} else {
				exit(1);
			}
		} else if (0 == irecv){
			printf("disconnect with client\n");
			close(iSockClient);
			goto reconnect;
		}
		printf("recv client ip:%s, data:", inet_ntoa(client_addr.sin_addr));
        for (int i = 0; i < irecv; ++i) {
            printf("0x%02x,", aRecv[i]);
        }printf("\n");
        uint16_t u16Command = (aRecv[4]<<8) | aRecv[5];
        u16Command = ntohs(u16Command);
        printf("Commnad:[%d]\n", u16Command);
        tuTimeSyncRequest uTimeSyncRequest = {0};
        tuTimeSyncResponse uTimeSyncResponse = {0};
        tuRFIDRequest uRFIDRequest = {0};
        tuRFIDResponse uRFIDResponse = {0};
        switch(u16Command){
            case E_GPRS_COMMAND_SYNC_TIME:
                printf("Receive Sync Time Command\n");
                memcpy(uTimeSyncRequest.auData, aRecv, sizeof(uTimeSyncRequest.auData));
                iTime = (int)time((time_t*)NULL);
                memcpy(&uTimeSyncResponse.sMessage.u32Time, &iTime, sizeof(iTime));
                uTimeSyncResponse.sMessage.u16Command = uTimeSyncRequest.sMessage.u16Command;
                uTimeSyncResponse.sMessage.u8Length = 1;
                checkError(send(iSockClient, uTimeSyncResponse.auData, sizeof(uTimeSyncResponse.auData), 0));
                break;
            case E_GPRS_COMMAND_RFID_REQUEST:
                printf("Receive RFID Request Command\n");
                memcpy(uRFIDRequest.auData, aRecv, sizeof(uRFIDRequest.auData));
                printf("RFID ID:0x%02x-0x%02x-0x%02x-0x%02x-0x%02x-0x%02x-0x%02x-0x%02x\n",
                uRFIDRequest.sMessage.auRFIDCode[0],uRFIDRequest.sMessage.auRFIDCode[1],
                       uRFIDRequest.sMessage.auRFIDCode[2],uRFIDRequest.sMessage.auRFIDCode[3],
                       uRFIDRequest.sMessage.auRFIDCode[4],uRFIDRequest.sMessage.auRFIDCode[5],
                       uRFIDRequest.sMessage.auRFIDCode[6],uRFIDRequest.sMessage.auRFIDCode[7]);
                iTime = (int)time((time_t*)NULL);
                memcpy(&uRFIDResponse.sMessage.u32Time, &iTime, sizeof(iTime));
                uRFIDResponse.sMessage.u16Command = E_GPRS_COMMAND_RFID_RESPONSE;
                uRFIDResponse.sMessage.u8Length = 1;
                uRFIDResponse.sMessage.u32Balance = ntohs(550);
                checkError(send(iSockClient, uRFIDResponse.auData, sizeof(uRFIDResponse.auData), 0));
                break;
            default:
                break;
        }

		sleep(1);
    }

	return 0;
}

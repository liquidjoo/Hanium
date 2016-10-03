#include<stdio.h>

#include<string.h>    //strlen

#include<sys/socket.h>

#include<arpa/inet.h> //inet_addr

#include<stdlib.h>

#include<time.h>

#include<unistd.h>

#include<signal.h>


int main(int argc , char *argv[])

{
    signal(SIGPIPE,SIG_IGN);
    
    int socket_desc;
    struct sockaddr_in server;
    char *message , server_reply[6000];
    int red=0, green=0, blue=0;
    int i, j;
    char* search_point;
    char cmd[100];
    FILE *fp;
    char buff[1024];
    char res[8];
    struct tm *clock;
    time_t current;
    int time_ary[8];
    int power_switch = 0, status = 0;
    int green_cmp = 1;
    int day=0, hour=0, min=0, sec=0;
    char string[100] =  "\"r\":\"153\",\"g\":\"10\",\"b\":\"176\"";
    char string2[100] = "\"r\":\"0\",\"g\":\"130\",\"b\":\"153\"";
    char string3[100] = "\"r\":\"204\",\"g\":\"114\",\"b\":\"61\"";
    char string4[100] = "\"r\":\"63\",\"g\":\"0\",\"b\":\"153\"";
    char string5[100] = "\"r\":\"0\",\"g\":\"51\",\"b\":\"153\"";
    char string6[100] = "\"r\":\"186\",\"g\":\"148\",\"b\":\"43\"";
    char string7[100] = "\"r\":\"34\",\"g\":\"116\",\"b\":\"28\"";
    char string8[100] = "\"r\":\"170\",\"g\":\"18\",\"b\":\"18\"";
    
    while(1){
        //socket setting
        socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        
        if (socket_desc == -1)
        {
            printf("Could not create socket");
        }
        
        //socket connect
        server.sin_addr.s_addr = inet_addr("14.63.197.34");
        server.sin_family = AF_INET;
        server.sin_port = htons( 80 );
        
        message = "GET /led1 HTTP/1.1\r\nHost: 14.63.197.34\r\n\r\n";
        
        if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
        {
            puts("connect error");
            return 1;
        }
        
        sleep(1);
        printf("socket %d\n", socket_desc);
        if(send(socket_desc , message , strlen(message) , 0) < 0)
        {
            puts("Send failed");
            return 1;
        }
        
        //Receive a reply from the server
        if( recv(socket_desc, server_reply , 6000 , 0) < 0)
        {
            puts("recv failed");
        }
        
        puts("Reply received\n");
        
        puts(server_reply); //Print
        
        search_point = strstr(server_reply, "[{");
        
        
        current = time(NULL);
        clock=localtime(&current);
        printf("%d %d %d\n", clock->tm_hour, clock->tm_min, clock->tm_sec);
        
        
        for(i=0;search_point[i]!='\0';i++){
            
            //Red
            if(search_point[i] == 'r'){
                i+=4;
                for(;(search_point[i] >= '0') && (search_point[i] <='9');i++){
                    red = red*10 + (search_point[i]-'0');
                }
            }
            
            //Green
            if(search_point[i] == 'g'){
                i+=4;
                for(;(search_point[i] >= '0') && (search_point[i] <= '9') ; i++){
                    green = green*10 + (search_point[i]-'0');
                }
            }
            
            //Blue
            if(search_point[i] == 'b'){
                i+=4;
                for(;(search_point[i] >= '0') && (search_point[i] <= '9') ; i++){
                    blue = blue*10 + (search_point[i]-'0');
                }
            }
            
            
            //time
            if(search_point[i] == 'm'){
                i+=5;
                j=0;
                for(;(search_point[i] >= '0') && (search_point[i] <= '9') ; i++){
                    time_ary[j++] = search_point[i]-'0';
                }
            }
            
            //power
            if(search_point[i] == 'w'){
                i+=6;
                power_switch = search_point[i] - '0';
            }
        }
        
        
        if((power_switch ^ status >= 1) || (green_cmp ^ green != 0)){
            
            day = time_ary[0]*10 + time_ary[1];
            hour = time_ary[2]*10 + time_ary[3];
            min = time_ary[4]*10 + time_ary[5];
            sec = time_ary[6]*10 + time_ary[7];
            green_cmp = green;
            printf("xor check point\n");
            
            if((day == clock->tm_mday) && (hour == clock->tm_hour) && (min == clock->tm_min)){
                //초의 오차
                if(sec+5 >= clock->tm_sec){
                    
                    printf("time check point\n");
                    //0
                    if(power_switch == 0){
                        status = power_switch;
                        
                        sprintf(cmd, "/var/coap-client -e \"0\" -m put coap://202.30.32.119/light");
                        fp = popen(cmd, "r");
                        fgets(buff, 256, fp);
                        fgets(res, 8, fp);
                        if (strncmp(res, "0", 1) == 0) system("sudo /var/test 0");
                        pclose(fp);
                        
                    }
                    
                    //sprintf(color_search_string, "\"r\":\"%d\",\"g\":\"%d\",\"b\":\"%d\"", red, green, blue);
                    
                    else if(power_switch == 1){
                        printf("switch check point\n");
                        status = power_switch;
                        
                        //1
                        if ((strstr(server_reply, string))!= NULL) {
                            sprintf(cmd, "/var/coap-client -e \"1\" -m put coap://202.30.32.119/light");
                            fp = popen(cmd, "r");
                            fgets(buff, 256, fp);
                            fgets(res, 8, fp);
                            if (strncmp(res, "1", 1) == 0) {
                                system("sudo /var/test 1");
                            }
                            pclose(fp);
                        }
                        
                        //2
                        else if ((strstr(server_reply, string2))!= NULL) {
                            sprintf(cmd, "/var/coap-client -e \"2\" -m put coap://202.30.32.119/light");
                            fp = popen(cmd, "r");
                            fgets(buff, 256, fp);
                            fgets(res, 8, fp);
                            if (strncmp(res, "2", 1) == 0) {
                                system("sudo /var/test 2");
                            }
                            pclose(fp);
                        }
                        
                        //3
                        else if ((strstr(server_reply, string3))!= NULL) {
                            sprintf(cmd, "/var/coap-client -e \"3\" -m put coap://202.30.32.119/light");
                            fp = popen(cmd, "r");
                            fgets(buff, 256, fp);
                            fgets(res, 8, fp);
                            if (strncmp(res, "3", 1) == 0) {
                                system("sudo /var/test 3");
                            }
                            pclose(fp);
                        }
                        
                        //4
                        else if ((strstr(server_reply, string4))!= NULL) {
                            sprintf(cmd, "/var/coap-client -e \"4\" -m put coap://202.30.32.119/light");
                            fp = popen(cmd, "r");
                            fgets(buff, 256, fp);
                            fgets(res, 8, fp);
                            if (strncmp(res, "4", 1) == 0) {
                                system("sudo /var/test 4");
                            }
                            pclose(fp);
                        }
                        
                        //5
                        else if ((strstr(server_reply, string5))!= NULL) {
                            sprintf(cmd, "/var/coap-client -e \"5\" -m put coap://202.30.32.119/light");
                            fp = popen(cmd, "r");
                            fgets(buff, 256, fp);
                            fgets(res, 8, fp);
                            if (strncmp(res, "5", 1) == 0) {
                                system("sudo /var/test 5");
                            }
                            pclose(fp);
                        }
                        
                        //6
                        else if ((strstr(server_reply, string6))!= NULL) {
                            sprintf(cmd, "/var/coap-client -e \"6\" -m put coap://202.30.32.119/light");
                            fp = popen(cmd, "r");
                            fgets(buff, 256, fp);
                            fgets(res, 8, fp);
                            if (strncmp(res, "6", 1) == 0) {
                                system("sudo /var/test 6");
                            }
                            pclose(fp);
                        }
                        
                        //7
                        else if ((strstr(server_reply, string7))!= NULL) {
                            sprintf(cmd, "/var/coap-client -e \"7\" -m put coap://202.30.32.119/light");
                            fp = popen(cmd, "r");
                            fgets(buff, 256, fp);
                            fgets(res, 8, fp);
                            if (strncmp(res, "7", 1) == 0) {
                                system("sudo /var/test 7");
                            }
                            pclose(fp);
                        }
                        
                        //8
                        else if ((strstr(server_reply, string8))!= NULL) {
                            sprintf(cmd, "/var/coap-client -e \"8\" -m put coap://202.30.32.119/light");
                            fp = popen(cmd, "r");
                            fgets(buff, 256, fp);
                            fgets(res, 8, fp);
                            if (strncmp(res, "8", 1) == 0) {
                                system("sudo /var/test 8");
                            }
                            pclose(fp);
                        }
                    }//if switch test
                    
                } //sec check
            } //time check
        }//xor check
        
        //else if((power_switch ^ status == 0) || (green_cmp ^ green == 0)){
        //printf("continue exe\n");
        //continue;
        //}
        
        puts("final_test");
        close(socket_desc);
    }//send while
    
    return 0;
}
//disclimer
//expecting every request from client(web browser) will be only http request for html file and we r supposed to only send http response and html file
//basically in this program we r only going to send html file
//this program is only for ipv4 connection (cause web browser http req r of ipv4 type)

//restrictions ->
//doesn't shows new connected client address name (impliment it)✅

//features ->
//server is multithreaded so it can handle multiple client simulteneously
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>   //for close,read, write

#define PORT 8080
#define BUFFER_SIZE 1024

void send_html(int client_sockfd,const char *file_path) {
    FILE *html_file = fopen(file_path,"r");
    if(html_file==NULL) {
        printf("error opening html file\n");
        return;
    }
    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    char *http_header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";  //to inform browser about our response and upcoming file
    if(send(client_sockfd,http_header,strlen(http_header),0)==-1){
        perror("http_header send error ");
        fclose(html_file);
        return;
    }

    while((bytes_read=fread(buffer,1,BUFFER_SIZE,html_file))>0) {
        if(send(client_sockfd,buffer,bytes_read,0)==-1) {
            perror("send error while sending html file ");
            fclose(html_file);
            return;
        }
    }
    fclose(html_file);
    printf("html file send successfully to client\n");
}

int main() {
    int serv_sockfd , client_sockfd;
    struct sockaddr_in serv_addr,client_addr; 
    //struct sockaddr_storage c_addr;
    socklen_t client_len = sizeof(client_addr);

    memset(&serv_addr,0,sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    if((serv_sockfd = socket(AF_INET,SOCK_STREAM,0))==-1) {
        perror("socket error ");
        exit(EXIT_FAILURE);
    }

    printf("socket creation successful\n");

    if(bind(serv_sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0) {
        perror("bind error ");
        close(serv_sockfd);
        exit(EXIT_FAILURE);
    }

    printf("bind to port 8080 successfull\n");

    if(listen(serv_sockfd,5)==-1) {
        perror("listen error ");
        close(serv_sockfd);
        exit(EXIT_FAILURE);
    }

    printf("server is listening to port 8080....\n\n");
    printf("//server is multithreaded means it can handle multiple client simultaneously\n");

    while(1) {
        if((client_sockfd=accept(serv_sockfd,(struct sockaddr *)&client_addr,&client_len))==-1) {
            perror("accept error ");
            close(serv_sockfd);
            continue;
        }
        char c_addr[BUFFER_SIZE];
        inet_ntop(client_addr.sin_family,&client_addr.sin_addr.s_addr,c_addr,sizeof(c_addr));

        printf("client(%s) connected\n",c_addr);
        //printf("connection type of new client : %d\n",c_addr.ss_family);

        if(fork()==0) {
            close(serv_sockfd);
            send_html(client_sockfd,"index.html");
            close(client_sockfd);
            printf("client disconnected\n");
            exit(EXIT_SUCCESS);
        }
        close(client_sockfd);
    }

}
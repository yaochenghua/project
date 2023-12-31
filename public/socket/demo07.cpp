/*
 * @Description: demo07.cpp，此程序用于演示socket通讯的客户端。每次客户端向服务端发送一个报文，再等待服务端的回应
 * @Version: v4.0
 * @Autor: lele
 * @Date: 2023-08-07 10:52:31
 * @LastEditors: lele
 * @LastEditTime: 2023-08-07 10:52:32
 */


#include "../_public.h"
 
int main(int argc,char *argv[])
{
  if (argc!=3)
  {
    printf("Using:./demo07 ip port\nExample:./demo07 127.0.0.1 5005\n\n"); return -1;
  }

  CTcpClient TcpClient;

  // 向服务端发起连接请求。
  if (TcpClient.ConnectToServer(argv[1],atoi(argv[2]))==false)
  {
    printf("TcpClient.ConnectToServer(%s,%s) failed.\n",argv[1],argv[2]); return -1;
  }

  char buffer[102400];
 
  // 与服务端通讯，发送一个报文后等待回复，然后再发下一个报文。
  for (int ii=0;ii<100000;ii++)
  {
    SPRINTF(buffer,sizeof(buffer),"这是第%d个超级女生，编号%03d。",ii+1,ii+1);
    if (TcpClient.Write(buffer)==false) break; // 向服务端发送请求报文。
    printf("发送：%s\n",buffer);

    memset(buffer,0,sizeof(buffer));
    if (TcpClient.Read(buffer)==false) break; // 接收服务端的回应报文。
    printf("接收：%s\n",buffer);

    sleep(1);  // 每隔一秒后再次发送报文。
  }
}


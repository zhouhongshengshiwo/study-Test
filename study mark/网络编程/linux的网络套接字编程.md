# server
```c++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8081

#define BUFFER_SIZE 1024

int main() {
    // 主函数，启动服务器并处理客户端连接
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    //创建套接字
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 设置套接字选项
//SO_REUSEADDR选项允许你在服务器重启后立即重新绑定到相同的地址和端口，而不是等待操作系统释放该地址。这对于开发和调试服务器程序非常有用，因为它可以避免因为“地址已被使用”而无法重新启动服务器的情况
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // 设置地址类型
    address.sin_family = AF_INET;//设置地址族为IPv4。
    address.sin_addr.s_addr = INADDR_ANY;//设置IP地址为任何地址，这表示服务器可以接受任何网络接口的连接请求
    address.sin_port = htons(PORT);
    // 绑定套接字到地址

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);

    }
    // 开始监听
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("服务器正在运行，等待连接...\n");
    // 接受客户端连接
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    // 主循环，处理客户端请求
    while (1) {
        memset(buffer, 0, BUFFER_SIZE);
        int valread = read(new_socket, buffer, BUFFER_SIZE);
        if (valread == 0) {
            printf("客户端已关闭连接\n");
            break;
        }
        printf("收到消息: %s\n", buffer);
        send(new_socket, buffer, strlen(buffer), 0);
        printf("已发送回显: %s\n", buffer);

    }
    // 关闭套接字
    close(new_socket);
    close(server_fd);
    return 0;

}
```
client
```c++
#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <arpa/inet.h>



#define PORT 8081

#define BUFFER_SIZE 1024



int main() {

    int sock = 0;

    struct sockaddr_in serv_addr;

    char buffer[BUFFER_SIZE] = {0};



    // 创建套接字

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {

        printf("\n 错误: 套接字未能创建 \n");

        return -1;

    }



    serv_addr.sin_family = AF_INET;

    serv_addr.sin_port = htons(PORT);



    // 将IPv4地址从文本转换为二进制

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {

        printf("\n 错误: 无效的地址/地址不支持 \n");

        return -1;

    }



    // 连接到服务器

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {

        printf("\n 连接失败 \n");

        return -1;

    }



    // 主循环，发送消息并接收回显

    while (1) {

        printf("请输入消息 (输入 'exit' 结束): ");

        fgets(buffer, BUFFER_SIZE, stdin);



        // 如果输入 exit，就退出

        if (strncmp(buffer, "exit", 4) == 0) {

            break;

        }



        send(sock, buffer, strlen(buffer), 0);

        printf("已发送: %s", buffer);



        // 接收回显

        int valread = read(sock, buffer, BUFFER_SIZE);

        buffer[valread] = '\0'; // 确保字符串结束

        printf("收到回显: %s", buffer);

    }



    // 关闭套接字

    close(sock);

    return 0;

}

```
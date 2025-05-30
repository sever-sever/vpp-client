#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCK_PATH "/run/vpp/cli.sock"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command1> [command2] ...\n", argv[0]);
        return 1;
    }

    int sock;
    struct sockaddr_un addr;
    char buffer[4096];
    ssize_t bytes;

    // Create socket
    if ((sock = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return 1;
    }

    // Setup address
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path) - 1);

    if (connect(sock, (struct sockaddr*)&addr, sizeof(struct sockaddr_un)) == -1) {
        perror("connect");
        close(sock);
        return 1;
    }

    // Build the command string with newline-separated commands
    for (int i = 1; i < argc; i++) {
        if (write(sock, argv[i], strlen(argv[i])) == -1) {
            perror("write");
            close(sock);
            return 1;
        }
        if (write(sock, "\n", 1) == -1) {
            perror("write");
            close(sock);
            return 1;
        }
    }

    // Optionally send 'quit' to close session and get EOF
    write(sock, "quit\n", 5);

    // Read output
    while ((bytes = read(sock, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes] = '\0';
        printf("%s", buffer);
    }

    close(sock);
    return 0;
}

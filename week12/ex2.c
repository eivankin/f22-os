#include <linux/input.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


#define FILE_PATH   "/dev/input/by-path/platform-i8042-serio-0-event-kbd" // does not work on my machine, I used "/dev/input/by-path/pci-0000:05:00.4-usb-0:4:1.0-event-kbd"
#define PRESSED     1
#define RELEASED    0

int main() {
    struct input_event event;
    int fd = open(FILE_PATH, O_RDONLY);

    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    while (1) {
        int res = read(fd, &event, sizeof(event));
        if (res == -1) {
            perror("read");
            return EXIT_FAILURE;
        }

        if (event.type == EV_KEY) {
            if (event.value == PRESSED) {
                printf("PRESSED 0x%x (%d)\n", event.code, event.code);
            } else if (event.value == RELEASED) {
                printf("RELEASED 0x%x (%d)\n", event.code, event.code);
            }
        }
    }
}
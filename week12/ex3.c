#include <linux/input.h>
#include <linux/input-event-codes.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

// does not work on my machine, I used "/dev/input/by-path/pci-0000:05:00.4-usb-0:4:1.0-event-kbd"
#define FILE_PATH   "/dev/input/by-path/platform-i8042-serio-0-event-kbd"

// event types
#define RELEASED    0
#define PRESSED     1
#define REPEATED    2

// shortcuts
#define PE_OUT      "I passed the Exam!"
#define CAP_OUT     "Get some cappuccino!"
#define RND_OUT     "Your random number is: 42"

const char* SHORTCUTS[] = {PE_OUT, CAP_OUT, RND_OUT};

#define SHORTCUT_DESC "Shortcuts:\nP+E:\t'"PE_OUT"'\nC+A+P:\t'"CAP_OUT"'\nR+N+D:\t'"RND_OUT"'\n"

// shortcut keys
#define MAX_SEQ_LEN     3
#define SHORTCUT_COUNT  3
#define NO_KEY          -1

const int SHORTCUT_KEYS[SHORTCUT_COUNT][MAX_SEQ_LEN] = {
        {KEY_P, KEY_E, NO_KEY},
        {KEY_C, KEY_A, KEY_P},
        {KEY_R, KEY_N, KEY_D}
};


void clear_buff(int buff[]) {
    for (int i = 0; i < MAX_SEQ_LEN; ++i) {
        buff[i] = NO_KEY;
    }
}

int main() {
    struct input_event event;
    printf(SHORTCUT_DESC);

    int buff[MAX_SEQ_LEN], buff_pos = 0;
    clear_buff(buff);

    int fd = open(FILE_PATH, O_RDONLY);

    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }
    int last_match = -1;

    while (1) {
        int res = read(fd, &event, sizeof(event));
        if (res == -1) {
            perror("read");
            return EXIT_FAILURE;
        }

        if (event.type == EV_KEY) {
            if (event.value == RELEASED) {
                last_match = -1;
                clear_buff(buff);
                buff_pos = 0;
            } else if (event.value == PRESSED) {
                buff[buff_pos] = event.code;

                for (int s = 0; s < SHORTCUT_COUNT; ++s) {

                    int num_matches = 0;
                    for (int i = 0; i < MAX_SEQ_LEN; ++i) {
                        for (int j = 0; j < MAX_SEQ_LEN; ++j) {
                            if (SHORTCUT_KEYS[s][i] == buff[j]) {
                                ++num_matches;
                                break;
                            }
                        }
                    }

                    if (num_matches == MAX_SEQ_LEN) {
                        last_match = s;
                        printf("%s\n", SHORTCUTS[s]);
                        break;
                    } else {
                        last_match = -1;
                    }
                }

                buff_pos = (buff_pos + 1) % MAX_SEQ_LEN;
            } else if (event.value == REPEATED && last_match != -1) {
                printf("%s\n", SHORTCUTS[last_match]);
            }
        }
    }
}
#include <stdio.h>
#include <stdlib.h>

#define COL_WIDTH 10
#define NUM_OF_HEADERS 6

typedef struct {
    unsigned arrival_time; // AT
    unsigned burst_time; // BT
    unsigned completion_time; // CT
    // TAT = CT - AT
    // WT = TAT - BT
} Process;


void input_number(unsigned *a) {
    if (scanf("%ud", a) < 1) {
        printf("Failed to read or parse the number");
        exit(EXIT_FAILURE);
    }
}

void read_process_data(Process *p, int i) {
    printf("AT & BT #%d: ", i);
    input_number(&p->arrival_time);
    input_number(&p->burst_time);
    if (p->burst_time < 1) {
        printf("Burst time should be greater then zero\n");
        exit(EXIT_FAILURE);
    }
}

void print_processes(Process *processes, int size) {
    printf("\n");
    char headers[NUM_OF_HEADERS][COL_WIDTH] = {
            "P[i]",
            "AT",
            "BT",
            "CT",
            "TAT",
            "WT"
    };
    for (int i = 0; i < NUM_OF_HEADERS; ++i) {
        printf("%-*s", COL_WIDTH, headers[i]);
    }
    printf("\n");

    double total_TAT = 0;
    double total_WT = 0;
    for (int i = 0; i < size; ++i) {
        Process p = processes[i];
        char p_s[COL_WIDTH];
        sprintf(p_s, "P%d", i);
        printf("%-*s", COL_WIDTH, p_s);
        printf("%-*d", COL_WIDTH, p.arrival_time);
        printf("%-*d", COL_WIDTH, p.burst_time);
        printf("%-*d", COL_WIDTH, p.completion_time);
        int TAT = p.completion_time - p.arrival_time;
        printf("%-*d", COL_WIDTH, TAT);
        total_TAT += TAT;
        int WT = TAT - p.burst_time;
        printf("%-*d\n", COL_WIDTH, WT);
        total_WT += WT;
    }
    printf("Average Turnaround Time = %g\n", total_TAT / size);
    printf("Average Waiting Time = %g\n", total_WT / size);
}

int compare_by_arrival_then_burst(const void *elem1, const void *elem2) {
    int a1 = ((Process *) elem1)->arrival_time;
    int a2 = ((Process *) elem2)->arrival_time;
    if (a1 > a2) return 1;
    if (a1 < a2) return -1;

    int b1 = ((Process *) elem1)->burst_time;
    int b2 = ((Process *) elem2)->burst_time;
    if (b1 > b2) return 1;
    if (b1 < b2) return -1;
    return 0;
}

void sjf(Process *processes, int num_of_processes) {
    // Sort processes by arrival time, and then by burst time
    qsort(processes, num_of_processes, sizeof(Process), compare_by_arrival_then_burst);

    int current_time = 0;
    for (int i = 0; i < num_of_processes; ++i) {
        Process *p = &processes[i];
        if (p->arrival_time > current_time) {
            // Wait for process to arrive
            current_time = p->arrival_time;
        }
        // Run process
        current_time += p->burst_time;
        p->completion_time = current_time;
        // Go to next process in queue
    }
}

int main() {
    unsigned num_of_processes;
    printf("Enter the number of processes: ");
    input_number(&num_of_processes);
    Process *processes = malloc(sizeof(Process) * num_of_processes);
    for (int i = 0; i < num_of_processes; ++i) {
        read_process_data(&processes[i], i);
    }
    sjf(processes, num_of_processes);
    print_processes(processes, num_of_processes);
    free(processes);
    return EXIT_SUCCESS;
}
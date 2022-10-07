#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define COL_WIDTH 10
#define NUM_OF_HEADERS 6

typedef struct {
    unsigned arrival_time; // AT
    unsigned burst_time; // BT
    unsigned completion_time; // CT
    // TAT = CT - AT
    // WT = TAT - BT

    unsigned running_time;
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

int compare_by_arrival(const Process *elem1, const Process *elem2) {
    int a1 = elem1->arrival_time;
    int a2 = elem2->arrival_time;
    if (a1 > a2) return 1;
    if (a1 < a2) return -1;
    return 0;
}

void robin(Process *processes, int num_of_processes, int quantum) {
    // Sort processes by arrival time
    qsort(processes, num_of_processes, sizeof(Process), (__compar_fn_t) compare_by_arrival);

    int current_time = processes[0].arrival_time;
    int num_of_complete_processes = 0;
    int skip_flag = 0;
    while (num_of_complete_processes != num_of_processes) {
        for (int i = 0; i < num_of_processes; ++i) {
            Process *p = &processes[i];
            if (p->completion_time != UINT_MAX) {
                // process completed
                continue;
            }
            int time_to_run = 0;
            if (p->arrival_time <= current_time ||
                // if there are no processes arrived yet, then skip to the next
                (skip_flag && (current_time = p->arrival_time) != 0)) {
                // Run process for the max of quantum
                if (quantum + p->running_time < p->burst_time) {
                    // Will not be complete after quantum
                    time_to_run = quantum;
                    current_time += time_to_run;
                    p->running_time += time_to_run;
                } else {
                    // Complete now
                    time_to_run = p->burst_time - p->running_time;
                    current_time += time_to_run;
                    p->running_time += time_to_run;
                    p->completion_time = current_time;
                    num_of_complete_processes++;
                }
            }
            if (time_to_run == 0) {
                skip_flag = 1;
            } else {
                skip_flag = 0;
            }
            // Go to next process in queue
        }
        // No new processes, start queue from beginning
    }
}

int main() {
    unsigned num_of_processes, quantum;
    printf("Enter the quantum: ");
    input_number(&quantum);
    printf("Enter the number of processes: ");
    input_number(&num_of_processes);
    Process *processes = malloc(sizeof(Process) * num_of_processes);
    for (int i = 0; i < num_of_processes; ++i) {
        read_process_data(&processes[i], i);
        processes[i].completion_time = UINT_MAX;
        processes[i].running_time = 0;
    }
    robin(processes, num_of_processes, quantum);
    print_processes(processes, num_of_processes);
    free(processes);
    return EXIT_SUCCESS;
}

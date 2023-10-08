#include <stdio.h>
#define SIZE 1000

typedef struct process {
    int pid;
    int wtime;
    int tatime;
    int btime;
    int arrtime;
    int comptime;
    int btime1;
    struct process* next;
} process;

process* head, * tail;

void sort(process* p, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (p[j].arrtime > p[j + 1].arrtime) {
                process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

int isempty() {
    return (!head);
}

void enqueue(process* p) {
    if (!head) {
        head = tail = p;
        return;
    }
    tail->next = p;
    tail = tail->next;
}

process* dequeue() {
    if (!head) {
        return NULL;
    }
    process* temp = head;
    if (head == tail) {
        head = tail = NULL;
    }
    else {
        head = head->next;
    }

    temp->next = NULL;
    return temp;
}

void rr(process* p, int n, int t) {
    // lower priority no highest priority
    sort(p, n);
    int time = p[0].arrtime;
    int cp = 0;
    while (cp < n || !isempty()) {
        while (cp < n && p[cp].arrtime <= time) {
            enqueue(&p[cp++]);
        }
        process* temp = dequeue();
        int ta = (temp->btime1 >= t) ? t : temp->btime1;
        temp->btime1 -= ta;
        time += ta;
        if (temp->btime1 <= 0) {
            temp->comptime = time;
            temp->wtime = time - temp->btime - temp->arrtime;
            temp->tatime = time - temp->arrtime;
            while (cp < n && p[cp].arrtime <= time) {
                enqueue(&p[cp++]);
            }
        }
        else {
            while (cp < n && p[cp].arrtime <= time) {
                enqueue(&p[cp++]);
            }
            enqueue(temp);
        }
    }
}

int main() {
    int n, t;
    printf("Enter the time slice : ");
    scanf("%d", &t);
    printf("Enter the number of processes : ");
    scanf("%d", &n);
    process p[SIZE];
    head = tail = NULL; // Initialize head and tail
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time : ");
        scanf("%d", &p[i].arrtime);
        printf("Enter burst time : ");
        scanf("%d", &p[i].btime);
        p[i].btime1 = p[i].btime;
        p[i].pid = i;
    }
    printf("\n");
    rr(p, n, t);
    int totalWT = 0, totalTT = 0;
    for (int i = 0; i < n; i++) {
        printf("waiting time of process %d : %d\n", p[i].pid + 1, p[i].wtime);
        totalWT += p[i].wtime;
        totalTT += p[i].tatime;
        printf("turnaround time of process %d : %d\n", p[i].pid + 1, p[i].tatime);
        printf("completion time of process %d : %d\n\n", p[i].pid + 1, p[i].comptime);
    }
    printf("\nTotal waiting time : %d", totalWT);
    printf("\nTotal turn around time : %d", totalTT);
    printf("\nAverage waiting time : %f", (float)totalWT / n);
    printf("\nAverage turn around time : %f\n\n", (float)totalTT / n);

    return 0;
}

// Shortest job first scheduling 
#include <stdio.h>
#define SIZE 1000
typedef struct
{
    int pid;
    int wtime;
    int tatime;
    int btime;
    int arrtime;
    int comptime;
    int si;
} process;
void sort(process *p, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (p[j].arrtime > p[j + 1].arrtime)
            {
                process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}
process heap[SIZE];
int tail = -1;
void insert(process p)
{
    if (tail + 1 >= SIZE)
    {
        return;
    }
    heap[++tail] = p;
    // heapify-up
    int childIndex = tail;
    int parentIndex = (tail - 1) / 2;
    while (childIndex > 0 && heap[parentIndex].btime > heap[childIndex].btime)
    {
        process temp = heap[parentIndex];
        heap[parentIndex] = heap[childIndex];
        heap[childIndex] = temp;
        childIndex = parentIndex;
        parentIndex = (childIndex - 1) / 2;
    }
}
int isempty()
{
    return (tail <= -1);
}
process delete()
{
    if (tail == -1)
    {
        return;
    }
    process temp = heap[0];
    heap[0] = heap[tail--];
    // heapify-down
    int parentIndex = 0;
    int leftChildIndex = 2 * parentIndex + 1;
    int rightChildIndex = 2 * parentIndex + 2;
    while (leftChildIndex <= tail)
    {
        int minIndex =
            (heap[parentIndex].btime > heap[leftChildIndex].btime) ? leftChildIndex : parentIndex;
        if (rightChildIndex <= tail)
        {
            minIndex =
                (heap[minIndex].btime > heap[rightChildIndex].btime) ? rightChildIndex : minIndex;
        }
        if (minIndex == parentIndex)
        {
            break;
        }
        process temp = heap[parentIndex];
        heap[parentIndex] = heap[minIndex];
        heap[minIndex] = temp;
        parentIndex = minIndex;
        leftChildIndex = 2 * parentIndex + 1;
        rightChildIndex = 2 * parentIndex + 2;
    }
    return temp;
}
void sjf(process *p, int n)
{
    sort(p, n);
    for (int i = 0; i < n; i++)
    {
        p[i].si = i;
    }
    int time =
        p[0].arrtime;
    int cp = 0;
    while (cp < n || !isempty())
    {
        while (cp < n && p[cp].arrtime <= time)
        {
            insert(p[cp++]);
        }
        process temp = delete ();
        p[temp.si].wtime = time - temp.arrtime;
        p[temp.si].tatime = p[temp.si].wtime + p[temp.si].btime;
        time += temp.btime;
        p[temp.si].comptime = time;
    }
}
void main()
{
    int n;
    printf("Enter the number of processes : ");
    scanf("%d", &n);
    process p[SIZE];
    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time : ");
        scanf("%d", &p[i].arrtime);
        printf("Enter burst time : ");
        scanf("%d", &p[i].btime);
        p[i].pid = i;
    }
    printf("\n");
    sjf(p, n);
    int totalWT = 0, totalTT = 0;
    for (int i = 0; i < n; i++)
    {
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
}


// First come First Serve Schedule 
#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000
struct sjf
{
    int pid;
    int btime;
    int wtime;
    int ttime;
    int arrtime;
    int comptime;
} p[10];
void sort(struct sjf *p, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (p[j].arrtime > p[j + 1].arrtime)
            {
                struct sjf temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}
int main()
{
    int i, n;
    int towtwtime = 0, totttime = 0;
    printf("\n ***fcfs scheduling***\n");
    printf("Enter the Number of processes : ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("\nBurst time of the process %d : ", i + 1);
        scanf("%d", &p[i].btime);
        printf("\nArrival time of the process %d : ", i + 1);
        scanf("%d", &p[i].arrtime);
    }
    sort(p, n);
    p[0].wtime = 0;
    p[0].ttime = p[0].comptime = p[0].btime;
    totttime += p[0].ttime;
    for (i = 1; i < n; i++)
    {
        p[i].wtime = (p[i].arrtime - p[i - 1].comptime >= 0) ? 0 : (p[i - 1].comptime - p[i].arrtime);
        p[i].ttime = p[i].wtime + p[i].btime;
        p[i].comptime = p[i].arrtime + p[i].wtime + p[i].btime;
        totttime += p[i].ttime;
        towtwtime += p[i].wtime;
    }
    printf("\nProcess\tArrival\tBurst Time\tTurnaround time\tWaiting time\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\t", p[i].pid);
        printf("%d\t", p[i].arrtime);
        printf("%d\t\t", p[i].btime);
        printf("%d\t\t", p[i].ttime);
        printf("%d\n", p[i].wtime);
    }
    printf("\ntotal waiting time :%d sec", towtwtime);
    printf("\naverage waiting time :%.2f sec", (float)towtwtime / n);
    printf("\ntotal turn around time :%d sec", totttime);
    printf("\naverage turn around time: :%.2f sec\n", (float)totttime / n);
}




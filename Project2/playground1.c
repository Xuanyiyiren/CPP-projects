#include <stdio.h>
#include <sys/time.h>

int main()
{
    struct timeval start, end;
    double time_spent;

    gettimeofday(&start, NULL);

    // 这里是你要测量运行时间的代码
    for (int i = 0; i < 1000000; i++)
    {
        // 一些计算
    }

    gettimeofday(&end, NULL);

    time_spent = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;

    printf("程序运行时间: %f 秒\n", time_spent);

    return 0;
}
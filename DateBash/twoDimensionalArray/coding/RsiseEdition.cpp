/*
 * @Description:
 * @Version: 2.0
 * @Autor: kerwinz
 * @Date: 2023-11-17 16:46:43
 * @LastEditors: kerwinz
 * @LastEditTime: 2023-11-17 16:59:40
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10
#define MAXSIZE 50

void matcreat(int matrix[MAX][MAX], int row, int col)
{ // 随机生成稀疏矩阵
    int i, j;
    int dataij[MAX * MAX / 5];
    int count;
    int rowc, colc;
    do
    {
        srand((int)time(0));
        count = rand() % (row * col / 5);  // 确定稀疏矩阵非零元个数
    } while (count < (row * col / 5 - 3)); // 设法使得稀疏数据量接近总量的20%，避免数据量过少
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++)
            matrix[i][j] = 0;   // 赋初值
    for (i = 0; i < count; i++) // 利用技巧解决了非零元分布的均匀性
    {
        dataij[i] = rand() % 100; // 先产生一个两位数，首位可以为0
        rowc = dataij[i] / 10;    // 十位数约定给行下标
        colc = dataij[i] % 10;    // 个位数约定给列下标
        do
        {
            matrix[rowc][colc] = rand() % 100; // 把这个位置控制住，再产生一个一位数的随机数存入
        } while (matrix[rowc][colc] < 10);
    }
    printf("这是产生的稀疏矩阵：\n");
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            printf("%6d", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void compress(int matrix[MAX][MAX], int row, int col)
{
    int compressed[MAXSIZE][3]; // 存储压缩后的数据
    int count = 0;              // 记录非零元素个数

    // 遍历原数组
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (matrix[i][j] != 0)
            {
                compressed[count][0] = i;            // 记录行数
                compressed[count][1] = j;            // 记录列数
                compressed[count][2] = matrix[i][j]; // 记录内容
                count++;
            }
        }
    }

    // 输出压缩后的数据
    printf("这是压缩后的数据：\n");
    for (int i = 0; i < count; i++)
    {
        printf("%d\t%d\t%d\n", compressed[i][0], compressed[i][1], compressed[i][2]);
    }
}

int main()
{
    int row, col;
    int matrixdata[MAX][MAX];
    char choice;
    while (1)
    {
        printf("    稀疏矩阵压缩存储\n");
        system("pause");
        printf("    请输入稀疏矩阵的规模(行 列)：");
        scanf("%d %d", &row, &col);
        matcreat(matrixdata, row, col);
        compress(matrixdata, row, col);
        printf("是否继续？按N结束，其他任意键继续…");
        fflush(stdin);
        scanf("%c", &choice);
        system("cls");
        if (choice == 'N' || choice == 'n')
            break;
    }
    return 0;
}
// ##快速排序

// **要点：**
//  1、递归算法的锚点，非递归的结束时刻
//  2、顺序
// ```
#include <stdio.h>


int a[101], n;

void quicksort(int left, int right)
{
    int i, j, t, temp;
    if(left > right) {
        return;
    }

    temp = a[left];     //基准数
    i = left;
    j = right;

    while(i != j) {
        //顺序很重要，要先从右往左找
        while(a[j] >= temp && i < j)
            j--;
        while(a[i] <= temp && i < j)
            i++;

        //当哨兵i和哨兵j没有相遇时，交换两个数在数组中的位置
        if(i < j){
            t = a[i];
            a[i] = a[j];
            a[j] = t;
        }
    }
    //最终将基准数归位
    a[left] = a[i];
    a[i] = temp;

    quicksort(left, i-1);
    quicksort(i+1, right);
}

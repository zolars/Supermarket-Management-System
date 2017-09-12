// Name: Qsort
// Author: 辛逸飞
// Date: 2017-09-12
// Language: C
// Features: 为一个数组从小到大排序. 时间复杂度为Θ(n\lgn), 空间复杂度为Θ(\lgn).

#include <stdio.h>

void qsort(int a[], int left, int right) {
  int i, j, key; //指针

  // 判断递归终点
  if (left >= right)
    return;

  i = left;
  j = right;
  key = a[left];

  // 遍历从 i 到 j
  while (i < j) {

    // 找到右端元素
    while (i < j && a[j] >= key)
      j--;
    a[i] = a[j];

    // 找到左端元素
    while (i < j && a[i] < key)
      i++;
    a[j] = a[i];
  }

  // 交换元素
  a[i] = key;

  // 分割, 继续递归
  qsort(a, left, i - 1);
  qsort(a, i + 1, right);
}

int main() {
  int n, i; // 声明数组长度
  int a[n]; // 声明数组

  scanf("%d", &n);
  for (i = 1; i <= n; i++)
    scanf("%d", &a[i]);

  qsort(a, 1, n);

  for (i = 1; i <= n; i++)
    printf("%d ", a[i]);

  return (0);
}

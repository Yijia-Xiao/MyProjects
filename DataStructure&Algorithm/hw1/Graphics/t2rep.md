# 第二题

## `题目大意`

在笛卡尔坐标系的第1象限，给定n条线段（端点分别在x、y轴）；求解：连接原点、P(x, y)的线段与这n条线段的交点个数

## `思路分析`

- ToLeft方法判断点与线段的位置关系（实质是用叉积，计算有向面积，通过面积+、-，来判断位置关系）

- 二分查找：将查找边界点的时间复杂度从$O(n)$降至$log(n)$

## `算法优化`

- 最初的代码实现：Toleft()函数由2部分构:
  - Area()：利用叉积，计算有向面积
  - Toleft()：通过Area()的正负，判断点、线段的左右关系

- 优化：此题中，我们关心的只是左、右的相对位置关系，并不关心线段与点的偏离程度。因此，将Area()面积函数、判断函数Toleft()可以合并成Toleft函数，减少调用、传参的开销

## `具体实现`

- 首先将x、y轴上点的坐标读入到两个数组xs、ys

- 其次，对xs、ys进行排序（有序性是二分查找的前提）

- 进行二分查找：一直寻找到边界线段，即`最后一个在p点左下方（包含过p点）`线段的index

- 输出结果

## `时间、空间复杂度分析`

### **时间复杂度**

- qsort() - $nlog(n)$

- 二分查找 - $log(n)$

### **空间复杂度**

- $O(kn)$ ('k'代表常数倍O(n))

## 总结感悟

- 分析要全面：计算结果不溢出，并不代表中间结果不溢出
  - （此题toleft()中间计算需要longlong类型）

- 二分查找的前提是单调，此题的妙处在于：
  - 保证x、y轴上的坐标单调递增，即可保证在Toleft()比较准则下，线段相对P单调递增（也就是说，对xs、ys排序后，即可对n条线段二分查找，其比较判断`"大小"`标准为Toleft()的真or假）
  - 问题与int数组在'<'号意义下的二分查找等同，将int二分查找算法的模板中比较标准'<' 改为ToLeft()（或!Toleft()， 实际情况确定），即可解决Toleft()意义下的二分查找
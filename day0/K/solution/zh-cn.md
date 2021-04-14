{{ self.title() }}

作者，版权声明等

## 题目简述

可以把题目的要点再说一遍。

## 子任务设计

如果有的话，也许需要解释一下部分分都是怎么设计的。

## 参考解法

根据初等数论知识：$(an+b,c)=1 \Leftrightarrow \forall p \mid c, p \nmid (an+b)$。

显然 $(a,b,c)\ne1$ 时无解。

接下来讨论在 $(a,b,c)=1$ 的情况下构造合法的 $n$。考虑 $c$ 的任意一个质因子 $p$，尝试取 $n$ 使 $p \nmid (an+b)$，讨论两种情况：

- 若  $p \mid b$，则有 $p \nmid a$，否则 $p$ 是 $a,b,c$ 的一个公因子，于是可令 $p \nmid n$；

- 若 $p \nmid b$，显然可令 $p \mid n$。

于是在这种构造方法下 $n$ 应满足： $p \mid c \Rightarrow (p \mid n \Leftrightarrow p \nmid b)$。

接下来讨论如何在高精度设定下构造出满足上述构造方法的 $n$，采用的思路是将 $b$ 的所有质因子从 $c$ 中消去。计算如下迭代：

$$
c_0=c, c_{i+1}=\frac{c_i}{(c_i, b)}
$$

不难验证这个迭代是收敛的，且最终得到的值恰好是将将 $b$ 的所有质因子从 $c$ 中消去剩下的结果，即为所求 $n$ 的一个可行值。

上述方法涉及到两个高精度计算：

- 高精度 gcd 使用如下方法递归计算（不妨令 $a>b$）：
    $$
    (a,b) = \begin{cases}
    2(a/2, b/2), & 2 \mid a, 2 \mid b \\
    (a/2, b), & 2 \mid a, 2 \nmid b  \\
    (a, b / 2), & 2 \nmid a, 2 \mid b \\
    ((a-b) / 2, b), & 2 \nmid a, 2 \nmid b
    \end{cases}
    $$

- 高精度整除可以取多个大质数用 CRT 计算。
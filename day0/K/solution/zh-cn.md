{{ self.title() }}

作者，版权声明等

## 题目简述

给定高精度整数 $a,b,c$，求 $n$ 使 $(a+bn,c)=1$。

## 参考解法

根据初等数论知识：$(an+b,c)=1 \Leftrightarrow \forall p \mid c, p \nmid (an+b)$。

显然 $(a,b,c)\ne1$ 时无解。

接下来讨论在 $(a,b,c)=1$ 的情况下构造合法的 $n$。考虑 $c$ 的任意一个质因子 $p$，尝试取 $n$ 使 $p \nmid (an+b)$，讨论两种情况：

- 若  $p \mid b$，则有 $p \nmid a$，否则 $p$ 是 $a,b,c$ 的一个公因子，于是可令 $p \nmid n$；

- 若 $p \nmid b$，显然可令 $p \mid n$。

于是在这种构造方法下 $n$ 应满足： $p \mid c \Rightarrow (p \mid n \Leftrightarrow p \nmid b)$。

接下来讨论如何在高精度设定下构造出满足上述构造方法的 $n$，采用的思路是将 $b$ 的所有质因子从 $c$ 中消去。计算如下迭代：

$$
d_0=(b,c), d_{i+1}=(d_i^2,c)
$$

不难验证此迭代将收敛至不动点，设为 $d$，则 $n=c/d$。

其中，高精度 gcd 使用如下方法递归计算（不妨令 $a>b$）：
$$
    (a,b) = \begin{cases}
    2(a/2, b/2), & 2 \mid a, 2 \mid b \\
    (a/2, b), & 2 \mid a, 2 \nmid b  \\
    (a, b / 2), & 2 \nmid a, 2 \mid b \\
    ((a-b) / 2, b), & 2 \nmid a, 2 \nmid b
    \end{cases}
$$

设高精度整数长度为 $l$，高精度 gcd 的复杂度为 $O(l^2)$，高精度乘法、除法可直接使用复杂度为 $O(l^2)$ 的实现，倍增次数为 $O(\log l)$，总时间复杂度为 $O(l^2 \log l)$。
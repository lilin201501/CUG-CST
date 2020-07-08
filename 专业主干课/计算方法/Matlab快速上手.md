## Matlab快速上手

### 输入矩阵格式

```
A=[1 2 3;4 5 6;7 8 9]
```

### 冒号表达式 起始:步长:终止

```
xx=0:0.1:10
```

### 求解方程

```
a=[4,1,-1,0;1,-5,-1,-3;2,-1,-6,1;5,4,4,30];
b=[8;1;-1;16];
x=a\b
```

### 匿名函数

handle = @(arglist)anonymous_function

handle为调用匿名函数时使用的名字

arglist为匿名函数的输入参数，可以是一个，也可以是多个，用逗号分隔

anonymous_function为匿名函数的表达式

```
f=@(x,y)x^2+y^2; 
f(1,2) 
ans =  5
```

### inline函数

FunctionName=inline(‘任何有效的matlab表达式’, ‘p1’,’p2’ ,….) 

其中‘p1’,’p2’ ,…是出现在表达式中的所有变量的名字。 
如：（求解F(x)=x^2*cos(a*x)-b ,a,b是标量；x是向量 ）  

```
Fx=inline('x.^2.*cos(a*x)-b','x','a','b')
```

设置输出精度

```
digits(9)
vpa(a)
```

### 接受多个返回值

```
[A,B]=lsline(xx,yy)
```

### 定义未知量

```
syms a b1 b2 b3;
```

### 求矩阵的逆

```
inv(A)
```

### 求矩阵的特征值

```
eig(A)
```

### 求矩阵的转置

```
A.'
transpose(A)
```

### 绘制函数

```
x=linspace(0,1); 
y=(-2。718.^x+2*x+2);
```

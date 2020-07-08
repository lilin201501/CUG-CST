import kotlin.math.pow
import kotlin.math.sin
import kotlin.math.abs as abs


fun main() {
    //val gaussA = arrayOf(doubleArrayOf(0.0),doubleArrayOf(0.0, -1.0, 0.0, -1.0, 0.0, 8.0), doubleArrayOf(0.0, 1.0, -5.0, -1.0, -3.0, 1.0), doubleArrayOf(0.0, 2.0, -1.0, -6.0, 1.0, -1.0), doubleArrayOf(0.0, 5.0, 4.0, 4.0, 30.0, 16.0))
    val iterA = arrayOf(doubleArrayOf( -1.0, 0.0, 1.0, 2.0), doubleArrayOf(1.0, 1.0, 1.0,1.0), doubleArrayOf( 1.0, 0.0, 1.0, 4.0), doubleArrayOf(-1.0, 0.0, 1.0, 8.0))
    val b = doubleArrayOf(4.5,3.0,3.0,2.25)
    //fixedPointMethod(1.0,2.0,0.000000001)
    //newtonIterationMethod(0.0, 2.0, 0.000000001)
    //gaussElimination(gaussA,4)
    jacobiIterativeMethod(iterA,b,4,0.00001)
    //gaussSeidel(iterA,b,4,0.00001)
    //catchUpMethod()
    //lagrangeInterpolation()
    //hermiteInterpolation()
    //trapezoidQuadratureFormula(0.0,0.25,100000)
    //simpsonFormula(0.0,1.0,100000)
   // rombergQuadratureFormula(1.0,3.0,0.00001)
    //goldenSectionSearch(0.0,1.0,0.00001)
}

//1.运用不动点迭代法求解非线性方程f(x)=x^5-3*x^3-2x^2+2=0在区间[0,1]内的解（精确到小数点后9位）
fun fixedPointMethod(left:Double, right:Double, ep:Double){
    var k: Double = (right + left) / 2
    while (abs(k - gx(k)) > ep) {
        println("g(x):"+String.format("%.9f", k))
        k = gx(k)
    }
    println("不动点迭代法求解为"+String.format("%.9f", k))
}

//fun gx(x: Double)=((x.pow(5) - 2 * x.pow(2) + 2) / 3.0).pow(1 / 3.0)
fun gx(x: Double)=((0.5*(10-x.pow(3)).pow(0.5)))

//2.用Newton迭代法求解sqrt(5)的近似值，精确到小数点后9位 （参考结果： 2.236067978）
fun newtonIterationMethod(left:Double, right:Double, ep:Double){
    var x: Double = 1.5
    while (fx(x) / dfx(x) > ep) {
        println("x: "+String.format("%.9f", x))
        x -= (fx(x) / dfx(x))
    }
    println("Newton迭代法求解为"+String.format("%.9f", x))
}

fun fx(x: Double)=(x*x*x-x-2)
fun dfx(x: Double)=(3*x*x-1)

//3.求解线性方程组（分别用Gauss消去法、Jacobi迭代法和Gauss-Seidel迭代法求解，精确到小数点后4位）
//Gauss消去法//采用增广矩阵存储方程且此处将arr[0][]和arr[][0]置空
fun gaussElimination(a: Array<DoubleArray>,n:  Int):DoubleArray{
    //采用顺序消元法，未进行行列变换，仅检测主对角线元素是否为零
    val xi=DoubleArray(n)
    for (k in 1..n){
        if(a[k][k]==0.0){
            println("主对角线存在零元素！无法求解")
            return xi
        }
    }

    for(row in 1..n){
        val diaVal=a[row][row]  //将主对角线元素存储
        for (cal in 1..n+1){
            a[row][cal]/=diaVal  //系数变为1
        }
        for (now in row+1..n){
            //val multiple=a[now][row]/a[row][row]
            val multiple=a[now][row]
            for (cal in 1..n+1){
                a[now][cal]-=multiple*a[row][cal]
            }
        }
    }

//回代
    for (i in n-1 downTo 1){
        for (j in i downTo 1){
            a[j][n+1]-=a[j][i+1]*a[i+1][n+1]
            a[j][i+1]=0.0
        }
    }

//输出方程解
    //println("Gauss消去法求解结果为：")
    for (m in 1..n){
        //val out="x$m: "+String.format("%.4f", a[m][n+1])
        xi[m-1]=a[m][n+1]
        //println(out)
    }
    return xi
}

//Jacobi迭代法
fun jacobiIterativeMethod(A: Array<DoubleArray>, b: DoubleArray, n: Int,ep:Double) {
    val x: DoubleArray = DoubleArray(n)
    val oldX: DoubleArray = DoubleArray(n)
    do {
        for (i in 0 until n){
            oldX[i] = x[i]
        }

        for (j in 0 until n){
            x[j] = b[j]
            for (k in 0 until n){
                if (j != k) x[j] = x[j] - A[j][k] * oldX[k]
            }
            x[j] = x[j] / A[j][j]
        }

    } while (testConvergence(x, oldX, ep) == 0)

    //输出方程解
    println("精度为$ep 的Jacobi迭代法解为")
    for (m in 0 until n){
        val out="x$m: "+String.format("%.4f", x[m])
        println(out)
    }
}

//Gauss-Seidel
fun gaussSeidel(A: Array<DoubleArray>, b: DoubleArray, n: Int,ep:Double){
    val x: DoubleArray = DoubleArray(n)
    val oldX: DoubleArray = DoubleArray(n)
    do {
        for (i in 0 until n){
            oldX[i] = x[i]
        }

        for (j in 0 until n){
            x[j] = b[j]
            for (k in 0 until n){
                if (j != k) x[j] = x[j] - A[j][k] * x[k]
            }
            x[j] = x[j] / A[j][j]
        }

    } while (testConvergence(x, oldX, ep) == 0)

    //输出方程解
    println("精度为$ep 的Gauss-Seidel法求解为")
    for (m in 0 until n){
        val out="x$m: "+String.format("%.4f", x[m])
        println(out)
    }
}

//判断是否达到精度
fun testConvergence(x: DoubleArray, oldX: DoubleArray, epsilon: Double): Int {
    for (i in x.indices){
        if (abs(x[i] - oldX[i]) >epsilon) return 0
    }
    return 1
}

//4.用追赶法求解方程组（6位有效数字）
fun catchUpMethod(){
    val n = 5
    val a = arrayOf(doubleArrayOf(0.0, 4.0, -1.0,100.0), doubleArrayOf(-1.0, 4.0, -1.0, 0.0), doubleArrayOf(-1.0, 4.0, -1.0, 0.0),doubleArrayOf(-1.0, 4.0, -1.0, 0.0), doubleArrayOf(-1.0, 4.0, 0.0, 200.0))
    val r = DoubleArray(n)
    val y = DoubleArray(n)
    val x = DoubleArray(n)
    r[0]=a[0][2]/a[0][1]
    y[0]=a[0][3]/a[0][1]
    for (k in 1 until n){
        r[k]=a[k][2]/(a[k][1]-r[k-1]*a[k][0])
        y[k]=(a[k][3]-y[k-1]*a[k][0])/(a[k][1]-r[k-1]*a[k][0])
    }
    x[n-1]=y[n-1]
    for (k in n-2 downTo 0){
        x[k]=y[k]-r[k]*x[k+1]
    }
    println("追赶法求解为：")
    for (m in 0 until n){
        val out="x$m: "+String.format("%g", x[m])
        println(out)
    }
}

//5.已知 f(x)=e^x*(3*x-e^x)
//（1）利用插值节点x0=1.00，x1=1.02，x2=1.04，x3=1.06，构造三次Lagrange插值公式，由此计算f(1.03)的近似值，并给出其实际误差（参考结果0.8093）。
//（2）利用插值节点x0=1，x1=1.05构造三次Hermite插值公式，由此计算f(1.03)的近似值，并给出其实际误差

fun lagrangeInterpolation() {
    val x=1.03
    val knownPoint=4
    val xi= doubleArrayOf(1.0,1.02,1.04,1.06)
    val yi=doubleArrayOf(fxInterpolationExm(1.0),fxInterpolationExm(1.02),fxInterpolationExm(1.04),fxInterpolationExm(1.06))
    var result = 0.0
    for (i in 0 until knownPoint) {
        var l = yi[i]
        for (j in 0 until knownPoint) {
            if (j != i) l = l * (x - xi[j]) / (xi[i] - xi[j])
        }
        result += l
    }
    println("Lagrange插值得到f(1.03)的近似值: $result")
    println("误差："+(fxInterpolationExm(1.03)-result))
}

fun hermiteInterpolation(){
    //H3(x)=a0+a1*x+a2*x^2+a3*x^3
    val ep=0.000001
    val n=2         //插值的维数
    val xi= doubleArrayOf(1.0,1.05)
    val yi=doubleArrayOf(fxInterpolationExm(1.0),fxInterpolationExm(1.05))
    val dyi=doubleArrayOf(dfxInterpolationExm(1.0),dfxInterpolationExm(1.05))
    val x=1.03

    val eq = arrayOf(doubleArrayOf(0.0),
            doubleArrayOf(0.0, 3*xi[0].pow(2), 2*xi[0], 1.0, 0.0, dfxInterpolationExm(xi[0])),
            doubleArrayOf(0.0, 3*xi[1].pow(2), 2*xi[1], 1.0, 0.0, dfxInterpolationExm(xi[1])),
            doubleArrayOf(0.0, xi[0].pow(3), xi[0].pow(2),  xi[0], 1.0, fxInterpolationExm(xi[0])),
            doubleArrayOf(0.0, xi[1].pow(3), xi[1].pow(2),  xi[1], 1.0, fxInterpolationExm(xi[1]))
    )
    //采用高斯消元法解该方程, 因为计算精度的问题，结果存在一些误差
    val ai=gaussElimination(eq,4)
    val result=ai[0]*x.pow(3)+ai[1]*x.pow(2)+ai[2]*x+ai[3]
    println("Hermite插值得到f(1.03)的近似值: $result")
    println("误差: "+(fxInterpolationExm(1.03)-result))
}


fun fxInterpolationExm(x: Double)=(2.7182818284.pow(x)*(3*x-2.7182818284.pow(x)))
fun dfxInterpolationExm(x: Double)=((3+3*x)*2.7182818284.pow(x)-(2*2.7182818284.pow(2*x)))


//6.拟合数据并把散点图和相应的拟合曲线画出来
fun fitData(){
    //由于使用Kotlin进行绘图比较繁琐，本题采用Python来完成...
}

//7.1 用复化梯形公式求解积分
fun trapezoidQuadratureFormula(left: Double,right: Double,division:Int){
    val step=(right-left)/division
    var integral:Double= (fxTrapezExm(left) + fxTrapezExm(right))/2
    var p=left
    //由于kotlin对数字精度不敏感，采用如下方式控制，相当于while(p+step<right)
    while (right-p-step>0.00000000000001){
        p+=step
        integral+=fxTrapezExm(p)
    }
    integral*=step
    println("复化梯形公式求解积分为：$integral")
}

fun fxTrapezExm(x: Double)=(4- sin(x).pow(2)).pow(0.5)

//7.2 用复化辛普森公式求解积分
fun simpsonFormula(left: Double,right: Double,division:Int){
    val step=(right-left)/division
    var integral:Double= (fxSimpsonExm(left) + fxSimpsonExm(right))
    var p=left
    while (right-p>0.00000000000001){
        p += step/2
        integral += 4*fxSimpsonExm(p)
        p += step/2
        integral += 2*fxSimpsonExm(p)
    }
    integral=(integral*step)/6
    println("复化辛普森公式求解积分为：$integral")
}

fun fxSimpsonExm(x: Double)=(2.7182818284.pow(x)/(4+x.pow(2)))

//8.利用Romberg算法计算积分
fun rombergQuadratureFormula(left: Double,right: Double,ep:Double){
    var step=right-left
    var x:Double
    var integral:Double
    var k:Int=1
    val T= DoubleArray(5)
    val S= DoubleArray(5)
    val C= DoubleArray(5)
    val R= DoubleArray(5)
    T[1]=(step * (fxRombergExm(left) + fxRombergExm(right)) / 2)
    while (true) {
        integral = 0.0
        x = left + step / 2.0
        while (true) {
            integral += fxRombergExm(x)
            x += step
            if (x >= right)	//若已超过区间右端点
                break
        }
        T[2] = T[1] / 2 + step / 2 * integral
        S[2] = T[2] + 1.0 / 3.0 * (T[2] - T[1])
        if (k == 1) {
            k++
            step /= 2.0
            T[1] = T[2]
            S[1] = S[2]
            continue
        }
        C[2] = S[2] + 1.0 / 15.0 * (S[2] - S[1])
        if (k == 2) {
            k++
            step /= 2.0
            C[1] = C[2]
            T[1] = T[2]
            S[1] = S[2]
            continue
        }
        R[2] = C[2] + 1.0 / 63.0 * (C[2] - C[1])
        if (k == 3) {
            k++
            step /= 2.0
            R[1] = R[2]
            C[1] = C[2]
            T[1] = T[2]
            S[1] = S[2]
            continue
        }
        if (abs(R[2] - R[1]) >= ep) {
            k++
            step /= 2.0
            R[1] = R[2]
            C[1] = C[2]
            T[1] = T[2]
            S[1] = S[2]
            continue
        }
        break
    }
    println("精度为"+ep+"的积分结果为"+R[2])
}

fun fxRombergExm(x:Double)=(3.0.pow(x)*x.pow(1.4)*(5*x+7)*sin(x.pow(2)))

//9.用黄金分割搜索法求解单峰函数f(x)=sin(x)-x^2在区间[0,1]上的极大值。容差为ε=10^-4
fun goldenSectionSearch(left: Double,right: Double,ep:Double){
    val k=(5.0.pow(0.5)-1)/2
    var count:Int=0
    var k1:Double
    var k2:Double
    var a=left
    var b=right

    while(b-a>ep){
        count+=1
        //println("第"+count+"次迭代")
        k1=a+(b-a)*(1-k)
        k2=a+(b-a)*k
        //println("k1=$k1 k2:$k2")
        //println("f(k1)=${fxGoldenSectionSearch(k1)} f(k2):${fxGoldenSectionSearch(k2)}")
        if(fxGoldenSectionSearch(k1)-fxGoldenSectionSearch(k2)<0) {
            a=k1
            //println("f(k1)<f(k2)")
        }
        else {
            b=k2
            //println("f(k1)>f(k2)")
        }
        //println("a=$a b:$b")
    }
    println("迭代次数为"+count+"  最优解区间为[$a,$b]"+"取中点得最优值为："+fxGoldenSectionSearch((a+b)/2))
}

fun fxGoldenSectionSearch(x:Double)=(sin(x)-x.pow(2))
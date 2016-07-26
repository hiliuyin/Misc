int add(int x, int y)
{
    int xor_ = 0;
    int and_ = 0;
    
    if (y == 0) return x;
    while (y != 0)
    {
        xor_ = x ^ y; // xor运算相当于丢失了进位的加法
        and_ = x & y; // and运算保留了所有的进位
        
        and_ = and_ << 1; // 将进位右移一位

        // 反复执行上述操作，直到and运算的结果为0
        x = xor_;
        y = and_;
    }
    
    return xor_;
}

int sub(int x, int y)
{
    return add(x, ~y+1); // 一个数字和它的补码的和为0
}

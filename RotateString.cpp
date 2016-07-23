void rotateString(std::string &str, int k)
{
    const int sz = (int)str.size();
    if (sz <= 1 || k == 0) return;
    
    k = k % sz;
    if (k < 0) k = sz + k;
    
    int from = 0, to = k;
    int origin = 0;
    char ch1 = str[from], ch2;
    for (int i = 0; i < sz; ++i)
    {
        ch2 = str[to];
        str[to] = ch1;
        ch1 = ch2;
        
        from = to;
        if (from == origin) // avoid circle
        {
            origin = ++from;
            ch1 = str[from];
        }
        to = (from + k) % sz;
    }
}

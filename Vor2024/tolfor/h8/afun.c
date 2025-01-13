void fun(long *a, int len, long *res) {
    int i;
  
    *res = 0;
    for (i=0; i<len; i++)
        *res += a[i];
}

int main(int argc, char *argv[]) {
    
    long a[] = {1, 2, 3, 4, 5, 6};
    long s;
    
    fun( a, 6, &s );
//    fun( a, 6, &(a[2]) );
    
    return 0;
}

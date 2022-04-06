
int recursive_sum(){
    int i, a = 1, b = 1, c;
    for(i=2;i<=15;i++){
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

int recursive_sum(int num){
    if (num <= 1){
        return 1;
    }
    return recursive_sum(num-1) + recursive_sum(num-2);
}
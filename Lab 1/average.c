// Only this line of comment is provided
int main() {
    double x;
    double total = 0.0;
    double average = 0.0;
    int count = 0;
    while (scanf("%lf", &x) == 1) {
        total += x;
        count++;
        average = total / count;
        printf("Total=%.6f Average=%.6f\n", total, average); 
        }
    return 0;
}
class Fibbonacci {

    // Fibbonacci recursive
    public static int fibbo(int no1, int no2) {
        if (no2 <= 100) {
            System.out.println(no2);

            return (fibbo(no2, no1 + no2));
        }
        return 0;
    }

    public static void main(String[] args) {

        // 0 1 1 2 3 5 8 ...
        int no = 100;
        int no1 = 0, no2 = 1;

        // Fibbonacci Iterative
        // System.out.println(0);
        // while(no2<no){
        // int t = no2;
        // no2 = no1+no2;
        // no1 = t;
        // System.out.println(no1);
        // }

        // Fibbonacci Recursive
        fibbo(no1, no2);

    }

}
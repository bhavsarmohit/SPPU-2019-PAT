
class Knapsack {

    public static int max(int a, int b) {
        return a > b ? a : b;
    }

    public static int knap(int w, int val[], int wt[], int n) {

        if (w == 0 || n == 0)
            return 0;

        if (wt[n - 1] > w) {
            return knap(w, val, wt, n - 1);
        } else {
            return max(val[n - 1] + knap(w - wt[n - 1], val, wt, n - 1),
                    knap(w, val, wt, n - 1));
        }

    }

    public static void main(String[] args) {
        int val[] = { 100, 200, 301 };
        int wt[] = { 10, 20, 30 };
        int w = 30;
        int n = val.length;

        System.out.println(knap(w, val, wt, n));

    }
}
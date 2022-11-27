public class NQueen {

    static int n = 4;

    public static void showBoard(int board[][]) {
        for (int i = 0; i < board.length; i++) {
            for (int j = 0; j < board.length; j++) {
                System.out.print(board[i][j] + " ");
            }
            System.out.println();

        }
    }

    public static boolean isSafe(int board[][], int row, int col) {
        int i, j;

        // rule 1
        for (i = 0; i < board.length; i++) {
            if (board[row][i] == 1) {
                return false;
            }
        }

        // rule 2
        for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 1) {
                return false;
            }
        }

        // rule 3
        for (i = row, j = col; i < board.length && j >= 0; i++, j--) {
            if (board[i][j] == 1) {
                return false;
            }
        }
        return true;
    }

    public static boolean Queen(int board[][], int col) {
        if (col >= board.length) {
            return true;
        }

        for (int i = 0; i < board.length; i++) {
            if (isSafe(board, i, col)) {
                board[i][col] = 1;

                if (Queen(board, col + 1)) {
                    return true;
                }

                board[i][col] = 0;

            }
        }
        return false;
    }

    public static void main(String[] args) {
        int board[][] = new int[n][n];

        if (Queen(board, 0)) {
            showBoard(board);
        } else {
            System.out.println("Unable to Place Queens");
        }

    }

}

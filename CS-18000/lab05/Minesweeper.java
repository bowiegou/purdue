/**
 * Auto Generated Java Class.
 */
import java.util.Random;
import java.util.Scanner;
public class Minesweeper {
    private int rows;
    private int columns;
    private boolean[][] minefield;
    private int[][] clueGrid;
    private boolean[][] checked;
    
    public Minesweeper(int rows, int columns, int mines) { 
        this.rows = rows;
        this.columns = columns;
        minefield = new boolean[rows][columns];
        clueGrid = new int[rows][columns];
        checked = new boolean[rows][columns];
        
        generateMinefield(mines);
        generateClueGrid();
        for (int i = 0; i < checked.length; i ++)
            for (int j = 0; j < checked[i].length; j ++)
            checked[i][j] = false;
        
    }
    

    private void generateMinefield(int mines) {
        int count = mines;
        int r = -1;
        int c = -1;
        Random ran = new Random(System.currentTimeMillis());
        for (int i = 0; i < minefield.length; i ++)
            for (int j = 0; j < minefield[i].length; j ++)
            minefield[i][j] = false;
        while (count > 0) {
            r = ran.nextInt(minefield.length);
            c = ran.nextInt(minefield[r].length);
            if (!minefield[r][c]) {
                minefield[r][c] = true;
                count--;
            }
        }
    }
    
    private void generateClueGrid() {
        for (int i = 0; i < clueGrid.length; i ++) {
            for (int j = 0; j < clueGrid[i].length; j ++) {
                if (!minefield[i][j])
                    clueGrid[i][j] = countMines(i, j);
                else
                    clueGrid[i][j] = -1;
            }
        }
        
    }
//        int r = 0;
//        int c = 0;
//        for (int i = 0; i < clueGrid.length; i ++)
//            for (int j = 0; j < clueGrid[i].length; j ++)
//            clueGrid[i][j] = 0;
//        for (int i = 0; i < minefield.length; i ++) {
//            for (int j = 0; j < minefield[i].length; j ++) {
//                if (minefield[i][j]) {
//                    if (i != 0) {
//                        cluefield[i-1][j]++;
//                        if (j != 0)
//                    }
//                    
//                    if (i + 1 != minefield.length)
//                        cluefield[i + 1][j]++;
//                    if (j != 0)
//                        cluefield[i][j-1]++;
//                    if (j + 1 != minefield.length)
//                        cluefield[i][j + 1]++;
//                }
//            }
//        }
//    }
            
        
    private int countMines(int row, int column) {
        int count = 0;
        int i = row;
        int j = column;
        if (i > 0) {
            // check array[i-1][j]
            if (minefield[i - 1][j])
                count++;
            if (j > 0) {
                // check array[i-1][j-1]
                if (minefield[i - 1][j])
                    count++;
                if (j < columns - 1) {
                    if (minefield[i - 1][j + 1])
                        count++;
                }
                // check array[i-1][j + 1]
            }
        }
        if (j > 0) 
            // check array[i][j-1]
            if (minefield[i][j - 1])
                count++;
        if (j < columns - 1) {
            if (minefield[i][j + 1])
                count++;
        }
            // check array[i][j + 1]
        if (i < rows - 1) {
            if (minefield[i + 1][j])
                count++;
            // check array[i + 1][j]
            if (j > 0) {
                // check array[i + 1][j-1]
                if (minefield[i + 1][j - 1])
                    count++;
                if (j < columns - 1) {
                    if (minefield[i + 1][j + 1])
                        count++;
                }
            }
        }
        return count;
    }
    
    private void printBoard() {
        char cellSymbol;
        char rl = 'A';
        // print column numbers
        System.out.print("   "); 
        for (int j = 0; j < columns; j ++) 
            System.out.print(" " + (j + 1)); 
        System.out.println(); 
        // print dividing line
        System.out.print("  +-"); 
        for (int j = 0; j < columns; j ++) 
            System.out.print("--"); 
        System.out.println(); 
        // print row letters and board cells
        for (int i = 0; i < rows; i ++) {
            // print a row of cells
            System.out.print(rl + " |"); 
            for (int j = 0; j < columns; j ++) { 
                if (!checked[i][j])
                    cellSymbol = '?';
                else if (minefield[i][j]) 
                    cellSymbol = '*';
                else if (clueGrid[i][j] > 0) 
                    cellSymbol = (char)('0' + clueGrid[i][j]);
                else  
                    cellSymbol = ' ';
                System.out.print(" " + cellSymbol);  
            }
            System.out.println(); 
            rl++;
        }
    }
    public void start() {
        Scanner scan = new Scanner(System.in);
        boolean win = false;
        while (!win) {
            String input;
            int r = 0;
            int c = 0;
            printBoard();
            System.out.println("Select a cell");
            input = scan.nextLine().toUpperCase();
            r = input.charAt(0) - 'A';
            c = input.charAt(1) - '1';
            
            if (!minefield[r][c]) 
                checked[r][c] = true;
            else
                break;
            
            win = true;
            for (int i = 0 ; i < rows && win; i ++)
                for (int j = 0; j < columns && win; j ++)
                    if (!checked[i][j] && !minefield[i][j])
                        win = false; 
        }
        
        for (int i = 0 ; i < rows; i ++)
            for (int j = 0; j < columns; j ++)
                checked[i][j] = true;
        printBoard();
            
        if (win)
            System.out.println("YOU WIN");
        else
            System.out.println("YOU LOSE");
    }
                               
           
    
    public static void main(String[] args) { 
        Minesweeper m = new Minesweeper(5, 5, 5);
        m.start();
    }
    
    /* ADD YOUR CODE HERE */
    
}

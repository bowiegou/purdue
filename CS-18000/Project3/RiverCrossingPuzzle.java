/**
 * CS 180 - Project 03 - RiverCrossingPuzzle
 * 
 * 
 * 
 * @Yibo Gou () <(gouy@purdue.edu)>
 * 
 * @815 (Your lab section)
 *
 * @Oct. 15 (Today's date)
 */
import java.util.Scanner;
public class RiverCrossingPuzzle {
    
    private int nCal = 0;
    private int nMis = 0;
    private int boatSize = 0;
    private int nCalL = 0;
    private int nMisL = 0;
    private boolean boatAtLeft = true;
    private int move = 0;
    private int status = 0;
    private static int[] avaCal;
    private static int[] avaMis;
    
 public RiverCrossingPuzzle() {
        this.nCal = 3;
        this.nMis = 3;
        this.boatSize = 2;
        avaCal = new int[(nCal+1)*(nMis+1)];
        avaMis = new int[(nMis+1)*(nCal+1)];
        reset();
    }
    public RiverCrossingPuzzle(int numEach, int boatSize) {
        this.nCal = numEach;
        this.nMis = numEach;
        this.boatSize = boatSize;
        avaCal = new int[(nCal+1)*(nMis+1)];
        avaMis = new int[(nMis+1)*(nCal+1)];
        reset();
    }
    public int numMissionariesOnLeftBank() {
        return nMisL;
    }
    public int numMissionariesOnRightBank() {
        return nMis - nMisL;
    }
    public int numCannibalsOnLeftBank() {
        return nCalL;
    }
    public int numCannibalsOnRightBank() {
        return nCal - nCalL;
    }
    public boolean boatOnLeftBank() {
        return boatAtLeft;
    }
    public boolean boatOnRightBank() {
        return !boatAtLeft;
    }
    
    public String availableActions() {
        String rText = "";
        int count = 0;
        if (boatOnLeftBank()) {
            if (numCannibalsOnLeftBank() != 0) {
                for (int i = 0; i <= numCannibalsOnLeftBank(); i++) {
                    for (int j = 0; j <= numMissionariesOnLeftBank(); j++) {
                        if (i + j <= boatSize && i + j > 0) {
                            rText += ("(" + (count ++) + ") " + i + " Cannibals and " + j + " Missionaries cross \n");
                            avaCal[count] = i;
                            avaMis[count] = j;
                        }
                    } 
                }
                return rText;
            }
            else {
                for (int j = 0; j <= numMissionariesOnLeftBank(); j++) {
                    int i = 0;
                    if (i + j <= boatSize && i + j > 0) {
                        count ++;
                        rText += ("(" + (count) + ") " + i + " Cannibals and " + j + " Missionaries cross \n");
                        avaCal[count] = i;
                        avaMis[count] = j;
                    }
                } 
            }
            return rText;
        }
        else {
            if (numCannibalsOnRightBank() != 0) {
                for (int i = 0; i <= numCannibalsOnRightBank(); i++) {
                    for (int j = 0; j <= numMissionariesOnRightBank(); j++) {
                        if (i + j <= boatSize && i + j > 0) {
                            count ++;
                            rText += ("(" + (count) + ") " + i + " Cannibals and " + j + " Missionaries cross \n");
                            avaCal[count] = i;
                            avaMis[count] = j;
                        }
                    } 
                }
                return rText;
            }
            else
            {
                for (int j = 0; j <= numMissionariesOnRightBank(); j++) {
                    int i = 0;
                    if (i + j <= boatSize && i + j > 0) {
                        rText += ("(" + (count ++) + ") " + i + " Cannibals and " + j + " Missionaries cross \n");
                        avaCal[count] = i;
                        avaMis[count] = j;
                    }
                } 
            }
            return rText;
        }
    }
    
    
    public void move(int numCannibalsToMove, int numMissionariesToMove) {
        
        if (boatOnLeftBank() && nCalL - numCannibalsToMove > 0 && 
            nMisL - numMissionariesToMove > 0 &&
   numMissionariesToMove + numCannibalsToMove <= boatSize &&
   (numMissionariesToMove + numCannibalsToMove) != 0)  {
            nCalL -= numCannibalsToMove;
            nMisL -= numMissionariesToMove;
            boatAtLeft = false;
            move ++;
            if( numCannibalsOnLeftBank() ==0 && numMissionariesOnLeftBank() ==0) {
                status = 1;
            }
            if (numCannibalsToMove > numMissionariesToMove || nCalL > nMisL ||(nCal-nCalL) > (nMis - nMisL))
                status = -1;
        }
        else if(numCannibalsOnRightBank() - numCannibalsToMove > 0 && 
                numMissionariesOnRightBank() - numMissionariesToMove > 0 &&
    numMissionariesToMove + numCannibalsToMove <= boatSize &&
    (numMissionariesToMove + numCannibalsToMove) != 0 )  {
            nCalL += numCannibalsToMove;
            nMisL += numMissionariesToMove;
            boatAtLeft = true;
            move ++;
            if( numCannibalsOnLeftBank() ==0 && numMissionariesOnLeftBank() ==0) {
                status = 1;
            }
            if (numCannibalsToMove > numMissionariesToMove || nCalL > nMisL ||(nCal-nCalL) > (nMis - nMisL))
                status = -1;
        }
        
    }
    public int totalMoves() {
        return move;
    }
    public void reset() {
        nCalL = nCal;
        nMisL = nCal;
        status = 0;
        move = 0;
        boatAtLeft = true;
    }
    public int status() {
        return status;
    }
    public void play() {
        Scanner scan;
        int[] temp;
        while(status() == 0) {
            scan = new Scanner(System.in);
            if( numCannibalsOnLeftBank() ==0 && numMissionariesOnLeftBank() ==0) {
                status = 1;
            }
   System.out.print(puzzleState());
            System.out.print(prompt());
            temp = new int[2];
   if (scan.hasNext()) {
    temp[0] = Integer.parseInt(scan.next());
    temp[1] = Integer.parseInt(scan.next());
   }
            move(temp[0], temp[1]);
        }
    }
    public static void main(String[] args) {
        int numEach = 0;
        int boatS = 0;
        Scanner scan = new Scanner(System.in);
        for (int i = 0; i < args.length; i ++) {
            if ( args[i].equals("-n")) {
                try { 
                    numEach = Integer.parseInt(args[i+1]);
                }
                catch (NumberFormatException e) {
                    System.out.println("Input type error");
                    
                }
            }
            else if (args[i].equals("-b")) {
                try { 
                    boatS = Integer.parseInt(args[i+1]);
                }
                catch (NumberFormatException e) {
                    System.out.println("Input type error");
                    
                }
                if(boatS > 4) {
                    System.out.println("Boat Size cannot be over 4");
                    
                }
            }
        }
        RiverCrossingPuzzle rc = new RiverCrossingPuzzle(numEach, boatS);
        rc.play();
		if(status() == 1)
			System.out.println("You Win");
		else
			System.out.println("You lose");
        System.out.println("Game over");
        scan.close();
        
    }  
    
    
    
    /**
     *  ***DO NOT CHANGE THIS FUNCTION.***
     * @return String containing the prompt for user input
     */
    public String prompt() {
        String str = "";
        str += "Available Actions\n";
        str += availableActions();
        str += "Action: ";
        return str;
    }
    
    /**
     * ***DO NOT CHANGE THIS FUNCTION.***
     * @return state of left (starting) bank as a String
     */
    private String leftBank() {
        String str = "";
        for (int i = 0; i < numCannibalsOnLeftBank(); i++)
            str += "C";
        str += " ";
        for (int i = 0; i < numMissionariesOnLeftBank(); i++)
            str += "M";
        str += " ";
        if (boatOnLeftBank())
            str += "B";
        return str;
    }
    
    /**
     *  ***DO NOT CHANGE THIS FUNCTION.***
     * @return state of right (ending) bank as a String
     */
    private String rightBank() {
        String str = "";
        if (boatOnRightBank())
            str += "B ";
        for (int i = 0; i < numCannibalsOnRightBank(); i++)
            str += "C";
        str += " ";
        for (int i = 0; i < numMissionariesOnRightBank(); i++)
            str += "M";
        return str;
    }
    
    public String toString() {
        return leftBank() + " | " + rightBank();
    }
    
    /**
     *  ***DO NOT CHANGE THIS FUNCTION.***
     * @return String representation of current state of puzzle
     */
    private String puzzleState() {
        String lb = leftBank();
        String rb = rightBank();
        String str = "\n";
        str += "Left Bank";
        for (int i = 9; i < lb.length(); i++)
            str += " ";
        str += " | ";
        for (int i = lb.length() + 3; i < lb.length() + rb.length() + 3 - 10; i++)
            str += " ";
        str += "Right Bank";
        str += "\n";
        str += lb;
        for (int i = lb.length(); i < 9; i++)
            str += " ";
        str += " | ";
        for (int i = rb.length() - 10; i < 0; i++)
            str += " ";
        str += rb;
        str += "\n";
        str += "\n";
        str += "   Cannibals on left,right banks: ";
        str += String.format("%3d,%3d", numCannibalsOnLeftBank(), numCannibalsOnRightBank());
        str += "\n";
        str += "Missionaries on left,right banks: ";
        str += String.format("%3d,%3d", numMissionariesOnLeftBank(), numMissionariesOnRightBank());
        str += "\n";
        str += "\n";
        str += "Number of moves: " + totalMoves();
        str += "\n";
        return str;
    }
}
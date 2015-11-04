/**
 * CS 180 - Lab 04 - Repetition
 * 
 * 
 * 
 * @Yibo Gou <(gouy@purdue.edu)>
 * 
 * @lab 815
 * 
 * @Sept.23, 2014 
 */
import java.util.Scanner;
public class Repetition {
    
    public static void main(String[] args) {
        /* Your testing can go here */
        // call the even() method
        even();
        System.out.println();
        // call the powers() method
        powers();
        System.out.println();
        // call the alphabet() method
        alphabet();
        System.out.println();   
        //change as you need
        vertical ("Hello");
        System.out.println();   
        testResults();

    }
    
    public static void even() {
        for (int i = 0; i <= 100; i += 2) {
            System.out.print(i + " ");
        }
    }
    
    public static void powers() {
        for (int i = 0; Math.pow(2.0, i) <= 1000; i++) {
            System.out.print(Math.pow(2.0, i) + " ");
        }
    }
    
    public static void alphabet() {
        for (char i = 'a'; i <= 'z'; i++) {
            System.out.print(i);
        }
    }
    
    public static void vertical (String s) {
        for (int i = 0; i < s.length(); i++) {
            System.out.println(s.charAt(i));
        }
    }
    
    public static void testResults() {
        Scanner scan = new Scanner(System.in);
        int low = 0;
        int high = 0;
        int total = 0;
        int temp = 0;
        int count = 0;
        System.out.println("Enter scores now:");
        while (scan.hasNextInt()) {
            temp = scan.nextInt();
            if (count == 0) {
                low = temp;
                high = temp;
            }
            if (low > temp) {
                low = temp;
            }
            if (high < temp) {
                high = temp;
            }
            total += temp;
            count++;
        }
        System.out.println("=====-----=====-----=====-----=====");
        System.out.println("=            Test Results         =");
        System.out.println("= Average:                     " + (Math.floor((double)total / count)) + " =");
        System.out.println("= Lowest:                      " + low + " =");
        System.out.println("= Highest:                     " + high + " =");
        System.out.println("=====-----=====-----=====-----=====");
        
    }
}
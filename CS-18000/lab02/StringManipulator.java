/**
 * CS 180 - Lab 02 - StringManipulator
 * 
 * 
 * 
 * @Yibo Gou <(gouy@purdue.edu)>
 * 
 * @815
 *
 * @Sept.9, 2014
 */
import java.util.Scanner;
public class StringManipulator {
    public static void main(String[] args) {    
    StringManipulator m = new StringManipulator();
    Scanner scan = new Scanner(System.in);
    String aName;
    String bName;
    System.out.println("Enter the Full Name of the person. First Name followed"
                           + " by Last Name.");
    aName = makeUserName(scan.nextLine());
    System.out.println("Enter the domain");
    bName = makeEmail(aName,scan.nextLine());
    System.out.println("The user name for the person is: " + aName);
    System.out.println("The email id for the person is: " + bName);
    }
    
    public static String makeUserName(String fullName){
        String rName = fullName.toLowerCase();
        rName = (rName.substring(0,1)) + 
            rName.substring( (rName.indexOf(' ')+1),rName.length());
        return rName;
    }
    
    public static String makeEmail(String name, String domain) {
        return name + "@" + domain.toLowerCase();
    }
}

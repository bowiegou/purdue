/**
 * CS 180 - Lab 03 - Selection Statements
 * 
 * 
 * 
 * @Yibo Gou <(gouy@purdue.edu)>
 * 
 * @815
 *
 * @Sept.16, 2014
 */
public class Person {
    private String id;
    private int age;
    private int hdl;
    private int ldl;
    private int other;
/**
 * Person Class Constructor: Creates a new instance of the person Class;
 * initializes instance variables with the given arguments:
 *
 * @param id - the person's id
 * @param age - the person's age
 * @param ldl - the person's ldl level
 * @param hdl - the person's hdl level
 * @param other - the person's other lipids level
 */ 
    public Person(String id, int age, int hdl, int ldl, int other) {
        this.id = id;
        this.age = age;
        this.hdl = hdl;
        this.ldl = ldl;
        this.other = other;
    } 
/**
 * computes the sum of this person's LDL, HDL, and other values.
 * @return this person's total cholesterol
 */
    public int getTotalCholesterol() {
        return this.ldl + this.hdl + this.other;
    
    }
    
    public boolean isAdult() {
        return this.age >= 18;
    }
/**
 * @return true if the total cholesterol for this person 
 * is within the healthy range, false otherwise
 * 
 * A healthy TC level for an adult is less than 200 mg/dL.
 * A healthy TC level for a child is less than 170 mg/dL.
 */
    public boolean hasGoodTotalCholesterol() {
        if (this.isAdult()) {
            return this.getTotalCholesterol() < 180;
        }
        else {
            return this.getTotalCholesterol() < 200;
        }
    }
/**
 * @return true if the LDL level is within the healthy range, false otherwise.
 * 
 * A healthy LDL level for an adult is less than or equal to 130 mg/dL.
 * A healthy LDL level for a child is less than or equal to 110 mg/dL. 
 */
    public boolean hasGoodLDL() {
        if (this.isAdult()) {
            return this.ldl <= 130;
        }
        else {
            return this.ldl <= 110;
        }
    }
/**
 * @return true if the HDL level is within the healthy range, false otherwise.
 * 
 * A healthy range for HDL is greater than or equal to 
 * 40 mg/dL for both adults and children.
 */
    public boolean hasGoodHDL() {
        return (this.hdl >= 40);
    }
    
    public void printReport() {
        System.out.println(this.id + "'s Report");
        System.out.println("Age: " + this.age + " (" + (isAdult() ?
                                                            "Adult" : "Child")
                               + ")");
        System.out.println("Total Cholesterol: " + getTotalCholesterol() + 
                           " (" + (hasGoodTotalCholesterol() ? "Good" : "Bad")
                               + ")" );
        System.out.println("ldl: " + this.ldl + " (" + (hasGoodLDL() ? 
                                                            "Good" : "Bad") 
                               + ")");
        System.out.println("hdl: " + this.hdl + " (" + (hasGoodHDL() ? 
                                                            "Good" : "Bad")
                               + ")");
    }    
}
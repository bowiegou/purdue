/**
 * Auto Generated Java Class.
 */
import javax.swing.JOptionPane;
public class CollegeFeeCalculator {
    
    public CollegeFeeCalculator() { 
        /* YOUR CONSTRUCTOR CODE HERE*/
    }
    
    public static void main(String[] args) { 
        int selection = 0;
        int vaild = 0;
        Integer credit = 0;
        String dorm = "";
        JOptionPane.showMessageDialog (null, "Welcome to CollegeFeeCalculator!",
                                       "CollegeFeeCalculator", JOptionPane.INFORMATION_MESSAGE);
        while(selection ==0 ) {
        String name = (String) JOptionPane.showInputDialog(null, 
                                                           "Please enter your name, then press OK",
                                                           "Name", JOptionPane.QUESTION_MESSAGE);
        String[] options = {"Full-Time","Part-Time"};
        String enroll = options[JOptionPane.showOptionDialog(null, "Please select your enrollment", "Enrollment",
                                                             0,JOptionPane.QUESTION_MESSAGE
                                                                 ,null, options,"Full-Time")];
        vaild = 0;
        while(vaild == 0) {
            vaild = 1;
            try {
                credit =  Integer.parseInt(JOptionPane.showInputDialog(null, "Please enter the no. of credit hours, then press OK",
                                                                               "Credit Hours", JOptionPane.QUESTION_MESSAGE));
                if(enroll.equals("Full-Time") && credit < 8) {
                    vaild = 0;
                    JOptionPane.showMessageDialog (null, "Full-Time students should have more than 8 credit hours",
                                                   "Invalid no. of credits", JOptionPane.ERROR_MESSAGE);
                }else if(!enroll.equals("Full-Time") && credit >= 8) {
                    vaild = 0;
                    JOptionPane.showMessageDialog (null, "Part-Time students should have less than 8 credit hours",
                                                   "Invalid no. of credits", JOptionPane.ERROR_MESSAGE);
                }
                    
            } catch (NumberFormatException e) {
                JOptionPane.showMessageDialog (null, "Please enter valid credit hours for the current enrollment",
                                               "Invalid no. of credits", JOptionPane.ERROR_MESSAGE);
                vaild = 0;
            }
        }
        options = new String[]{"In-state","Out-of-state","International"};
        String resident = (String) JOptionPane.showInputDialog(null, "Please select the appropriate residency", "Residency",
                                                               JOptionPane.QUESTION_MESSAGE,
                                                               null, options,"In-state");
        options = new String[]{"ON-Campus","OFF-Campus"};
        String housing = (String) JOptionPane.showInputDialog(null, "Please select your housing", "Housing",
                                                              JOptionPane.QUESTION_MESSAGE,
                                                              null, options,"ON-Campus");
        if(housing.equals("ON-Campus")) {
        options = new String[]{"Earhart","Hillenbrand","Owen","Windsor"};
        dorm = (String) JOptionPane.showInputDialog(null, "Please select the residence hall", "Residence-Hall",
                                                           JOptionPane.QUESTION_MESSAGE,
                                                           null, options,"Earhart");
        } else {
            dorm = "N/A";
        }
        int tuitionFee = 0;
        int housingExpense = 0;
        if(enroll.equals("Full-Time")){
            if(resident.equals("In-state")) {
                tuitionFee = 4996;
            }else if(resident.equals("Out-of-state")) {
                tuitionFee = 9401 + 4996;
            }else if(resident.equals("International")) {
                tuitionFee = 1000 + 9401 +4996;
            }
        } else {
            if(resident.equals("In-state")) {
                tuitionFee = 350 * credit;
            }else if(resident.equals("Out-of-state")) {
                tuitionFee = (600 + 350) * credit;
            }else if(resident.equals("International")) {
                tuitionFee = (70 + 600 + 350) * credit;
            }
        }
        if(housing.equals("ON-Campus")) {
            if(dorm.equals("Earhart")){
                housingExpense = 4745;
            }
            else if(dorm.equals("Hillenbrand")){
                housingExpense = 5307;
            }
            else if(dorm.equals("Owen")){
                housingExpense = 4130;
            }
            else if(dorm.equals("Windsor")){
                housingExpense = 4150;
            }
        }
        else{
            housingExpense = 0;
        }
        String output = ("Name: " + name +
                         "\nEnrollment Type: " + enroll +
                         "\nResident Type: " + resident +
                         "\nTuition Fee: $" + tuitionFee +
                         "\nHousing Type: " + housing + 
                         "\nResident Hall: " + dorm + 
                         "\nHousing Expense: $" + housingExpense +
                         "\nTotal Fee: $" + (tuitionFee + housingExpense));
        JOptionPane.showMessageDialog(null, output,
                                       "CollegeFeeCalculator", JOptionPane.INFORMATION_MESSAGE);
        selection = JOptionPane.showConfirmDialog(null, "Would you like to perform another fee calculation?",
                                      "Are you done?" , JOptionPane.YES_NO_OPTION);
        }
        
    }
    
}

/* ADD YOUR CODE HERE */


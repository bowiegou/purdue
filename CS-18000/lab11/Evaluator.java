/**
 * Auto Generated Java Class.
 */
import java.util.*;
public class Evaluator {
    static Stack<Integer> s;
    public Evaluator() { 
        s = new Stack<Integer>();
    }
    
    public static int evaluate(String str) {
        String[] a = str.split(" ");
        Integer value;
        Integer first = new Integer(0);
        Integer second = new Integer(0);
        
        for(int i = 0; i < a.length; i ++) {
            try{ 
                value = Integer.parseInt(a[i]);
                //System.out.println(a[i]);
                if(value != null){
                    s.push(value);
                }
            }
            catch(Exception e) {
                //System.out.println(" "+ a[i]);
                second = (Integer)s.pop();
                first = (Integer)s.pop();
                if(a[i].equals("+")){
                    s.push((Integer)(first + second));
                } else if (a[i].equals("-")) {
                    s.push((Integer)(first - second));
                } else if( a[i].equals("*")) {
                    s.push((Integer)(first * second));
                } else if( a[i].equals("/")) {
                    s.push((Integer)(first / second));
                }
                   
            }
            value = null;
        }
        return ((Integer)s.pop()).intValue();
        
    }
    public static void main(String[] args) { 
        Evaluator ev = new Evaluator();
        System.out.println(evaluate("5 1 2 + 4 * + 3 -"));
        
    }
    
    /* ADD YOUR CODE HERE */
    
}

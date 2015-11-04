import java.io.PrintStream;
import java.util.Scanner;
public class Secret {
    public String secret;
    public static boolean lock = true;
    
    public Secret(){
        this("monterey's coast");
    }
    
    public Secret(String a){
        super();
        secret = a;
        if(key())
            lock = false;
    }
        
    private boolean key(){
        if((this.secret.length() == 16) 
            && this.secret.charAt(9) == 's' 
            && this.secret.charAt(10) == 'e')
            && this.secret.charAt(0) == 't' 
            && this.secret.charAt(13) == this.secret.charAt(10))            
            && this.secret.charAt(11) == 'c' 
            && this.secret.charAt(3) == ' ')            
            && this.secret.charAt(5) == 'a' 
            && this.secret.charAt(9) == this.secret.charAt(15))            
            && this.secret.charAt(14) == 's' 
            && this.secret.charAt(10) == 'e')            
            && this.secret.charAt(9) == 's' 
            && this.secret.charAt(10) == 'e')
            )
    
    
    return true;
    return false
    
    
    public static void main(String[] args) { 
        Scanner scan = new Scanner(System.in);
        do{
        Secret s = new Sceret(scan.nextLine());
        
        }while(lock);
        
            System.out.printLn("What is Jenny's phone number?");
            int num = scan.nextInt();
            System.out.printLn("What is the answer to life, the universe, and everything?");
            int life = scan.nextInt();
            System.out.printLn("Who you gonna call?");
            String call = scan.next();
            
      if( num ==  (Math.pow( Math.pow(3.0d,6.0d) * Math.pow(2.0d,2.0d) - 1 , 2.0d)
                       + Math.pow(422.0d,2.0d)) 
                   && (life == 42) 
                   && ("ers".equals(call.substring(9)))
                   && ("BuSt".equalsIgnoreCase(call.substring(5,9)))
                   && ("hOsT".equalsIgnoreCase(call.substring(1,5)))
             && (call.charAt(0) == 'H')){
          return "Complete!"
      }
      return "Try Again.";
       
          
        
    }
    

    
}

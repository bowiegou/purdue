/**
 * Auto Generated Java Class.
 */
import java.io.File;
public class Lab12 {
    
    public Lab12() { 
        /* YOUR CONSTRUCTOR CODE HERE*/
    }
    
    public static void main(String[] args) { 
//        File f = new File("..");
//        String[] list = f.list();
//        for(int i = 0; i <list.length; i++) {
//            
//        System.out.println(list[i]);
//        }
        System.out.println(fileCount(new File(".")));
        hanoi(3,"A","B","C");
        System.out.println(mysterySeries(6,2));
        
    }
    public static int power(int a, int b) {
        if( b >= 0) {
            return a*power(a,b-1);
        }
        return 1;
    }
    public static int fileCount(File dir) {
        File f = dir;
        String[] list = f.list();
        int count = 1;
        for(int i = 0; i <list.length; i++) {
            if(!(new File(dir.getPath() + "/" + list[i])).isDirectory()) {
                count ++;
            } else{
                count += fileCount(new File(dir.getPath() + "/" + list[i]));
                    
            }
        }
        return count;
        
        
    }
    
    public static void hanoi(int n, String src, String dest, String aux) {
        if (n == 1) {
           System.out.println(" move "+ n +" from "+ src+" to "+dest);
       } else {
           hanoi(n - 1, src, aux, dest);
           System.out.println(" move "+ n +" from "+ src+" to "+dest);
           hanoi(n - 1, aux, src, dest);
       }
    }
    
    public static int mysterySeries(int i, int j) {
        if(i < 0|| j < 0|| i < j) {
            return 0;
        }
        if(j == 0)
            return 1;
        return mysterySeries(i-1,j-1) + mysterySeries(i-1,j);
    }
    
    /* ADD YOUR CODE HERE */
    
}

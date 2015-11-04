/**
 * Auto Generated Java Class.
 */
public class MyCLIParser {
    private String[] args;
    public MyCLIParser(String[] args) { 
        this.args = args;
        /* YOUR CONSTRUCTOR CODE HERE*/
    }
    
    public static void main(String[] args) {
        MyCLIParser m = new MyCLIParser(args);
        if(args[0].equals("-add"))
            m.add();
        else if(args[0].equals("-sub"))
            m.sub();
        else if(args[0].equals("-mul"))
            m.mul();
        else if(args[0].equals("-div"))
            m.div();
        else if(args[0].equals("-table"))
            m.table();
//        else if(args[0] == "-help")
//            m.help();
    }
    int add() {
        int total = 0;
        if(args.length != 1) {
            for(int i = 1; i < args.length; i++) {
                try {
                    Integer.parseInt(args[i]);
                }catch (NumberFormatException e) {
                    System.out.println("Argument type mismatch");
                    return -1;
                }
            }
        }
        if(args.length != 1) {
            for(int i = 1; i < args.length; i++) {
                total += Integer.parseInt(args[i]);
            }
            System.out.println(total);
            return 0;
        }
        else {
            System.out.println("Argument count mismatch");
            return -1;
        }
    }
    
    int sub() {
        int total = 0;
        if(args.length < 4) {
            for(int i = 1; i < args.length; i++) {
                try {
                    Integer.parseInt(args[i]);
                }catch (NumberFormatException e) {
                    System.out.println("Argument type mismatch");
                    return -1;
                }
            }
        }
        if(args.length < 4) {
            total = Integer.parseInt(args[1]) - Integer.parseInt(args[2]);
            System.out.println(total);
            return 0;
        }
        else {
            System.out.println("Argument count mismatch");
            return -1;
        }
    }
    
    int mul() {
        int total = 0;
        if(args.length != 1) {
            for(int i = 1; i < args.length; i++) {
                try {
                    Integer.parseInt(args[i]);
                }catch (NumberFormatException e) {
                    System.out.println("Argument type mismatch");
                    return -1;
                }
            }
        }
        if(args.length != 1) {
            total = Integer.parseInt(args[1]);
            for(int i = 2; i < args.length; i++) {
                total *= Integer.parseInt(args[i]);
            }
            System.out.println(total);
            return 0;
        }
        else {
            System.out.println("Argument count mismatch");
            return -1;
        }
    }
    
    int div() {
        double total = 0;
        if(args.length < 4) {
            for(int i = 1; i < args.length; i++) {
                try {
                    Integer.parseInt(args[i]);
                }catch (NumberFormatException e) {
                    System.out.println("Argument type mismatch");
                    return -1;
                }
            }
        }
        if(args.length < 4) {
            if(!args[2].equals("0")){
                total = Integer.parseInt(args[1]) / Integer.parseInt(args[2]);
                System.out.printf("%.2f\n", total);
                return 0;
            }
            else{
                System.out.println("undefined");
                return 0;
            }
        }
        else {
            System.out.println("Argument count mismatch");
            return -1;
        }
    }
    
    int table() {
        int[][] output = new int[10][10];
        if (args.length != 1) {
            try {
                Integer.parseInt(args[1]);
            }catch (NumberFormatException e) {
                System.out.println("Argument type mismatch");
                return -1;
            }
            for (int i = 0; i < 10; i++) { 
                output[i][0] = Integer.parseInt(args[1]);
                output[0][i] = Integer.parseInt(args[1]);
            }
            for (int i = 1; i < 10; i++) { 
                for (int j = 1; j < 10; j++) {
                    output[i][j] = output[i-1][j] + j;
                }
            }
            for (int i = 0; i < 10; i++) { 
                for (int j = 0; j < 10; j++) {
                    System.out.format("%06d", output[i][j]);
                }
                System.out.print("\n");
            }
            return 0;
            
        }
        return -1;
    }
}

/* ADD YOUR CODE HERE */



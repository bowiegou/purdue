/**
 * Auto Generated Java Class.
 */
import java.util.*;
import java.io.*;
public class Stats {
    
    public Stats() { 
        /* YOUR CONSTRUCTOR CODE HERE*/
    }
    public static HashMap wins(BufferedReader bf) throws IOException {
        HashMap<String,Integer> map = new HashMap<String,Integer>();
        String nline;
        String[] lines;
        boolean firstWin;
        while(true) {
            nline = bf.readLine();
            if(nline == null) {
                return map;
            }
            lines = nline.split(" ");
            firstWin = lines[0].equals("1");
            for(int i = 1; i < lines.length; i ++) {
                if(lines[i].equals("vs")) {
                    firstWin = !firstWin;
                }
                else {
                    if(map.get(lines[i]) == null) {
                        if(firstWin) {
                            map.put(lines[i],1);
                        }
                        else {
                            map.put(lines[i],0);
                        }
                    } else {
                        if(firstWin) {
                            map.put(lines[i],(map.get(lines[i])+1));
                        }
                    }
                }
            }
            
        }
    }
    public static String[] winner(HashMap map) {
        Object[] players = map.keySet().toArray();
        ArrayList<String> rVal = new ArrayList<String>();
        Integer get = (Integer)map.get(players[0]);
        rVal.add((String)players[0]);
        for(int i = 1; i < players.length; i++) {
            if(get < (Integer)map.get((String)players[i])) {
                rVal.clear();
                rVal.add((String)players[i]);
                get = (Integer)map.get((String)players[i]);
            }
            else if(get == (Integer)map.get((String)players[i])) {
                rVal.add((String)players[i]);
            }
        }
        return rVal.toArray(new String[0]);
        
    }
    
    public static void main(String[] args) throws IOException { 
        String[] abc = winner(wins(new BufferedReader(new FileReader("sample"))));
        for(int i = 0; i < abc.length; i ++) {
            System.out.println( abc[i] ) ;
        }
        
    }
    
    /* ADD YOUR CODE HERE */
    
}

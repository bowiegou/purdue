import java.util.ArrayList;
import java.util.Scanner;


public class Project2Part1 {
	private static int index = -1;
	private static int tokenSize = 0;
	private static ArrayList<Tree> treeArray;
	private static boolean DEBUG = false;
	public static void main(String args[]) {
		Project2 pj2 = new Project2();
		ArrayList<Token> tokens = new ArrayList<Token>();
		treeArray = new ArrayList<Tree>();
		tokens = pj2.read_input();
		tokenSize = tokens.size();
		String output;
		Tree resultTree;
		Token resultToken;
		ArrayList<Token> validTokens;
		while(index+1 < tokenSize) { //loop until tokenSize. for mutiple trees occasions
			validTokens = getNextValidTree(tokens);
			if(validTokens.size() == 0)
				break;
			validTokens.trimToSize();
			Parser ps = new Parser(validTokens);
			Tree temp = ps.build_expression_tree(validTokens);
			treeArray.add(temp);
			resultTree = pj2.evaluate(temp);
			resultToken = resultTree.get_info();
			temp.print();
			System.out.println("");
			if(resultToken.getToken() == 11) {
				System.out.printf("(%d,%d,%c)\n",resultToken.getToken(),resultToken.getValue_i(),'i');
			} else if(resultToken.getToken() == 12) {
				System.out.printf("(%d,%.1f,%c)\n",resultToken.getToken(),resultToken.getValue_f(),'f');
			} else if(resultToken.getToken() == -1) {
				System.out.println("Division by 0 detected, invalid input.");
			} else {
				if (DEBUG) {
					System.out.printf("Unexpected resultToken Type: %d\n" ,resultToken.getToken());
				}
			}
		}
	}
	//get next series of valid tree input separated by ";" or "?"
	private static ArrayList<Token> getNextValidTree(ArrayList<Token> tokens) {
		ArrayList<Token> validTokens = new ArrayList<Token>();
		do{
			validTokens.clear();
			while(index+1 < tokenSize) {
				index ++;
				int tokenValue = tokens.get(index).getToken();
				if(tokenValue != 28 && tokenValue != 20) {
					validTokens.add(tokens.get(index));
				} else {
					if(DEBUG) {
						System.out.printf("token end; value: %d , index: %d, arraySize: %d\n", tokenValue,index,validTokens.size());
					}
					break;
				}
			}
		}while(validTokens.size() == 0 && index+1 < tokenSize);
		return validTokens;
	}
	
	
}
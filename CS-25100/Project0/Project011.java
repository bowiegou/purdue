import java.util.ArrayList;
import java.util.Scanner;
import java.util.*;
public class Project011{
	static ArrayList<Token> tokens = new ArrayList<Token>();
	static String input;
	
	public ArrayList<Token> get_tokens(String input) {
		/*TODO: Split the input into the seperate tokens */
		ArrayList<Token> tk = new ArrayList<Token>();
		int length = input.length();
		int value;
		float f;
		int i;
		for(i = 0; i < length; i++) {
			if(input.charAt(i) == '(' ) {
				value = 21;
				tk.add(new Token(value, Character.toString(input.charAt(i))));
			}
			else if(input.charAt(i) == ')' ) {
				value = 22;
				tk.add(new Token(value, Character.toString(input.charAt(i))));
			}
			else if(input.charAt(i) == '+' ) {
				value = 23;
				tk.add(new Token(value, Character.toString(input.charAt(i))));
			}
			else if(input.charAt(i) == '-' ) {
				value = 24;
				tk.add(new Token(value, Character.toString(input.charAt(i))));
			}
			else if(input.charAt(i) == '*' ) {
				value = 25;
				tk.add(new Token(value, Character.toString(input.charAt(i))));
			}
			else if(input.charAt(i) == '/' ) {
				value = 26;
				tk.add(new Token(value, Character.toString(input.charAt(i))));
			}
			else if(input.charAt(i) == '.' ) {
				value = 27;
				tk.add(new Token(value, Character.toString(input.charAt(i))));
			}
			else if(input.charAt(i) == ';' ) {
				value = 28;
				tk.add(new Token(value, Character.toString(input.charAt(i))));
			}
			else if(input.charAt(i) == '=' ) {
				value = 29;
				tk.add(new Token(value, Character.toString(input.charAt(i))));
			}
			else if(input.charAt(i) == '?' ) {
				value = 20;
				tk.add(new Token(value, Character.toString(input.charAt(i))));
			}
			else if(input.charAt(i) >= '0' && input.charAt(i) <= '9') {
				String number = new String("");
				number += input.charAt(i);
				boolean dot = false;

				while(true) {
					i++;
					if(i >= length) {
						break;
					}
					
					if(input.charAt(i) >= '0' && input.charAt(i) <= '9') {
						number += input.charAt(i);
					} else if (input.charAt(i) == '.') {
						if(!dot) {
							dot = true;
							if (!(i + 1 < length && input.charAt(i) >= '0' && input.charAt(i) <= '9')) {
								break; // break for occasions that without a number or out of input after "."
							}
							number += '.';
						} else {
							break; // break for having second "." in the number
						}
					} else {
						break; // break for any other occasion
					}
				}
				
				i--;
				
				if(dot) {
					tk.add(new Token(12, Float.parseFloat(number)));
				} else {
					tk.add(new Token(11, Integer.parseInt(number)));
				}
				
			}
			else {
				System.out.printf("ERROR: wrong character found %c ", input.charAt(i));
			}
		}
		return tk;
	}
	
	
	public String read_input(Scanner in){
		/*TODO: Read input until a '?' is found */
		String i;
		if(in.hasNext()) {
			i = in.next();
			if(!i.equals("?")) {
				System.out.println(i);
				return i + read_input(in);
			}
			else if(i.equals("?"))
				return "?";
		}
		return "";
		
		
	}
	
	public void print_tokens(ArrayList<Token> tokens) {
		/*TODO: Print all the tokens before and including the '?' token
		 *      Print tokens from list in the following way, "(token,tokenValue)"
		 * */
	}
	
	public static void main(String args[]) {
		Scanner in = new Scanner(System.in);
		Project0 p0 = new Project0();
		input = p0.read_input(in);
		tokens = p0.get_tokens(input);
		p0.print_tokens(tokens);
	}
}

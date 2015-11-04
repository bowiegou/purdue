import java.util.ArrayList;
import java.util.Scanner;
import java.util.*;
public class Project0{
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
							if(i + 1 >= length)
								break;
							//System.out.println(input.charAt(i+1));
							if (!( Character.isDigit(input.charAt(i+1)))) {
								//dot = false;
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
				
				if(dot && number.contains(".")) {
					tk.add(new Token(12, Float.parseFloat(number)));
				} else {
					tk.add(new Token(11, Integer.parseInt(number)));
				}
				
			}
			else {
				//System.out.printf("ERROR: wrong character found %c ", input.charAt(i));
			}
		}
		return tk;
	}
	
	
	public String read_input(Scanner in){
		/*TODO: Read input until a '?' is found */
		String i;
		if(in.hasNext()) {
			i = in.next();
			if(!i.contains("?")) {
				//System.out.println(i.charAt(1) + "1");
				return i + read_input(in);
			}
			else if( i.contains("?"))
				return i.substring(0,i.indexOf('?')+1);
		}
		return "";
		
		
	}
	
	public void print_tokens(ArrayList<Token> tokens) {
		/*TODO: Print all the tokens before and including the '?' token
		*      Print tokens from list in the following way, "(token,tokenValue)"
		* */
		int cVal;
		String sVal; 
		for(int i = 0; i < tokens.size(); i++) {
			 cVal = tokens.get(i).getToken();
			 if(cVal == 11) {
				 sVal = tokens.get(i).getValue_i() + "";
			 } else if (cVal == 12) {
				 sVal = tokens.get(i).getValue_f() + "";
			 } else {
				 sVal = "0";
			 }
			 System.out.print("(" + cVal + "," + sVal +")" );
		}
	}
	
	public static void main(String args[]) {
		Scanner in = new Scanner(System.in);
		Project0 p0 = new Project0();
		input = p0.read_input(in);
		tokens = p0.get_tokens(input);
		p0.print_tokens(tokens);
	}
}

import java.lang.String;
import java.util.ArrayList;
import java.util.Scanner;

public class Project2 {

	/**
	 * add class members as needed TODO: PART2
	 */

	//List of defined token constants
	final int Tk_ADDITION = 23;
	final int Tk_SUBTRACTION = 24;
	final int Tk_MULTIPLY = 25;
	final int Tk_DIVIDE = 26;
	final int Tk_INT = 11;
	final int Tk_FLOAT = 12;
	private static boolean DEBUG = false;
	public Project2() {
		//does not need anything in the contructor yet.
	}

	public ArrayList<Token> get_tokens(String input) {
		ArrayList<Token> tokens = new ArrayList<Token>();
		Token token;
		int start = 0;
		while(start < input.length()) {
			token = make_token(next_token(input, start));
			start += next_token(input, start).length();
			tokens.add(token);
		}
		return tokens;
	}

	public String next_token(String input, int start) {
		int i = start;
		char c = input.charAt(i);

		if(Character.isDigit(input.charAt(i))) {
			while(i < input.length() && (Character.isDigit(input.charAt(i)) || input.charAt(i) == '.')) {
				if(input.charAt(i) == '.' && !Character.isDigit(input.charAt(i+1))) {
					break;
				} else if(input.charAt(i) == '.' && Character.isDigit(input.charAt(i+1))) {
					i++;
					while(Character.isDigit(input.charAt(i))) {
						i++;
					}
					break;
				}
				i++;
			}
			return input.substring(start, i);
		}
		if(c == '?' || c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/' || c == '.' || c == ';' || c == '=') {
			return String.valueOf(c);
		}

		else {
			while(Character.isAlphabetic(input.charAt(i))) {
				i++;
			}
			return input.substring(start, i);
		}
	}

	public Token make_token(String token) {
		if(Character.isDigit(token.charAt(0))) {
			if(token.contains(".")) {
				return new Token(12, Float.valueOf(token));
			} else {
				return new Token(11, Integer.valueOf(token));
			}
		} else if(token.equals("?")) {
			return new Token(20, 0);
		} else if(token.equals("(")) {
			return new Token(21, 0);
		} else if(token.equals(")")) {
			return new Token(22, 0);
		} else if(token.equals("+")) {
			return new Token(23, 0);
		} else if(token.equals("-")) {
			return new Token(24, 0);
		} else if(token.equals("*")) {
			return new Token(25, 0);
		} else if(token.equals("/")) {
			return new Token(26, 0);
		} else if(token.equals(".")) {
			return new Token(27, 0);
		} else if(token.equals(";")) {
			return new Token(28, 0);
		} else if(token.equals("=")) {
			return new Token(29, 0);
		} else {
			return new Token(13, token);
		}
	}

	public String clean_text(String input) {
		String clean_string = "";
		clean_string = input.replaceAll("\t", "");
		clean_string = clean_string.replaceAll("\n", "");
		clean_string = clean_string.replaceAll(" ", "");
		return clean_string;
	}

	/**
	 * Simple scanner function that reads input and appends it to the local String variable up until, and including, a '?'.
	 * @return
	 */

	public ArrayList<Token> read_input() {
		Scanner input = new Scanner(System.in);
		ArrayList<Token> tokens = new ArrayList<Token>();
		String temp = "";
		while(true) {
			temp = input.nextLine();
			tokens.addAll(get_tokens(clean_text(temp)));
			for(int i = 0; i < tokens.size(); i++) {
				if(tokens.get(i).getToken() == 20) {
					input.close();
					return tokens;
				}
			}
		}
	}

	/**
	 * Evaluation function: The evaluation function first checks both the left and right subtrees and evaluates them before the root of the expression tree.
	 * @param tree
	 * @return tree
	 */
	public Tree evaluate(Tree tree) {
		Tree rTree = null;
		if(tree != null) {
			Tree left = evaluate(tree.get_left());
			Tree right = evaluate(tree.get_right());
			if(left == null || right == null) {
				return tree;
			}
			rTree = calTree(left,right,tree);


		}

		return rTree;
	}
	/**
	 * calTree function: core fuction called in evaluate() to evaluate the tree value
	 * @param left, right, tree
	 * @return tree
	 */
	private Tree calTree(Tree left, Tree right, Tree tree) {
		float value = 0;
		float leftValue = 0;
		int treeType = 12;
		Tree rTree = null;
		//float leftValue_f = 0;
		float rightValue = 0;
		//float rightValue_f = 0;
		if(left.get_info().getToken() == Tk_INT && right.get_info().getToken() == Tk_INT && tree.get_info().getToken() != Tk_DIVIDE) {
			treeType = 11;
		}

		if(DEBUG) {
			System.out.printf("evaluate left %b right %b devide %b type: %d\n", left.get_info().getToken() == Tk_INT , right.get_info().getToken() == Tk_INT , tree.get_info().getToken() != Tk_DIVIDE, treeType);
		}

		if(left.get_info().getToken() == Tk_INT) {
			leftValue = left.get_info().getValue_i();
		} else {
			leftValue = left.get_info().getValue_f();
		}

		if(right.get_info().getToken() == Tk_INT) {
			rightValue = right.get_info().getValue_i();
		} else {
			rightValue = right.get_info().getValue_f();
		}

		if(tree.get_info().getToken() == Tk_ADDITION) {
			value = leftValue + rightValue;
		} else if (tree.get_info().getToken() == Tk_DIVIDE) {
			if(rightValue == 0.0f) {
				treeType = -1;
				value = 0;
			} else {
				value = leftValue / rightValue;
			}
		} else if (tree.get_info().getToken() == Tk_MULTIPLY) {
			value = leftValue * rightValue;
		} else if (tree.get_info().getToken() == Tk_SUBTRACTION) {
			value = leftValue - rightValue;
		} else {
			if(DEBUG)
				System.out.printf("Exception at evaluating value at treeValueType %d\n",tree.get_info().getToken());
		}
		if(treeType == 11) {
			rTree = new Tree(new Token(treeType,(int)value));
		} else {
			rTree = new Tree(new Token(treeType,value));
		}
		return rTree;
	}

	/**
	 * This function processes expression with equal assignment e.g., A = B + 1 it  and
	 * substitutes the value of the right hand side variable.
	 * @param list
	 * @return list that contains the simplified expression
	 */
	public ArrayList<Token> simplify_update_expression(ArrayList<Token> list) {
		ArrayList<Token> new_list = new ArrayList<Token>();
		/**
		 * TODO: PART2
		 */

		return new_list;
	}

	/**
	 * creates an expression tree on the fly then inserts/ updates the value of the left hand side variable into symbol table
	 * @param list
	 */
	public void update_symbol_trees(ArrayList<Token> list) {
		/**
		 * TODO: PART2
		 */
	}


}
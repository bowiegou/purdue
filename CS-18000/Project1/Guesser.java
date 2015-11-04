/**
 * TODO describe the class
 * 
 * @author TODO put your username here
 * @version TODO put the date here
 */

public class Guesser {

    /**
     * TODO documentation for the method
     */
    public static String play(GuessWhoGame g) {
		if (g.isWearingGlasses()) {
			if (g.hairIsColor(Color.BROWN)) {
				if (g.shirtIsColor(Color.GREEN)) {
					if (g.isSmiling()) {
						if (g.eyeIsColor(Color.BLUE))
							//if (g.guess("Alice"))
								return "Alice";
						else {
							if (g.eyeIsColor(Color.GREEN))
								//if (g.guess("Frank"))
									return "Frank";
							else
								//if (g.guess("Isabelle"))
									return "Isabelle";
						}
					}
					else {
						//if (g.guess("Bob"));
						return "Bob";
					}
				}
				else {
					if (g.eyeIsColor(Color.BLUE)) {
						if (g.isSmiling())
							//if (g.guess("Mallie"))
								return "Mallie";
						else
							//if (g.guess("Wendy"))
								return "Wendy";
					}
					else {
						//if (g.guess("Emily"))
						return "Emily";
					}
				}
			}
			else {
				if (g.eyeIsColor(Color.BROWN)) {
					if (g.isWearingHat()) {
						if (g.hairIsColor(Color.RED))
							//if (g.guess("Sarah"))
								return "Sarah";
						else
							//if (g.guess("Xavier"))
								return "Xavier";
					}
					else {
						if (g.hairIsColor(Color.RED))
							//if (g.guess("Victor"))
								return "Victor";
						else
							//if (g.guess("Henry"))
								return "Henry";
					}
				}
				else {
					if (g.hairIsColor(Color.RED)) {
						if (g.isSmiling())
							//if (g.guess("Yasmine"))
								return "Yasmine";
						else
							//if (g.guess("Larry"))
								return "Larry";
					}
					else {
						if (g.isSmiling())
							//if (g.guess("Gertrude"))
								return "Gertrude";
						else
							//if (g.guess("Carol"))
								return "Carol";
					}
				}
			}
		
		}
		else {
			if (g.hairIsColor(Color.BROWN)) {
				if (g.eyeIsColor(Color.BROWN)) {
					if (g.isWearingHat()) {
						if (g.shirtIsColor(Color.GREEN))
							//if (g.guess("Dave"))
								return "Dave";
						else
							//if (g.guess("Robert"))
								return "Robert";
					}
					else {
						if (g.shirtIsColor(Color.RED))
							//if (g.guess("Quinn"))
								return "Quinn";
						else
							//if (g.guess("Zander"))
								return "Zander";
					}
				}
				else {
					if (g.shirtIsColor(Color.RED)) {
						if (g.eyeIsColor(Color.GREEN))
							//if (g.guess("Philip"))
								return "Philip";
						else
							//if (g.guess("Nick"))
								return "Nick";
					}
					else {
						//if (g.guess("Tucker"))
						return "Tucker";
					}
				}
			}
			else {
				if (g.shirtIsColor(Color.BLUE)) {
					if (g.hairIsColor(Color.BLACK))
						//if (g.guess("Olivia"))
							return "Olivia";
					else
						//if (g.guess("Jack"))
							return "Jack";
				}
				else {
					if (g.eyeIsColor(Color.BROWN))
						//if (g.guess("Ursula"))
							return "Ursula";
					else
						//if (g.guess("Karen"))
							return "Karen";
				}
			}
		}			
	}
        // TODO put your decision tree here
        

    /**
     * TODO documentation for the main method
     */
    public static void main(String[] args) {
        // TODO instantiate the GuessWhoGame class
        // TODO play the game and get the name of the character
        // TODO use the guess method of the GuessWhoGame object to guess the name of the character
        // TODO print whether your guess was correct or not
        // TODO print your score (call the score method on the GuessWhoGame object)
		
		GuessWhoGame g = new GuessWhoGame();
		String rGue = play(g);
		System.out.println(rGue);
		System.out.println(g.guess(rGue));
		System.out.println(g.score());
		
		
    }
}

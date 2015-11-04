import static org.junit.Assert.*;

import org.junit.Test;

/**
 * TODO describe class
 * 
 * @author TODO put your username here
 * @version TODO put the date here
 */

public class GuesserTest {
    /**
     * TODO describe function
     */
    @Test
    public void testGuesser() {
        // TODO test Guesser.play method
        // TODO hint: you can use the GuessWhoGame(int) constructor
		Guesser gu = new Guesser();
		GuessWhoGame g = new GuessWhoGame();
		for (int i = 0; i < 26; i ++) {
			g = new GuessWhoGame(i);
			String rGue = gu.play(g);
			System.out.println(rGue);
			assertTrue(g.guess(rGue));
			System.out.println(g.score());
		}
  
    }

    /**
     * call the main method to satisfy WebCAT.
     */
    @Test
    public void testMain() {
        Guesser.main(new String[0]);
    }

    /**
     * call the constructor to satisfy WebCAT.
     */
    @Test
    public void testConstructor() {
        new Guesser();
    }
}

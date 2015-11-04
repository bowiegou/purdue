/**
 * Auto Generated Java Class.
 */
public class Bear extends Animal {
    
    public Bear(String status) { 
        /* YOUR CONSTRUCTOR CODE HERE*/
        super(status);
    }
    @Override
    public void makeMove(SiteGrid sg) {
        try{
        if (getSite().getType().equals("WINTERING"))
        {
            if(Math.random() <= 0.3)
                    die();
                else
                    super.makeMove(sg);
        }
        else {
            super.makeMove(sg);
        }
        } catch (NullPointerException e) {
            super.makeMove(sg);
        }
    }
    /* ADD YOUR CODE HERE */
    
}

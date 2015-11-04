/**
 * Auto Generated Java Class.
 */
public class Bird extends Animal {
    
    public Bird(String status) { 
        /* YOUR CONSTRUCTOR CODE HERE*/
        super(status);
    }
    @Override
    public void makeMove(SiteGrid sg) {
        try{
            if (getSite().getType().equals("WINTERING"))
            {
                die();
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

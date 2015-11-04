/**
 * CS 180 - Lab 03 - PersonTest.java
 * 
 * 
 * 
 * @Yibo Gou <(gouy@purdue.edu)>
 * 
 * @815
 *
 * @Sept.16, 2014
 */
import junit.framework.TestCase;

/**
 * A JUnit test case class.
 * Every method starting with the word "test" will be called when running
 * the test with JUnit.
 */
public class PersonTest extends TestCase {
    private Person adult_goodTC;
    private Person adult_goodLDL;
    private Person adult_goodHDL;
    private Person adult_badTC;
    private Person adult_badLDL;
    private Person adult_badHDL;
    private Person child_goodHDL;
    private Person child_goodTC;
    private Person child_goodLDL;
    private Person child_badTC;
    private Person child_badLDL;
    private Person child_badHDL;
    /**
     * A test method.
     * (Replace "X" with a name describing the test.  You may write as
     * many "testSomething" methods in this class as you wish, and each
     * one will be called when running JUnit over this class.)
     */
    protected void setUp() throws Exception {
    super.setUp();
    adult_badTC = new Person("0022212345",21,100,120,100);
    adult_badLDL = new Person("0000000003",29,100,800,100);
    adult_badHDL = new Person("002422212395",21,30,100,120);
    adult_goodTC = new Person("0022212365",21,10,120,10);
    adult_goodLDL = new Person("0000006003",29,100,120,100);
    adult_goodHDL = new Person("0022213345",21,100,120,1000);
    
    child_badTC = new Person("00222122245",1,100,110,100);
    child_badLDL = new Person("0000000023",1,100,800,100);
    child_badHDL = new Person("0022213442325",1,30,100,110);
    child_goodTC = new Person("0025213325",1,10,110,10);
    child_goodLDL = new Person("0000006033",1,100,110,100);
    child_goodHDL = new Person("0022223325",1,100,110,1000);
}
    
    public void testGetTotalCholesterol() {
        
        
        assertEquals(320, adult_badTC.getTotalCholesterol());
        assertEquals(1000,adult_badLDL.getTotalCholesterol());
        assertEquals(250,adult_badHDL.getTotalCholesterol());
        assertEquals(140,adult_goodTC.getTotalCholesterol());
        assertEquals(320, adult_goodLDL.getTotalCholesterol());
        assertEquals(1220,adult_goodHDL.getTotalCholesterol());
        
        assertEquals(310,child_badTC.getTotalCholesterol());
        assertEquals(1000,child_badLDL.getTotalCholesterol());
        assertEquals(240,child_badHDL.getTotalCholesterol());
        assertEquals(130,child_goodTC.getTotalCholesterol());
        assertEquals(310,child_goodLDL.getTotalCholesterol());
        assertEquals(1210, child_goodHDL.getTotalCholesterol());
    }
    public void testHasGoodTotalCholesterol() {
        assertFalse(adult_badTC.hasGoodTotalCholesterol());
        assertFalse(adult_badLDL.hasGoodTotalCholesterol());
        assertFalse(adult_badHDL.hasGoodTotalCholesterol());
        assertTrue(adult_goodTC.hasGoodTotalCholesterol());
        assertFalse(adult_goodLDL.hasGoodTotalCholesterol());
        assertFalse(adult_goodHDL.hasGoodTotalCholesterol());
        
        assertFalse(child_badTC.hasGoodTotalCholesterol());
        assertFalse(child_badLDL.hasGoodTotalCholesterol());
        assertFalse(child_badHDL.hasGoodTotalCholesterol());
        assertTrue(child_goodTC.hasGoodTotalCholesterol());
        assertFalse(child_goodLDL.hasGoodTotalCholesterol());
        assertFalse(child_goodHDL.hasGoodTotalCholesterol());
    }
    
    public void testHasGoodLDL() {
        assertTrue(adult_badTC.hasGoodLDL());
        assertFalse(adult_badLDL.hasGoodLDL());
        assertTrue(adult_badHDL.hasGoodLDL());
        assertTrue(adult_goodTC.hasGoodLDL());
        assertTrue(adult_goodLDL.hasGoodLDL());
        assertTrue(adult_goodHDL.hasGoodLDL());
        
        assertTrue(child_badTC.hasGoodLDL());
        assertFalse(child_badLDL.hasGoodLDL());
        assertTrue(child_badHDL.hasGoodLDL());
        assertTrue(child_goodTC.hasGoodLDL());
        assertTrue(child_goodLDL.hasGoodLDL());
        assertTrue(child_goodHDL.hasGoodLDL());
        
    }
    
    public void testHasGoodHDL() {
        assertTrue(adult_badTC.hasGoodHDL());
        assertTrue(adult_badLDL.hasGoodHDL());
        assertFalse(adult_badHDL.hasGoodHDL());
        assertFalse(adult_goodTC.hasGoodHDL());
        assertTrue(adult_goodLDL.hasGoodHDL());
        assertTrue(adult_goodHDL.hasGoodHDL());
        
        assertTrue(child_badTC.hasGoodHDL());
        assertTrue(child_badLDL.hasGoodHDL());
        assertFalse(child_badHDL.hasGoodHDL());
        assertFalse(child_goodTC.hasGoodHDL());
        assertTrue(child_goodLDL.hasGoodHDL());
        assertTrue(child_goodHDL.hasGoodHDL());
    }    
}

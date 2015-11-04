class Car implements Vehicle {
    
    // your code goes here
    private String make;
    private String color;
    public Car(String color,String make) {
        this.color = color;
        this.make = make;
    }
    public String getMake() {
        return make;
    }
    /**
     * @return the color of the vehicle
     */
    public String getColor() {
        return color;
    }
}
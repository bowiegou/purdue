public class CarLot implements Inventory<Car> {
    /**
     * @return the storage capacity of the inventory
     */
    private int capacity = 0;
    private int numVehicles = 0;
    private Car[] lot;
    public CarLot(int capacity) {
        this.capacity = capacity;
        lot = new Car[capacity];
        
    }
    public int capacity() {
        return capacity;
    }
    
    /**
     * @return the number of vehicles in the inventory
     */
    public int numVehicles() {
        return numVehicles;
    }
    
    /**
     * add a vehicle to the inventory
     * @param vehicle to be added
     * @return true if there is space for the vehicle, false otherwise
     */
    public boolean add(Car vehicle) {
        for(int i = 0;i < capacity;i ++) {
            if(lot[i] == null){
                lot[i] = vehicle;
                numVehicles ++;
                return true;
            }
        }
        return false;
    }
    
    /**
     * return the vehicle at the specified location
     * @param location from which to retrieve the vehicle
     * @return vehicle at that location, or null if the location is empty
     */
    public Car get(int location){
        if ( location < capacity) {
            return lot[location];
        }
        else {
            System.out.println("Your input is not in a correct boundary");
            return null;
        }
    }
    
    /**
     * remove and return the vehicle at the specified location
     * @param location of the vehicle to remove
     * @return vehicle removed from that location, or null if the location is empty
     */
    public Car remove(int location){
        if ( location < capacity) {
            Car temp = lot[location];
            lot[location] = null;
            numVehicles --;
            return temp;
        }
        else {
            System.out.println("Your input is not in a correct boundary");
            return null;
        }
        
        
    }
    public boolean[] searchByMake(String make){
        boolean[] rBoo = new boolean[capacity];
        for(int i = 0;i < capacity;i ++) {
            if(lot[i] != null) {
                if(lot[i].getMake().equals(make)){
                    rBoo[i] = true;
                }
                else {
                    rBoo[i] = false;
                }
            }
            else
                rBoo[i] = false;
        }
        return rBoo;
    }
    
    /**
     * search for vehicles that match the specified make
     * @param make of the vehicles to search for
     * @return array of boolean values indicating which spaces contain vehicles of the specified make.
     * 
     * A value of true at index n indicates that the n-th space contains a car of the specified make (match),
     * whereas a value of false at index n indicates that the n-th space contains a car of a different make (mismatch).
     */
}
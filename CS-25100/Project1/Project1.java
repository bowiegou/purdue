import java.awt.Point;
import java.util.ArrayList;
import java.util.Scanner;

public class Project1 {
	private int m;
	private int n;
	private static Scanner scan = new Scanner(System.in); //universal scanner
	private WeightedQuickUnionUF qu;
	private int[][] grid;
	private ArrayList<Point> connections;

	/**
	 * initializes UnionFind structure, grid and connection list
	 * @param m
	 * @param n
	 */
	public Project1(int m, int n){
		if(m > 0 && n > 0) {
			this.m = m;
			this.n = n;
			grid = new int[m][n];
			connections = new ArrayList<Point>();
			qu = new WeightedQuickUnionUF(m*n);
		} else {
			System.exit(1);
		}
	}

	/**
	 * Reads input from user (pair of connections presented as points), store the input in a list  
	 */
	public void read_input() {
		//Scanner scan = new Scanner(System.in);
		//System.out.print("Enter number of pairs of connections: ");
		int connect = scan.nextInt();
		int c_x;
		int c_y;
		int c_xx;
		int c_yy;
		connections.clear();
		for(int i = 0 ; i < connect; i++) {
			c_x = scan.nextInt();
			c_y = scan.nextInt();			
			c_xx = scan.nextInt();
			c_yy = scan.nextInt();
			Point p1 = new Point(c_x,c_y);
			Point p2 = new Point(c_xx,c_yy);
			if(is_adjacent(p1,p2) && c_x >= 0 && c_x <m && c_y >= 0 && c_y < n && c_xx >= 0 && c_xx <m && c_yy >= 0 && c_yy < n)
				connections.add(new Point(map(p1), map(p2)));
			//else 
			//	System.out.printf(" here     p1: %d, %d; p2: %d, %d\n", p1.x , p1.y, p2.x, p2.y);

		}
	}

	/**
	 * converts point into an integer
	 * @param p
	 * @return
	 */

	public int map(Point p) {
		//System.out.println((p.x ) * n + p.y);
		return (p.x ) * n + p.y ;
	}

	/***
	 * converts integer into a point
	 * @param i
	 * @return
	 */
	public  Point unmap(int i) {
		int x;
		int y;
		x = i / n ;
		y = i - (x)*n ;
		return new Point(x,y);
	}

	/***
	 * scans connections and populates UnionFind structure
	 */
	public void process_connections(){
		for(int i = 0; i < connections.size() ; i++) {
			qu.union(connections.get(i).x,connections.get(i).y);
		}

	}

	/**
	 * retrieve the connected sets from the UnionFind structure
	 * @return connected sets
	 */
	public ArrayList<Point> retrieve_connected_sets() {
		ArrayList<Point> ar = new ArrayList<Point>();
		//int[] parent = qu.getParent();
		int[] size = qu.getSize();
		int p;
		boolean exist = false;
		for(int i = 0; i < m*n; i++) {
			exist = false;
			p = qu.find(i);
			//System.out.println(p);
			if(size[p] > 1) {
				for(int t = 0; t < ar.size(); t++) {
					if(ar.get(t).x == p) {
						exist = true;
						break;
					}
				}
				if(!exist) {
					ar.add(new Point(p,size[p]));
				}
			}
		}
		//sort the arraylist so that the one with smaller number is at the front
		for(int i = 0; i <ar.size()-1; i++) {
			for(int k = i+1; k < ar.size(); k++) {
				if(ar.get(i).x > ar.get(k).x) {
					//swapping two entries
					Point pt = ar.get(i);
					ar.set(i, ar.get(k));
					ar.set(k, pt);
				}
			}
		}
		//System.out.printf("number of sets: %d\n", ar.size());
		for(int i = 0; i < ar.size(); i++) {
			Point pt = unmap(ar.get(i).x);
			System.out.printf("Set (%d,%d) with size %d\n", pt.x, pt.y, ar.get(i).y);
		}
		return ar;
	}

	/**
	 * Tests whether two Cells are connected in the grid
	 * @param p1
	 * @param p2
	 * @return
	 */
	public boolean is_adjacent(Point p1, Point p2) {
		if(p1.x + 1 != p2.x && p1.x - 1 != p2.x && p2.x != p1.x) {
			//System.out.printf(" xxx     p1: %d, %d; p2: %d, %d\n", p1.x , p1.y, p2.x, p2.y);
			return false;
		}
		if(p1.y + 1 != p2.y && p1.y - 1 != p2.y && p1.y != p2.y) {
			//System.out.printf(" yyy     p1: %d, %d; p2: %d, %d\n", p1.x , p1.y, p2.x, p2.y);
			return false;
		}
		return true;
	}

	/**
	 * outputs the boundaries and size of each connected set
	 * @param sets
	 */
	public void output_boundaries_size(ArrayList<Point> sets) {
		int bound_x_lower;
		int bound_x_upper;
		int bound_y_lower;
		int bound_y_upper;
		Point pt; //for storing the point that is currently processing
		int parent;
		for(int t = 0; t < sets.size(); t++) {
			parent = sets.get(t).x;
			pt = unmap(parent);
			bound_x_lower = pt.x;
			bound_x_upper = pt.x;
			bound_y_lower = pt.y;
			bound_y_upper = pt.y;
			for(int i = 0; i < m*n; i++) {
				if(qu.find(i) == parent) {
					pt = unmap(i);
					if(pt.x < bound_x_lower) bound_x_lower = pt.x;
					if(pt.x > bound_x_upper) bound_x_upper = pt.x;
					if(pt.y < bound_y_lower) bound_y_lower = pt.y;
					if(pt.y > bound_y_upper) bound_y_upper = pt.y;
				}
			}
			pt = unmap(parent);
			System.out.printf("Boundaries for (%d,%d) are %d<=x<=%d and %d<=y<=%d\n", pt.x, pt.y, bound_y_lower, bound_y_upper,bound_x_lower, bound_x_upper );
		}
	}

	public static void main(String args[]) {
		int m, n;
		//Scanner scan = new Scanner(System.in);
		//System.out.print("Enter size of grid(m n): ");
		m = scan.nextInt();
		n = scan.nextInt();
		//scan.nextLine();
		Project1 project1 = new Project1(m,n);
		project1.read_input();
		project1.process_connections();
		ArrayList<Point> sets = project1.retrieve_connected_sets();
		project1.output_boundaries_size(sets);
		scan.close();

	}
}
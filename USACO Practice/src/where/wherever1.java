/*
ID: andwerp1
LANG: JAVA
TASK: where
*/

package where;

import java.io.*;
import java.util.*;

public class wherever1 {
	public static void main (String [] args) throws IOException {
		
	//since the size of the grid is so small; <= 20, we can iterate through all the possible rectangles that are contained within the grid, ~40k.
	//from there, once we see that a rectangle is a possible cow image, we check if it is contained within, or contains another rectangle. 
	//if it contains one, then we remove that one, and if it is contained, then we don't add it to the list.
    
    BufferedReader fin = new BufferedReader(new FileReader("where.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("where.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    
    
    fin.close();
    fout.close();
    
	}
}
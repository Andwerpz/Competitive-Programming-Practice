/*
ID: andwerp1
LANG: JAVA
TASK: pails
*/

package pails;

import java.io.*;
import java.util.*;

class pailsver1 {
	public static void main (String [] args) throws IOException {
		
	//we can represent the possible moves as an 2d grid, which we can floodfill through. i think...
    
    BufferedReader fin = new BufferedReader(new FileReader("pails.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("pails.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    
    
    fin.close();
    fout.close();
    
	}
}
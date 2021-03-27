/*
ID: andwerp1
LANG: JAVA
TASK: example
*/

package example;

import java.io.*;
import java.util.*;

public class example {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("example.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("example.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    
    
    fin.close();
    fout.close();
    
	}
}
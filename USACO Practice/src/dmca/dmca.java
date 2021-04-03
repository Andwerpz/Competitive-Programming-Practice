
//package dmca;

import java.io.*;
import java.util.*;

public class dmca {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    System.out.println((int)Math.sqrt(n));
    
    
    fin.close();
    
	}
}
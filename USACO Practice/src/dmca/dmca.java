
//package dmca;

import java.io.*;
import java.util.*;

public class dmca {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    //StringTokenizer st = new StringTokenizer(fin.readLine());
    
    String n = fin.readLine();
    while(Integer.parseInt(n) >= 10) {
    	int temp = 0;
    	for(int i = 0; i < n.length(); i++) {
    		temp += Integer.parseInt(n.charAt(i) + "");
    	}
    	n = temp + "";
    }
    
    
    System.out.println(n);
    fin.close();
    
	}
}
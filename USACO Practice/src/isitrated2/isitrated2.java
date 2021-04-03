
//package isitrated2;

import java.io.*;
import java.util.*;

public class isitrated2 {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    
    boolean done = false;
    while(!done) {
    	String next = null;
    	try {
    		next = fin.readLine();
    	}
    	catch(IOException e) {
    		
    	}
    	if(next == null || next.equals("")) {
    		done = true;
    	}
    	else {
    		System.out.println("NO");
    	}
    }
    
    fin.close();
    
	}
}
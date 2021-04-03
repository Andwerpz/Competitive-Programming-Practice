
//package vladikandcourtesy;

import java.io.*;
import java.util.*;

public class vladikandcourtesy {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int a = Integer.parseInt(st.nextToken());
    int b = Integer.parseInt(st.nextToken());
    
    boolean done = false;
    int counter = 1;
    
    while(!done) {
    	if(counter % 2 != 0) {
	    	if(a - counter < 0) {
	    		System.out.println("Vladik");
	    		done = true;
	    	}
	    	else {
	    		a -= counter;
	    	}
    	}
    	else {
    		if(b - counter < 0) {
    			System.out.println("Valera");
    			done = true;
    		}
    		else {
    			b -= counter;
    		}
    	}
    	counter ++;
    }
    
    StringBuilder fout = new StringBuilder();
    
    System.out.print(fout);
    fin.close();
    
	}
}
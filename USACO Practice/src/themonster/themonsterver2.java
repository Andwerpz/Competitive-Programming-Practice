
package themonster;

import java.io.*;
import java.util.*;

public class themonsterver2 {
	public static void main (String [] args) throws IOException {
		
	//simulating the chase, if there is a gap that we have already seen before, then it's an infinite loop.
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int a = Integer.parseInt(st.nextToken());
    int b = Integer.parseInt(st.nextToken());
    
    st = new StringTokenizer(fin.readLine());
    int c = Integer.parseInt(st.nextToken());
    int d = Integer.parseInt(st.nextToken());
    
    HashSet<Integer> gaps = new HashSet<Integer>();
    gaps.add(b - d);
    
    boolean done = false;
    
    while(!done) {
    	System.out.println(b + " " + d);
    	if(b == d) {
    		done = true;
    		System.out.println(b);
    	}
    	else {
    		if(b < d) {
    			b += a;
    			if(gaps.contains(b - d)) {
    				System.out.println(-1);
    				done = true;
    			}
    			else {
    				gaps.add(b - d);
    			}
    		}
    		else {
    			d += c;
    			if(gaps.contains(b - d)) {
    				System.out.println(-1);
    				done = true;
    			}
    			else {
    				gaps.add(b - d);
    			}
    		}
    	}
    }
    
    
    fin.close();
    
	}
}
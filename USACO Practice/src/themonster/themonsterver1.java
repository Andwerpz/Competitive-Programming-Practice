
package themonster;

import java.io.*;
import java.util.*;

public class themonsterver1 {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int a = Integer.parseInt(st.nextToken());
    int b = Integer.parseInt(st.nextToken());
    
    st = new StringTokenizer(fin.readLine());
    int c = Integer.parseInt(st.nextToken());
    int d = Integer.parseInt(st.nextToken());
    
    if(a != b && c == d) {
    	System.out.println(-1);
    }
    
    else {
    	while(a != b) {
    		a += c;
    		if(a == b) {
    			System.out.println(a);
    			break;
    		}
    		while(b < a) {
    			b += d;
    		}
    		if(a == b) {
    			System.out.println(a);
    			break;
    		}
    	}
    }
    
    
    fin.close();
    
	}
}

//package buyashovel;

import java.io.*;
import java.util.*;

public class buyashovel {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int k = Integer.parseInt(st.nextToken());
    int r = Integer.parseInt(st.nextToken());
    int ans = 0;
    int counter = 1;
    while(true) {
    	if(k * counter % 10 == 0 || k * counter % 10 == r) {
    		ans = counter;
    		break;
    	}
    	counter++;
    }
    
    System.out.println(ans);
    fin.close();
    
	}
}

package vladikandflights;

import java.io.*;
import java.util.*;

public class vladikandflightsver1 {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int a = Integer.parseInt(st.nextToken()) - 1;
    int b = Integer.parseInt(st.nextToken()) - 1;
    
    int[] ports = new int[n];
    String input = fin.readLine();
    
    for(int i = 0; i < n; i++) {
    	ports[i] = Integer.parseInt(input.charAt(i) + "");
    }
    
    if(a == b) {
    	System.out.println(0);
    }
    
    else if(ports[a] == ports[b]) {
    	System.out.println(0);
    }
    
    else {
    	System.out.println(1);
    }
    
    
    
    fin.close();
    
	}
}
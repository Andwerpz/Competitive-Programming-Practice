
package buyashovel;

import java.io.*;
import java.util.*;

public class buyashovelver1 {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int k = Integer.parseInt(st.nextToken());
    int r = Integer.parseInt(st.nextToken());
    int ans = 10;
    for(int i = 10; i >= 1; i--) {
    	if(k * i % 10 == 0 || k * i % 10 == r) {
    		ans = i;
    	}
    }
    
    System.out.println(ans);
    fin.close();
    
	}
}
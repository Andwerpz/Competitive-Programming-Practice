
package notafraid;

import java.io.*;
import java.util.*;

public class notafraidver1 {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int m = Integer.parseInt(st.nextToken());
    boolean traitor = false;
    
    for(int i = 0; i < m; i++) {
    	HashSet<Integer> dict = new HashSet<Integer>();
    	st = new StringTokenizer(fin.readLine());
    	int k = Integer.parseInt(st.nextToken());
    	traitor = true;
    	for(int j = 0; j < k; j++) {
    		int input = Integer.parseInt(st.nextToken());
    		if(dict.contains(-input)) {
    			traitor = false;
    			break;
    		}
    		else {
    			dict.add(input);
    		}
    	}
    	if(traitor) {
    		break;
    	}
    }
    
    System.out.println(traitor? "YES" : "NO");
    fin.close();
    
	}
}

package shellgame;

import java.io.*;
import java.util.*;

public class shellgamever1 {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int x = Integer.parseInt(fin.readLine());
    int[] shells = new int[3];
    shells[x] = 1;
    
    n %= 6;
    
    for(int i = n; i > 0; i--) {
    	if(i % 2 == 0) {
    		int temp = shells[2];
    		shells[2] = shells[1];
    		shells[1] = temp;
    	}
    	if(i % 2 != 0) {
    		int temp = shells[0];
    		shells[0] = shells[1];
    		shells[1] = temp;
    	}
    }
    
    for(int i = 0; i < shells.length; i++) {
    	if(shells[i] == 1) {
    		System.out.println(i);
    	}
    }
    
    //StringBuilder fout = new StringBuilder();
    
    //System.out.print(fout);
    fin.close();
    
	}
}
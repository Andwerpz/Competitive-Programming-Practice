
//package polandballandgame;

import java.io.*;
import java.util.*;

public class polandballandgame {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int m = Integer.parseInt(st.nextToken());
    int both = 0;
    int p = n;
    int e = m;
    
    HashSet<String> pSet = new HashSet<String>();
    
    for(int i = 0; i < n; i++) {
    	pSet.add(fin.readLine());
    }
    for(int i = 0; i < m; i++) {
    	if(pSet.contains(fin.readLine())) {
    		p--;
    		e--;
    		both++;
    	}
    }
    
    boolean turn = false;
    
    while(true) {
    	//System.out.println(p + " " + e + " " + both);
    	if(!turn) {
    		turn = true;
    		if(both > 0) {
    			both--;
    		}
    		else {
    			p--;
    		}
    		if(p == -1) {
    			System.out.println("NO");
    			break;
    		}
    	}
    	else {
    		turn = false;
    		if(both > 0) {
    			both--;
    		}
    		else {
    			e--;
    		}
    		if(e == -1) {
    			System.out.println("YES");
    			break;
    		}
    	}
    }
    
    
    
    //StringBuilder fout = new StringBuilder();
    
    //System.out.print(fout);
    fin.close();
    
	}
}
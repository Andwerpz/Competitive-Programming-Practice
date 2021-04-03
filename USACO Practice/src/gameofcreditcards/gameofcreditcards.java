
//package gameofcreditcards;

import java.io.*;
import java.util.*;

public class gameofcreditcards {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int[] s = new int[n];
    int[] m = new int[n];
    
    String input = fin.readLine();
    for(int i = 0; i < n; i++) {
    	s[i] = Integer.parseInt(input.charAt(i) + "");
    }
    
    input = fin.readLine();
    for(int i = 0; i < n; i++) {
    	m[i] = Integer.parseInt(input.charAt(i) + "");
    }
    
    Arrays.sort(m);
    
    boolean[] visited = new boolean[n];
    
    int ans = 0;
    StringBuilder fout = new StringBuilder();
    
    for(int i = 0; i < n; i++) {	//minimizing flicks received
    	boolean success = false;
    	for(int j = 0; j < n; j++) {
    		if(m[j] >= s[i] && !visited[j]) {
    			success = true;
    			visited[j] = true;
    			break;
    		}
    	}
    	if(!success) {
    		ans++;
    		for(int j = 0; j < n; j++) {
    			if(!visited[j]) {
    				visited[j] = true;
    				break;
    			}
    		}
    	}
    }
    fout.append(ans).append("\n");
    
    ans = 0;
    visited = new boolean[n];
    
    for(int i = 0; i < n; i++) {	//maximizing flicks given
    	boolean success = false;
    	for(int j = 0; j < n; j++) {
    		if(m[j] > s[i] && !visited[j]) {
    			success = true;
    			visited[j] = true;
    			ans++;
    			break;
    		}
    	}
    	if(!success) {
    		for(int j = 0; j < n; j++) {
    			if(!visited[j]) {
    				visited[j] = true;
    				break;
    			}
    		}
    	}
    }
    fout.append(ans).append("\n");
    
    System.out.print(fout);
    fin.close();
    
	}
}
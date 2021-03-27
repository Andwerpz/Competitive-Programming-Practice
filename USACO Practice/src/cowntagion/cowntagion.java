/*
ID: andwerp1
LANG: JAVA
TASK: cowntagion
*/

//package cowntagion;

import java.io.*;
import java.util.*;

public class cowntagion {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    
    ArrayList<ArrayList<Integer>> connections = new ArrayList<ArrayList<Integer>>();
    
    for(int i = 0; i < n; i++) {
    	connections.add(new ArrayList<Integer>());
    }
    
    for(int i = 0; i < n - 1; i++) {
    	st = new StringTokenizer(fin.readLine());
    	int a = Integer.parseInt(st.nextToken()) - 1;
    	int b = Integer.parseInt(st.nextToken()) - 1;
    	connections.get(a).add(b);
    	connections.get(b).add(a);
    }
    
    Stack<Integer> toProcess = new Stack<Integer>();
    toProcess.add(0);
    
    HashSet<Integer> visited = new HashSet<Integer>();
    visited.add(0);
    
    int days = 0;
    
    while(toProcess.size() != 0) {
    	
    	int cur = toProcess.pop();
    	
    	//System.out.println("now processing node " + cur);
    	
    	ArrayList<Integer> curCon = connections.get(cur);
    	
    	if(cur == 0) {	//we have to do a special case for the first farm since all the connections need infected cows and we need to leave a cow behind
    		days += Math.ceil(Math.log10(curCon.size() + 1) / Math.log10(2));
    	}
    	else {
    		days += Math.ceil(Math.log10(curCon.size()) / Math.log10(2));
    	}
    	
    	
    	//System.out.println(Math.ceil(Math.log10(curCon.size()) / Math.log10(2)));
    	//System.out.println(Math.ceil(Math.log10(65536) / Math.log10(2)));
    	//the log base 2 of the number of connections is equal to the number of days required to multiply the cows necessary to give all the adjacent
    	//farms infected cows. We do a ceil since we can only measure time in whole days
    	
    	for(int i = 0; i < curCon.size(); i++) {
    		if(!visited.contains(curCon.get(i))) {
    			toProcess.add(curCon.get(i));
    			visited.add(curCon.get(i));
    			days ++;
    		}
    	}
    	
    }
    
    StringBuilder fout = new StringBuilder();
    fout.append(days).append("\n");
    System.out.print(fout);
    fin.close();
    
	}
}
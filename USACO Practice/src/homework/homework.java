/*
ID: andwerp1
LANG: JAVA
TASK: homework
*/

//package homework;

import java.io.*;
import java.util.*;

class homework {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("homework.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("homework.out")));
    
    
    int n = Integer.parseInt(fin.readLine());
    
    int[] scores = new int[n];
    int[] prefixSum = new int[n + 1];
    
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    for(int i = 0; i < n; i++) {
    	
    	scores[i] = Integer.parseInt(st.nextToken());
    	prefixSum[i + 1] = prefixSum[i] + scores[i];
    	
    	
    	
    }
    
    int[] prefixMin = new int[n];
    prefixMin[n - 1] = scores[n - 1];
    
    for(int i = n - 2; i >= 0; i--) {
    	if(prefixMin[i + 1] > scores[i]) {
    		prefixMin[i] = scores[i];
    	}
    	
    	else {
    		prefixMin[i] = prefixMin[i + 1];
    	}
    }
    
    for(int i = 0; i < n; i++) {
    	
    	//System.out.println(scores[i] + " " + prefixSum[i + 1] + " " + prefixMin[i]);
    	
    }
    
    double maxScore = 0;
    ArrayList<Integer> whichK = new ArrayList<Integer>();
    
    for(int i = 1; i < n - 1; i++) {
    	
    	int sum = (prefixSum[n] - prefixSum[i]) - prefixMin[i];
    	int numScores = n - i - 1;
    	
    	double avg = (double) sum / (double) numScores;
    	
    	if(avg > maxScore) {
    		
    		maxScore = avg;
    		whichK = new ArrayList<Integer>();
    		whichK.add(i);
    		
    	}
    	
    	else if(avg == maxScore) {
    		whichK.add(i);
    	}
    	
    	//System.out.println("K: " + i + " Sum: " + sum + " Avg: " + avg + " numscores: " + numScores + " min: " + prefixMin[i]);
    	
    	
    }
    
    for(int i = 0; i < whichK.size(); i++) {
    	fout.println(whichK.get(i));
    }
    
    
    fin.close();
    fout.close();
    
	}
}
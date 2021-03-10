/*
ID: andwerp1
LANG: JAVA
TASK: lifeguards
*/

package lifeguards;

import java.io.*;
import java.util.*;

class lifeguardsver1 {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("lifeguards.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("lifeguards.out")));
  
    
    int n = Integer.parseInt(fin.readLine());
    
    int[][] times = new int[n * 2][2];
    int[] timeAlone = new int[n];
    HashSet<Integer> active = new HashSet<Integer>();
    
    int totalTime = 0;
    
    for(int i = 0; i < n * 2; i += 2) {
    	
    	StringTokenizer st = new StringTokenizer(fin.readLine());
    	
    	times[i + 1][0] = Integer.parseInt(st.nextToken());
    	times[i + 1][1] = i / 2;
    	
    	times[i][0] = Integer.parseInt(st.nextToken());
    	times[i][1] = i / 2;
    	
    }
    
    
    Arrays.sort(times, (a, b) -> a[0] - b[0]);
    
    for(int[] i : times) {
    	System.out.println(i[0] + " " + i[1]);
    }
    
    for(int i = 0; i < times.length; i++) {
    	
    	if(i == 0) {
    		
    		int cowId = times[i][1];
    		active.add(cowId);
    		
    	}
    	
    	else {
    		
    		int timeElapsed = times[i][0] - times[i - 1][0];
    		int cowId = times[i][1];
    		
    		if(active.size() == 1) {
    			
    			int aloneCow = active.iterator().next();
    			timeAlone[aloneCow] += timeElapsed;
    			
    		}
    		
    		if(active.size() != 0) {
    			
    			totalTime += timeElapsed;
    			
    		}
    		
    		if(active.contains(cowId)) {
    			active.remove(cowId);
    		}
    		
    		else {
    			active.add(cowId);
    		}
    		
    	}
    	
    }
    
    
    Arrays.sort(timeAlone);
    
    fout.println(totalTime - timeAlone[0]);
    
    fin.close();
    fout.close();
    
	}
}
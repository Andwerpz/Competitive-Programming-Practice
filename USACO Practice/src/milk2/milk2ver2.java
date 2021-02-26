/*
ID: andwerp1
LANG: JAVA
TASK: milk2
*/

//ver2

package milk2;

import java.io.*;
import java.util.*;


public class milk2ver2 {
	public static void main (String [] args) throws IOException {
		
    BufferedReader fin = new BufferedReader(new FileReader("milk2.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("milk2.out")));
    int numFarmers = Integer.parseInt(fin.readLine());
    
    ArrayList<int[]> finalMilkingTimes = new ArrayList<int[]>();
    int[][] milkingTimes = new int[numFarmers * 2][2];
    
    for(int i = 0; i < numFarmers; i++) {
    	
    	StringTokenizer st = new StringTokenizer(fin.readLine());
    	
    	milkingTimes[i][0] = Integer.parseInt(st.nextToken());
    	milkingTimes[i + numFarmers][0] = Integer.parseInt(st.nextToken());
    	
    	milkingTimes[i][1] = 0;
    	milkingTimes[i + numFarmers][1] = 1;
    	
    }
    
    for(int i = 0; i < milkingTimes.length; i++) {
    	
    	int min = -1;
    	int minIndex = 0;
    	
    	for(int j = 0; j < milkingTimes.length; j++) {
    		
    		if((milkingTimes[j][0] < min || min == -1) && milkingTimes[j][0] != -1) {
    			min = milkingTimes[j][0];
    			minIndex = j;
    		}
    		
    	}
    	
    	milkingTimes[minIndex][0] = -1;
    	int[] temp = {min, milkingTimes[minIndex][1]};
    	finalMilkingTimes.add(temp);
    	System.out.println(temp[0] + " " + temp[1]);
    	
    }
    
    boolean isSimplified = false;
    
    
    while(!isSimplified) {
    	
    	isSimplified = true;
    	
    	for(int i = 0; i < finalMilkingTimes.size() - 1; i++) {
    		if(finalMilkingTimes.get(i)[0] != finalMilkingTimes.get(i + 1)[0] && finalMilkingTimes.get(i)[1] == finalMilkingTimes.get(i + 1)[1]) {
    			
    			if(finalMilkingTimes.get(i)[1] == 0) {
    				finalMilkingTimes.get(i + 1)[0] = finalMilkingTimes.get(i)[0];
    			}
    			
    			if(finalMilkingTimes.get(i)[1] == 1) {
    				finalMilkingTimes.get(i)[0] = finalMilkingTimes.get(i + 1)[0];
    			}
    			
    			isSimplified = false;
    			
    		}
    		
    	}
    	
    }
    
    for(int[] i : finalMilkingTimes) {
    	System.out.println(i[0] + " " + i[1]);
    }
    
    int longestMilk = 0;
    int longestIdle = 0;
    
    for(int i = 0; i < finalMilkingTimes.size() - 1; i++) {
    	
    	if(finalMilkingTimes.get(i)[1] != finalMilkingTimes.get(i + 1)[1]) {
    		
    		if(finalMilkingTimes.get(i)[1] == 0 && finalMilkingTimes.get(i + 1)[0] - finalMilkingTimes.get(i)[0] > longestMilk) {
    			longestMilk = finalMilkingTimes.get(i + 1)[0] - finalMilkingTimes.get(i)[0];
    		}
    		
    		if(finalMilkingTimes.get(i)[1] == 1 && finalMilkingTimes.get(i + 1)[0] - finalMilkingTimes.get(i)[0] > longestIdle) {
    			longestIdle = finalMilkingTimes.get(i + 1)[0] - finalMilkingTimes.get(i)[0];
    		}
    		
    	}
    	
    }
    
    fout.println(longestMilk + " " + longestIdle);
    
    fout.close();
    fin.close();
    
	}
}

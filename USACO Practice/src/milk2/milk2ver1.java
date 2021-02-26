/*
ID: andwerp1
LANG: JAVA
TASK: milk2
*/

package milk2;

import java.io.*;
import java.util.*;


public class milk2ver1 {
	public static void main (String [] args) throws IOException {
		
    BufferedReader fin = new BufferedReader(new FileReader("milk2.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("milk2.out")));
    int numFarmers = Integer.parseInt(fin.readLine());
    
    ArrayList<Integer> finalMilkingTimes = new ArrayList<Integer>();
    int[][] milkingTimes = new int[numFarmers][2];
    
    
    int latestMilkingTime = 0;
    int beginningMilkingTime = -1;
    
    for(int i = 0; i < numFarmers; i++) {
    	
    	StringTokenizer st = new StringTokenizer(fin.readLine());
    	
    	milkingTimes[i][0] = Integer.parseInt(st.nextToken());
    	milkingTimes[i][1] = Integer.parseInt(st.nextToken());
    	
    	if(milkingTimes[i][1] > latestMilkingTime) {
    		latestMilkingTime = milkingTimes[i][1];
    	}
    	if(milkingTimes[i][0] < beginningMilkingTime || beginningMilkingTime == -1) {
    		beginningMilkingTime = milkingTimes[i][0];
    	}
    	
    	System.out.println(milkingTimes[i][0] + " " + milkingTimes[i][1]);
    	
    }
    
    boolean isMilking = true;
    int counter = 0;
    System.out.println(beginningMilkingTime);
    
    for(int i = beginningMilkingTime -1; i < latestMilkingTime; i++) {
    	
    	boolean toggle = false;
    	
    	for(int j = 0; j < numFarmers; j++) {	
    		if(milkingTimes[j][0] <= i && milkingTimes[j][1] > i) {
    			toggle = true;
    		}
    	}
    	
    	if(toggle == isMilking) {
    		counter++;
    	}
    	
    	else {
    		
    		finalMilkingTimes.add(counter);
    		isMilking = toggle;
    		
    		counter = 1;
    		
    	}
    	
    	if(i == latestMilkingTime - 1) {
    		finalMilkingTimes.add(counter);
    	}
    	
    }
    
    finalMilkingTimes.set(1, finalMilkingTimes.get(1) - 1);
    
    for(int i : finalMilkingTimes) {
    	System.out.println(i);
    }
    
    int longestMilk = 0;
    int longestIdle = 0;
    
    for(int i = 0; i < finalMilkingTimes.size(); i++) {
    	if(finalMilkingTimes.get(i) > longestIdle && i % 2 == 1) {
    		longestIdle = finalMilkingTimes.get(i);
    	}
    	if(finalMilkingTimes.get(i) > longestMilk && i % 2 == 0) {
    		longestMilk = finalMilkingTimes.get(i);
    	}
    }
    
    fout.println(longestMilk + " " + longestIdle);
    
    fout.close();
    fin.close();
    
	}
}

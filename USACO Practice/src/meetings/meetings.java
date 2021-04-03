
//package meetings;

import java.io.*;
import java.util.*;

public class meetings {
	public static void main (String [] args) throws IOException {
		
	//first we must figure out how much time passes before half of the cows in weight are in barns. 
	//when we get the time, then we can compute how many meetings happen
    
    BufferedReader fin = new BufferedReader(new FileReader("meetings.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("meetings.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int l = Integer.parseInt(st.nextToken());
    
    int[][] cows = new int[n][3];
    ArrayList<int[]> pos = new ArrayList<int[]>();
    ArrayList<int[]> neg = new ArrayList<int[]>();
    //int[][] endTimes = new int[n][2];
    
    long totalWeight = 0;
    
    for(int i = 0; i < n; i++) {
    	st = new StringTokenizer(fin.readLine());
    	int w = Integer.parseInt(st.nextToken());
    	int x = Integer.parseInt(st.nextToken());
    	int d = Integer.parseInt(st.nextToken());
    	cows[i] = new int[] {x, w, d};
    	if(d == 1) {
    		pos.add(new int[] {x, w});
    	}
    	else {
    		neg.add(new int[] {x, w});
    	}
    	totalWeight += w;
    }
    
    pos.sort((a, b) -> (a[0] - b[0]) * -1);
    neg.sort((a, b) -> a[0] - b[0]);
    Arrays.sort(cows, (a, b) -> a[0] - b[0]);
    
    int low = 0;
    int high = n - 1;
    
    int pP = 0;
    int nP = 0;
    
    int sum = 0;
    
    for(int i = 0; i < n; i++) {
    	
    	if(pP < pos.size() && nP < neg.size()) {
	    	if(l - pos.get(pP)[0] < neg.get(nP)[0]) {
	    		sum += cows[high][1];
	    		high --;
	    		pP ++;
	    	}
	    	else if(l - pos.get(pP)[0] > neg.get(nP)[0]) {
	    		sum += cows[low][1];
	    		low ++;
	    		nP ++;
	    	}
	    	else {
	    		sum += cows[low][1] + cows[high][1];
	    		low ++;
	    		high --;
	    		nP ++;
	    		pP ++;
	    	}
    	}
    	else if(pP < pos.size()) {
    		sum += cows[high][1];
    		high --;
    		pP ++;
    	}
    	else if(nP < neg.size()) {
    		sum += cows[low][1];
    		low ++;
    		nP ++;
    	}
    	
    	
    	//System.out.println(sum);
    	if(sum >= totalWeight / 2) {
    		break;
    	}
    }
    
    nP --;
    pP --;
    int time = 0;
    if(nP >= 0 && pP >= 0) {
    	time = Math.max(neg.get(nP)[0], l - pos.get(pP)[0]);
    }
    else if(nP >= 0) {
    	time = neg.get(nP)[0];
    }
    else {
    	time = pos.get(pP)[0];
    }
    
    
    //System.out.println("time: " + time);
    long ans = 0;
    
    //we have to check the positives against the negatives, and vice versa. 
    //two positives won't collide
    
    for(int i = 0; i < pos.size(); i++) {
    	int x = pos.get(i)[0];
    	for(int j = 0; j < neg.size(); j++) {
    		if(neg.get(j)[0] >= x && neg.get(j)[0] <= x + time * 2) {
    			ans ++;
    		}
    	}
    }
    
    
    
    fout.println(ans);
    
    fin.close();
    fout.close();
    
	}
}
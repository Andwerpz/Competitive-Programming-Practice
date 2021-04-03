
package diamond;

import java.io.*;
import java.util.*;

public class diamondver2 {
	public static void main (String [] args) throws IOException {
    
    BufferedReader fin = new BufferedReader(new FileReader("diamond.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("diamond.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int k = Integer.parseInt(st.nextToken());
    int[] diamonds = new int[n];
    
    for(int i = 0; i < n; i++) {
    	diamonds[i] = Integer.parseInt(fin.readLine());
    }
    Arrays.sort(diamonds);
    
    int a = 0;
    int b = 0;
    
    int ansLow = 0;
    int ansHigh = 0;
    int max = 0;
    
    while(b != n - 1) {	//calculating first range
    	if(b - a + 1 > max) {
    		max = b - a + 1;
    		ansLow = a;
    		ansHigh = b;
    	}
    	if(b + 1 < n && diamonds[b + 1] - diamonds[a] <= k) {
    		b++;
    	}
    	else {
    		a++;
    	}
    }
    
    int max2 = 0;
    a = 0;
    b = 0;
    
    while(b != n - 1) {	//calculating second range
    	//System.out.println(a + " " + b);
    	if(b - a + 1 > max2 && !(a >= ansLow && a <= ansHigh) && !(b >= ansLow && b <= ansHigh)) {
    		max2 = b - a + 1;
    	}
    	if(b + 1 < n && diamonds[b + 1] - diamonds[a] <= k) {
    		b++;
    	}
    	else {
    		a++;
    	}
    }
    
    //System.out.println(ansLow + " " + ansHigh + " " + (max + max2));
    
    fout.println(max + max2);
    
    fin.close();
    fout.close();
    
	}
}
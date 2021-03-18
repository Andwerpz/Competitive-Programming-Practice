/*
ID: andwerp1
LANG: JAVA
TASK: studyingalgorithms
*/

package studyingalgorithms;

import java.io.*;
import java.util.*;

class studyingalgorithms {
	public static void main (String [] args) throws IOException {
    
    Scanner fin = new Scanner(System.in);
    StringTokenizer st = new StringTokenizer(fin.nextLine());
    
    int n = Integer.parseInt(st.nextToken());
    int x = Integer.parseInt(st.nextToken());
    
    int[] algorithms = new int[n];
    
    st = new StringTokenizer(fin.nextLine());
    
    for(int i = 0; i < n; i++) {
    	algorithms[i] = Integer.parseInt(st.nextToken());
    }
    
    Arrays.sort(algorithms);
    
    int counter = 0;
    
    for(int i = 0; i < n; i++) {
    	if(x - algorithms[i] >= 0) {
    		counter++;
    		x -= algorithms[i];
    	}
    	else {
    		break;
    	}
    }
    
    System.out.println(counter);
    
    fin.close();
    
	}
}
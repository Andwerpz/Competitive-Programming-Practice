/*
ID: andwerp1
LANG: JAVA
TASK: notimetopaint
*/

//package notimetopaint;

import java.io.*;
import java.util.*;

public class notimetopaint {
	public static void main (String [] args) throws IOException {
		
	//prefix sums and suffix sums
		
	//to exclude the interval, we can use prefix sums with suffix sums. 
	//we construct the prefix sums and suffix sums the same way. We scan through the input, maintaining a stack. every time we see a color higher than the current top of the stack, we push the new color onto it.
	//if we see a color that is lower than the current top of the stack, we have to pop colors off of the stack until we find the color, or we reach a color below that color. 
	//if we can't find the color, then we have to push it onto the stack. The total amount of pushes onto the stack represents the amount of strokes that we have to do to do.
		
	//now that we have our suffix and prefix sum arrays, we can take in the query, and get the prefix sum for the amount of strokes for the beginning of the range, and do the suffix for the end of the range.
	//add them up to get the answer.
    
    BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int q = Integer.parseInt(st.nextToken());
    
    int[] fence = new int[n];
    
    int[] pfx = new int[n + 1];
    int[] sfx = new int[n + 1];
    
    String input = fin.readLine();
    
    for(int i = 0; i < n; i++) {
    	
    	fence[i] = input.charAt(i);
    	
    }
    Stack<Integer> colors = new Stack<Integer>();
    for(int i = 0; i < n; i++) {
    	
    	
    	
    	if(i == 0) {
    		
    		colors.push(fence[i]);
    		pfx[i + 1] += 1;
    		
    		
    		
    	}
    	
    	//System.out.println(fence[i] > colors.peek());
    	
    	if(fence[i] > colors.peek()) {
    		
    		colors.push(fence[i]);
    		pfx[i + 1] += 1;
    		
    	}
    	
    	else if(fence[i] < colors.peek()) {
    		
    		while(colors.size() != 0 && colors.peek() != fence[i]) {
    			
    			colors.pop();
    			
    		}
    		
    		if(colors.size() == 0) {
    			
    			colors.push(fence[i]);
    			pfx[i + 1] += 1;
    			
    		}
    		
    	}
    	
    	pfx[i + 1] += pfx[i];
    	
    	//System.out.println(colors.peek());
    	
    }
    colors = new Stack<Integer>();
    for(int i = n - 1; i >= 0; i--) {
    	
    	
    	
    	if(i == n - 1) {
    		
    		colors.push(fence[i]);
    		sfx[i] += 1;
    		
    	}
    	
    	
    	if(fence[i] > colors.peek()) {
    		
    		colors.push(fence[i]);
    		sfx[i] += 1;
    		
    	}
    	
    	else if(fence[i] < colors.peek()) {
    		
    		while(colors.size() != 0 && colors.peek() != fence[i]) {
    			
    			colors.pop();
    			
    		}
    		
    		if(colors.size() == 0) {
    			
    			colors.push(fence[i]);
    			sfx[i] += 1;
    			
    		}
    		
    	}
    	
    	sfx[i] += sfx[i + 1];
    		
    }
    
    
    
    StringBuilder fout = new StringBuilder();
    
    for(int i = 0; i < q; i++) {
    	
    	st = new StringTokenizer(fin.readLine());
    	
    	int a = Integer.parseInt(st.nextToken()) - 1;
    	int b = Integer.parseInt(st.nextToken()) - 1;
    	
    	fout.append(pfx[a] + sfx[b]).append("\n");
    	
    }
    
    
    
    System.out.print(fout);
    fin.close();
    
	}
}
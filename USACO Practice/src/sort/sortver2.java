
package sort;

import java.io.*;
import java.util.*;

public class sortver2 {
	public static void main (String [] args) throws IOException {
		
	//the number of bubble sort passes it requires is equal to the distance a number is from it's correct location? maybe
    
    BufferedReader fin = new BufferedReader(new FileReader("sort.in"));
    PrintWriter fout = new PrintWriter(new BufferedWriter(new FileWriter("sort.out")));
    StringTokenizer st = new StringTokenizer(fin.readLine());
    
    int n = Integer.parseInt(st.nextToken());
    int[][] nums = new int[n][2];
    
    for(int i = 0; i < n; i++) {
    	nums[i][0] = Integer.parseInt(fin.readLine());
    	nums[i][1] = i;
    	System.out.println(nums[i][0] + " " + nums[i][1]);
    }
    
    
    boolean sorted = false;
    long ans = 0;
    
    while(!sorted) {
    	sorted = true;
    	ans++;
    	for(int i = 0; i < nums.length - 1; i++) {
    		if(nums[i + 1][0] < nums[i][0]) {
    			int temp = nums[i][0];
    			nums[i][0] = nums[i + 1][0];
    			nums[i + 1][0] = temp;
    			
    			temp = nums[i][1];
    			nums[i][1] = nums[i + 1][1];
    			nums[i + 1][1] = temp;
    			sorted = false;
    		}
    	}
    }
    
    System.out.println();
    for(int[] i : nums) {
    	System.out.println(i[0] + " " + i[1]);
    }
    
    System.out.println(ans);
    
    fin.close();
    fout.close();
    
	}
}
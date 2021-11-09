//package phoenixandbeauty;

import java.util.*;
import java.io.*;

public class phoenixandbeauty {
	public static void main(String[] args) throws IOException {
		
		//1348B
		
		//notice that in order to make any array have all subarrays of length k be equal, you need to make the entire array consist of identical arrays of length k. 
		
		//If there are more than k unique values in the array, then it is not possible to make the array beautiful. 
		
		//else, then what you can do is just include all the unique numbers at the beginning of the cycle, and put in "filler" numbers at the end. 
		//then repeat this cycle n times.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			HashSet<Integer> dict = new HashSet<Integer>();
			int[] nums = new int[n];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
				dict.add(nums[i]);
			}
			if(dict.size() > k) {
				fout.append("-1\n");
			}
			else {
				fout.append(n * k).append("\n");
				int pointer = 1;
				while(dict.size() != k) {
					dict.add(pointer);
					pointer ++;
				}
				for(int i = 0; i < n; i++) {
					for(int j : dict) {
						fout.append(j).append(" ");
					}
				}
				fout.append("\n");
			}
		}
		System.out.print(fout);
	}
}	

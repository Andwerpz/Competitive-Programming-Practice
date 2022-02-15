//package reverse;

import java.util.*;
import java.io.*;

public class reverse {
	public static void main(String[] args) throws IOException {
		
		//1638A
		
		//since you want to get the minimum lexographic value, use a greedy approach to minimize the array
		//focus on minimizing the first value, and if the first is already at a minimum, move to the next value
		
		//since you're trying to move the minimum value to a specific spot, there is only 1 way to reverse the array to get 
		//lexographic minimum: l is at the value you want to minimize, and r is at the minimum number
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] nums = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			int l = 0;
			int r = 0;
			int target = 0;
			for(int i = 0; i < n; i++) {
				if(nums[i] != i + 1) {
					l = i;
					r = i;
					target = i + 1;
					break;
				}
			}
			if(target != 0) {
				while(nums[r] != target) {
					r ++;
				}
			}
			for(int i = 0; i < l; i++) {
				fout.append(nums[i]).append(" ");
			}
			for(int i = r; i >= l; i--) {
				fout.append(nums[i]).append(" ");
			}
			for(int i = r + 1; i < n; i++) {
				fout.append(nums[i]).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}

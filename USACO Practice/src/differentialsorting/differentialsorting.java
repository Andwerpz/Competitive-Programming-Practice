//package differentialsorting;

import java.util.*;
import java.io.*;

public class differentialsorting {
	public static void main(String[] args) throws IOException {
		
		//1635C
		
		//notice that using the operation, you can't use lower index numbers to affect higher
		//indexed numbers. 
		
		//notice that you can't change the numbers at index n, and n - 1. So in order to be valid,
		//these numbers have to be sorted.
		
		//if a[n] >= 0, then it is guaranteed that you'll be able to sort the array. Just make every number equal to 
		//a[n - 1] - a[n]. 
		
		//if a[n] < 0, then the array must already be sorted for the input to be valid. This is true since 
		//a[n - 1] < a[n - 1] - a[n].
		
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
			if(nums[n - 1] < nums[n - 2]) {
				fout.append("-1\n");
				continue;
			}
			if(nums[n - 1] >= 0) {
				fout.append(n - 2).append("\n");
				for(int i = 0; i < n - 2; i++) {
					fout.append(i + 1).append(" ").append(n - 1).append(" ").append(n).append("\n");
				}
				continue;
			}
			else {
				boolean sorted = true;
				for(int i = 1; i < n; i++) {
					if(nums[i - 1] > nums[i]) {
						sorted = false;
						break;
					}
				}
				fout.append(sorted? "0\n" : "-1\n");
			}
		}
		System.out.print(fout);
	}
}

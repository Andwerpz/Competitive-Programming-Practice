//package permutationsort;

import java.util.*;
import java.io.*;

public class permutationsort {
	public static void main(String[] args) throws IOException {
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
			boolean sorted = true;
			for(int i = 0; i < n; i++) {
				if(nums[i] != i + 1) {
					sorted = false;
					break;
				}
			}
			if(sorted) {
				fout.append("0\n");
			}
			else if(nums[0] == 1 || nums[n - 1] == n) {
				fout.append("1\n");
			}
			else if(nums[0] == n && nums[n - 1] == 1) {
				fout.append("3\n");
			}
			else {
				fout.append("2\n");
			}
		}
		System.out.print(fout);
	}
}	

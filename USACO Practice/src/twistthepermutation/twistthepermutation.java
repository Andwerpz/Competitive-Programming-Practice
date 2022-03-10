//package twistthepermutation;

import java.util.*;
import java.io.*;

public class twistthepermutation {
	public static void main(String[] args) throws IOException {
		
		//1650D
		
		//since the inputs are so small, you can just simulate this in O(n^2) time. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] nums = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken()) - 1;
			}
			int[] ans = new int[n];
			for(int i = n - 1; i >= 0; i--) {
				int next = i;
				int dist = 0;
				for(int j = 0; j < n; j++) {
					if(next == nums[j]) {
						dist = (j - i + (i + 1)) % (i + 1);
						//System.out.println(dist + " " + j + " " + nums[i]);
						break;
					}
				}
				int[] temp = new int[n];
				for(int j = 0; j < n; j++) {
					temp[j] = nums[j];
				}
				for(int j = 0; j <= i; j++) {
					int newIndex = j - dist;
					newIndex = (newIndex + i + 1) % (i + 1);
					nums[newIndex] = temp[j];
				}
				ans[i] = dist;
			}
			for(int i : ans) {
				fout.append(i).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}
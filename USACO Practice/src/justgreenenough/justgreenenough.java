//package justgreenenough;

import java.util.*;
import java.io.*;

public class justgreenenough {
	
	static long numSubarrays(boolean[][] nums) {
		long ans = 0;
		for(int i = 0; i < nums.length; i++) {
			boolean[] top = new boolean[nums.length];
			for(int j = 0; j < nums[i].length; j++) {
				top[j] = nums[i][j];
			}
			for(int j = i; j < nums.length; j++) {
				for(int k = 0; k < nums[i].length; k++) {
					if(!(top[k] && nums[j][k])) {
						top[k] = false;
					}
				}
				int counter = 0;
				for(int k = 0; k < nums[i].length; k++) {
					if(top[k]) {
						counter++;
					}
					else {
						counter = 0;
					}
					ans += counter;
				}
			}
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		boolean[][] hundo = new boolean[n][n];
		boolean[][] hundo1 = new boolean[n][n];
		
		for(int i = 0; i < n; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int j = 0; j < n; j++) {
				int next = Integer.parseInt(st.nextToken());
				if(next >= 100) {
					hundo[i][j] = true;
				}
				if(next >= 101) {
					hundo1[i][j] = true;
				}
			}
		}
		
		System.out.println(numSubarrays(hundo) - numSubarrays(hundo1));
	}
}

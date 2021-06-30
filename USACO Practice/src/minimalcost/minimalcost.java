//package minimalcost;

import java.util.*;
import java.io.*;

public class minimalcost {
	public static void main(String[] args) throws IOException {
		
		//1491B
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int u = Integer.parseInt(st.nextToken());
			int v = Integer.parseInt(st.nextToken());
			st = new StringTokenizer(fin.readLine());
			boolean allOne = true;
			boolean trapped = true;
			boolean oneWall = true;
			int prev = 0;
			int ans = 0;
			int[] nums = new int[n];
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken());
				nums[i] = next;
				if(i == 0) {
					prev = next;
				}
				else {
					if(Math.abs(prev - next) > 1) {
						trapped = false;
						break;
					}
					else {
						if(prev - next != 0) {
							allOne = false;
						}
						if(next == 0) {
							oneWall = false;
							break;
						}
					}
					prev = next;
				}
			}
			if(trapped) {
				if(allOne) {
					ans += Math.min(v * 2, v + u);
				}
				else {
					ans += Math.min(u, v);
				}
			}
			if(!oneWall) {
				trapped = true;
				prev = 0;
				for(int i = n - 1; i >= 0; i--) {
					if(i == n - 1) {
						prev = nums[n - 1];
					}
					else {
						if(Math.abs(prev - nums[i]) > 1) {
							trapped = false;
							break;
						}
						else {
							if(nums[i] == 1000001) {
								break;
							}
							prev = nums[i];
						}
					}
					if(trapped) {
						ans += Math.min(u, v);
					}
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}

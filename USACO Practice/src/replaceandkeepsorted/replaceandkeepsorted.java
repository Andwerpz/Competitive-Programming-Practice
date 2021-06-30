//package replaceandkeepsorted;

import java.util.*;
import java.io.*;

public class replaceandkeepsorted {
	public static void main(String[] args) throws IOException {
		
		//1485B
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int q = Integer.parseInt(st.nextToken());
		int k = Integer.parseInt(st.nextToken());
		int[] pfx = new int[n];
		int[] nums = new int[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		for(int i = 1; i < n - 1; i++) {
			pfx[i] = nums[i + 1] - nums[i - 1] - 2;//System.out.print(pfx[i] + " ");
			pfx[i] += pfx[i - 1];
			
		}
		//System.out.println();
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < q; i++) {
			st = new StringTokenizer(fin.readLine());
			int l = Integer.parseInt(st.nextToken()) - 1;
			int r = Integer.parseInt(st.nextToken()) - 1;
			if(l == r) {
				fout.append(k - 1).append("\n");
			}
			else {
				int ans = (nums[l + 1] - 2) + (k - nums[r - 1] - 1) + (pfx[r - 1] - pfx[l]);
				fout.append(ans).append("\n");
			}
		}
		System.out.print(fout);
	}
}	

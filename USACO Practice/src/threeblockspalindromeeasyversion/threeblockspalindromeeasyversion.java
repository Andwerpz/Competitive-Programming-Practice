//package threeblockspalindromeeasyversion;

import java.util.*;
import java.io.*;

public class threeblockspalindromeeasyversion {
	public static void main(String[] args) throws IOException {
		
		//1335E1
		
		//use prefix sums. partition the numbers into ranges, and you can make a pfx for each number since there are only 26.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] nums = new int[n];
			int[] numNums = new int[26];
			int[][] pfx = new int[26][n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken()) - 1;
				numNums[nums[i]] ++;
				pfx[nums[i]][i] ++;
				if(i != 0) {
					for(int j = 0; j < 26; j++) {
						pfx[j][i] += pfx[j][i - 1];
					}
				}
			}
//			for(int[] i : pfx) {
//				for(int j : i) {
//					System.out.print(j + " ");
//				}
//				System.out.println();
//			}
//			for(int i : numNums) {
//				System.out.print(i + " ");
//			}
			//System.out.println();
			int ans = 0;
			for(int i = 0; i < 26; i++) {
				int cur = 0;
				int low = 0;
				int high = n - 1;
				for(int j = 1; j <= numNums[i] / 2; j++) {
					cur += 2;
					while(pfx[i][low] != j) {
						low ++;
					}
					if(j != 1) {
						high --;
					}
					while(nums[high] != i) {
						high --;
					}
					int max = 0;
					for(int k = 0; k < 26; k++) {
						max = Math.max(max, pfx[k][high - 1] - pfx[k][low]);
					}
					//System.out.println(max + " " + low + " " + high);
					ans = Math.max(max + cur, ans);
				}
			}
			for(int i = 0; i < 26; i++) {
				ans = Math.max(ans, numNums[i]);
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}

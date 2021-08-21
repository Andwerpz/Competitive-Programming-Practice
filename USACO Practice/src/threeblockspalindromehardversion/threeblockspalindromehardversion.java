//package threeblockspalindromehardversion;

import java.util.*;
import java.io.*;

public class threeblockspalindromehardversion {
	public static void main(String[] args) throws IOException {
		
		//1335E2
		
		//the observation is that you always want to use the outer 'braces' of each number to make the combinations. It is wasteful to not use them, since by using them, 
		//you are giving yourself more potential material to work with.
		
		//construct a bunch of pfx sums.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[][] pfx = new int[200][n];
			int[] nums = new int[n];
			for(int i = 0; i < n; i++) {
				int next = Integer.parseInt(st.nextToken()) - 1;
				nums[i] = next;
				pfx[next][i] ++;
			}
			int ans = 0;
			for(int i = 0; i < pfx.length; i++) {
				for(int j = 1; j < pfx[i].length; j++) {
					pfx[i][j] += pfx[i][j - 1];
				}
				ans = Math.max(ans, pfx[i][n - 1]);
			}
			for(int i = 0; i < pfx.length; i++) {
				int left = -1;
				int right = n;
				int counter = 0;
				while(true) {
					left ++;
					right --;
					counter ++;
					while(left < n && nums[left] != i) {
						left ++;
					}
					while(right > -1 && nums[right] != i) {
						right --;
					}
					if(left >= right) {
						break;
					}
					else {
						int max = 0;
						for(int j = 0; j < pfx.length; j++) {
							max = Math.max(max, pfx[j][right - 1] - pfx[j][left]);
						}
						ans = Math.max(ans, counter * 2 + max);
					}
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}

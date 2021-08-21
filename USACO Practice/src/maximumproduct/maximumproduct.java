///package maximumproduct;

import java.util.*;
import java.io.*;

public class maximumproduct {
	public static void main(String[] args) throws IOException {
		
		//1406B
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			Integer[] nums = new Integer[n];
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			long ans = -Long.MAX_VALUE;
			Arrays.sort(nums);
			Stack<Integer> mult = new Stack<Integer>();
			for(int i = 0; i < 3; i++) {
				long posSum = 1;
				long negSum = 1;
				for(int j = 0; j < i * 2; j++) {
					negSum *= nums[j];
				}
				for(int j = n - 1; j >= n - (5 - (i * 2)); j--) {
					posSum *= nums[j];
				}
				ans = Math.max(ans, posSum * negSum);
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}

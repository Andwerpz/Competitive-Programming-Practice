//package thedeliverydilemma;

import java.util.*;
import java.io.*;

public class thedeliverydilemma {
	public static void main(String[] args) throws IOException {
		
		//1443C
		
		//the solution is to greedily cancel the delivery that takes the longest. Since you are trying to minimize the maximum time, it doesn't help if you cancel a delivery that isn't the longest, 
		//since that won't affect the maximum time taken. Once the sum of Petya's times exceeds the next delivery time, you should stop.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[][] nums = new int[n][2];
			for(int i = 0; i < n; i++) {
				nums[i][0] = Integer.parseInt(st.nextToken());
			}
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i][1] = Integer.parseInt(st.nextToken());
			}
			Arrays.sort(nums, (a, b) -> -Comparator.compareInt(a, b));
//			for(int[] i : nums) {
//				System.out.println(i[0] + " " + i[1]);
//			}
			long ans = nums[0][0];
			long sum = 0;
			boolean gotAll = true;
			for(int i = 0; i < n - 1; i++) {
				sum += nums[i][1];
				if(sum > nums[i + 1][0]) {
					gotAll = false;
					break;
				}
				ans = nums[i + 1][0];
			}
			if(gotAll) {
				sum += nums[n - 1][1];
			}
			ans = Math.min(ans, sum);
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
	
	static class Comparator {
	
		public static int compareInt(int[] a, int[] b) {
			int result = Integer.compare(a[0], b[0]);
			if(result != 0) {
				return result;
			}
			return Integer.compare(a[1], b[1]);
		}
		
	}
}



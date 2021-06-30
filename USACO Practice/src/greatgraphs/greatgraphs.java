//package greatgraphs;

import java.util.*;
import java.io.*;

public class greatgraphs {
	public static void main(String[] args) throws IOException {
		
		//1541C
		
		//connect the other nodes to 1 in ascending total cost.
		
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
			Arrays.sort(nums);
			long ans = 0;
			long diffSum = 0;
			for(int i = 1; i < n; i++) {
				long prev = nums[i - 1];
				long cur = nums[i];
				diffSum += (cur - prev) * i;
				ans += (cur - prev) - diffSum;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}

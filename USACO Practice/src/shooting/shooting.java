//package shooting;

import java.util.*;
import java.io.*;

public class shooting {
	public static void main(String[] args) throws IOException {
		
		//1216B
		
		//it is optimal to shoot the highest resistance targets first
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		long ans = 0;
		int[][] nums = new int[n][2];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i][0] = Integer.parseInt(st.nextToken());
			nums[i][1] = i + 1;
		}
		Arrays.sort(nums, (a, b) -> Integer.compare(a[0], b[0]));
		StringBuilder fout = new StringBuilder();
		int c = 0;
		for(int i = n - 1; i >= 0; i--) {
			ans += nums[i][0] * c + 1;
			c ++;
			fout.append(nums[i][1]).append(" ");
		}
		System.out.println(ans + "\n" + fout);
	}
}

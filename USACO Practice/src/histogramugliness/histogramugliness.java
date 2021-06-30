//package histogramugliness;

import java.util.*;
import java.io.*;

public class histogramugliness {
	public static void main(String[] args) throws IOException {
		
		//1534B
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] nums = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			long ans = nums[0] + nums[n - 1];
			for(int i = 1; i < n; i++) {
				ans += Math.abs(nums[i - 1] - nums[i]);
			}
			for(int i = 0; i < n; i++) {
				if(i == 0 && n > 1) {
					if(nums[0] > nums[1]) {
						int diff = nums[0] - nums[1];
						nums[0] = nums[1];
						ans -= (long) diff;
					}
				}
				else if(i == n - 1 && n > 1) {
					if(nums[n - 1] > nums[n - 2]) {
						int diff = nums[n - 1] - nums[n - 2];
						nums[n - 1] = nums[n - 2];
						ans -= (long) diff;
					}
				}
				else if(n > 1){
					int max = Math.max(nums[i - 1], nums[i + 1]);
					if(nums[i] > max) {
						int diff = nums[i] - max;
						nums[i] = max;
						ans -= (long) diff;
					}
				}
			}
			if(n == 1) {
				ans = nums[0];
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}

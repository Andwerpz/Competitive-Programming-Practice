//package makeitgood;

import java.util.*;
import java.io.*;

public class makeitgood {
	public static void main(String[] args) throws IOException {
		
		//1385C
		
		//notice that a good array b needs to first increase then decrease. With this information, you know that to get the shortest prefix, you need to find the longest good array b in the suffix.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[] nums = new int[n];
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			boolean increasing = true;
			int ans = 0;
			for(int i = n - 2; i >= 0; i--) {
				//System.out.print(nums[i] + " ");
				if(increasing) {
					if(nums[i] < nums[i + 1]) {
						increasing = false;
					}
				}
				else {
					if(nums[i] > nums[i + 1]) {
						ans = i + 1;
						break;
					}
				}
			}
			//System.out.println();
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}

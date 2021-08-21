//package meximization;

import java.util.*;
import java.io.*;

public class meximization {
	public static void main(String[] args) throws IOException {
		
		//1497A
		
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
			boolean[] v = new boolean[n];
			Arrays.sort(nums);
			int prev = -1;
			for(int i = 0; i < n; i++) {
				if(nums[i] > prev) {
					fout.append(nums[i]).append(" ");
					v[i] = true;
					prev = nums[i];
				}
			}
			for(int i = 0; i < n; i++) {
				if(!v[i]) {
					fout.append(nums[i]).append(" ");
				}
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}

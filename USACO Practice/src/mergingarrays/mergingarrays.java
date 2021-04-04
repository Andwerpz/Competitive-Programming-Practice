//package mergingarrays;

import java.util.*;
import java.io.*;/

public class mergingarrays {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		int[] nArr = new int[n];
		int[] mArr = new int[m];
		int[] nums = new int[n + m];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nArr[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < m; i++) {
			mArr[i] = Integer.parseInt(st.nextToken());
		}
		int a = 0;
		int b = 0;
		int counter = 0;
		StringBuilder fout = new StringBuilder();
		while(true) {
			if(a == n && b == m) {
				break;
			}
			else if(a == n) {
				nums[counter] = mArr[b];
				b++;
			}
			else if(b == m) {
				nums[counter] = nArr[a];
				a++;
			}
			else if(nArr[a] <= mArr[b]) {
				nums[counter] = nArr[a];
				a++;
			}
			else {
				nums[counter] = mArr[b];
				b++;
			}
			counter++;
		}
		//String output = "";
		for(int i = 0; i < nums.length; i++) {
			if(i == nums.length - 1) {
				fout.append(nums[i]);
			}
			else {
				fout.append(nums[i]).append(" ");
			}
		}
		System.out.println(fout);
	}
}

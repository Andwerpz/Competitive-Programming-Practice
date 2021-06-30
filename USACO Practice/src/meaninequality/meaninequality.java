//package meaninequality;

import java.util.*;
import java.io.*;

public class meaninequality {
	public static void main(String[] args) throws IOException {
		
		//1526A
		
		//brute force, i don't know how it works
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine()) * 2;
			int[] nums = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());	
			}
			int start = n;
			int pointer = n;
			while(pointer - n <= start) {
				if(nums[(pointer + 1) % n] + nums[(pointer - 1) % n] == nums[pointer % n] * 2) {
					start = pointer;
					int temp = nums[pointer % n];
					nums[pointer % n] = nums[(pointer + 1) % n];
					nums[(pointer + 1) % n] = temp;
				}
				pointer ++;
			}
			for(int i = 0; i < n; i++) {
				fout.append(nums[i]).append(" ");
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}

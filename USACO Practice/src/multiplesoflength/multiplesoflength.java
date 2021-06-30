//package multiplesoflength;

import java.util.*;
import java.io.*;

public class multiplesoflength {
	public static void main(String[] args) throws IOException {
		
		//1396A
		
		//the first operation should be performed on the segment 1 - (n - 1). Since you have to add multiples of n - 1, you can always make the numbers in the array into multiples of n. 
		//just add nums[i] * (n - 1). The second operation should be performed on the last number. Since the length of the segment is 1, we can just subtract the number from itself, getting 0. 
		//the third operation should be performed on the entire array. Since it is already guaranteed that all the numbers are multiples of n, we can just subtract them from themselves.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		long n = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		long[] nums = new long[(int) n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		if(n == 1) {
			fout.append("1 1\n");
			fout.append("0\n");
			fout.append("1 1\n");
			fout.append("0\n");
			fout.append("1 1\n");
			fout.append(nums[0] * -1).append("\n");
		}
		else {
			fout.append("1 ").append(n - 1).append("\n");
			for(int i = 0; i < n - 1; i++) {
				fout.append((n - 1) * nums[i]).append(" ");
			}
			fout.append("\n");
			fout.append(n + " " + n).append("\n");
			if(nums[(int) n - 1] > 0) {
				fout.append(- nums[(int) n - 1]).append("\n");
				nums[(int) n - 1] += (- nums[(int) n - 1]);
			}
			else if(nums[(int) n - 1] < 0) {
				fout.append(- nums[(int) n - 1]).append("\n");
				nums[(int) n - 1] += (- nums[(int) n - 1]);
			}
			else {
				fout.append(0).append("\n");
			}
			fout.append("1 " + n).append("\n");
			for(int i = 0; i < n - 1; i++) {
				fout.append(-(nums[i] * n)).append(" ");
			}
			fout.append(-(nums[(int) n - 1]));
			fout.append("\n");
		}
		System.out.print(fout);
	}
}

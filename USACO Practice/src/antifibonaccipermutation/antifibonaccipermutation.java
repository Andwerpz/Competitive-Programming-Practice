//package antifibonaccipermutation;

import java.util.*;
import java.io.*;

public class antifibonaccipermutation {
	public static void main(String[] args) throws IOException {
		
		//1644B
		
		//notice that if you sort the permutation in descending order, it isn't a fib permutation
		
		//also notice that if you reverse any two numbers within the descending order permutation, it is also not a 
		//fib permutation
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] nums = new int[n];
			for(int i = 0; i < n; i++) {
				nums[i] = n - i;
			}
			for(int i : nums) {
				fout.append(i).append(" ");
			}
			fout.append("\n");
			for(int i = 0; i < n - 1; i++) {
				//reverse
				int temp = nums[i];
				nums[i] = nums[i + 1];
				nums[i + 1] = temp;
				for(int j : nums) {
					fout.append(j).append(" ");
				}
				fout.append("\n");
				//switch back
				//reverse
				temp = nums[i];
				nums[i] = nums[i + 1];
				nums[i + 1] = temp;
			}
		}
		System.out.print(fout);
	}
}

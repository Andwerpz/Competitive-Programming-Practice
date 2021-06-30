//package nastiaandagoodarray;

import java.util.*;
import java.io.*;

public class nastiaandagoodarray {
	public static void main(String[] args) throws IOException {
		
		//1521B
		
		//we are given an array. We can perform up to n operations on it, each operation consisting of changing two numbers. The limitation being that the min of the two numbers must stay
		//the same after the operation.
		//we want to make it so that the gcd of any two adjacent numbers is no more than 1.
		//to do this, we can always do this in n - 1 moves. We use the fact that for any number above 1, gcd(x, x + 1) = 1. To do this, find the lowest number in the array. 
		//then proceed to do the operations on the rest of the numbers, from 1 - n, != pos of min number. If we always include the min number in the operation, we can always change
		//the other number to any number we would like, since no other number is smaller than the minimum number. Then we just proceed to make a v shaped array, with each number being either 1 less than or
		//greater than the following number.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[] nums = new int[n];
			int min = Integer.MAX_VALUE;
			int pos = 0;
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
				if(nums[i] < min) {
					pos = i;
					min = nums[i];
				}
			}
			fout.append(n - 1).append("\n");
			int counter = 1;
			for(int i = pos - 1; i >= 0; i--) {
				fout.append(pos + 1).append(" ").append(i + 1).append(" ").append(min).append(" ").append(min + counter).append("\n");
				counter ++;
			}
			counter = 1;
			for(int i = pos + 1; i < n; i++) {
				fout.append(pos + 1).append(" ").append(i + 1).append(" ").append(min).append(" ").append(min + counter).append("\n");
				counter ++;
			}
		}
		System.out.print(fout);
	}
}

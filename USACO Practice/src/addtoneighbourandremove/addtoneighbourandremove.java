//package addtoneighbourandremove;

import java.util.*;
import java.io.*;

public class addtoneighbourandremove {
	public static void main(String[] args) throws IOException {
		
		//1462D
		
		//notice that it is only consecutive numbers that add up to the final number, and the final number has to be equal to the sum of all elements in the array divided by
		//the amount of remaining numbers. Since n <= 3000, we can just try all amounts of remaining numbers, for which it can divide the sum of the array with no remainder.
		//to test, just walk along array, and add a running sum. If the sum is equal to the target value, set running sum to 0, but if it goes above target value, then this
		//amount of remaining numbers is invalid.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t -- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int sum = 0;
			int[] nums = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
				sum += nums[i];
			}
			int ans = 0;
			for(int i = n; i >= 1; i--) {
				if(sum % i == 0) {
					//System.out.println("TARGET: " + (sum / i));
					int target = sum / i;
					int curSum = 0;
					boolean isValid = true;
					for(int j = 0; j < n; j++) {
						curSum += nums[j];
						if(curSum == target) {
							curSum = 0;
						}
						else if(curSum > target) {
							isValid = false;
							break;
						}
					}
					if(isValid) {
						ans = n - i;
						break;
					}
				}
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}

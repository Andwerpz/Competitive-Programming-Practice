//package qualityvsquantity;

import java.util.*;
import java.io.*;

public class qualityvsquantity {
	public static void main(String[] args) throws IOException {
		
		//1646B
		
		//we have two constraints, the number of blue numbers must be greater than the number of red numbers,
		//and the sum of red numbers must be greater than the sum of blue numbers. 
		
		//from the second constraint, we can see that we want to minimize the individual values of blue numbers
		//and maximize individual values of red numbers. We also want to keep the difference between 
		//the count of red and blue numbers as small as possible: exactly 1. 
		
		//so the solution is to give red the largest number, and give blue the 2 smallest numbers. If the sum
		//of red is less than blue, then just give both colors another number; red the next largest, and blue the
		//next smallest.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			Integer[] nums = new Integer[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			Arrays.sort(nums, (a, b) -> Integer.compare(a, b));
			boolean isValid = false;
			int pr = n - 1;
			int pb = 1;
			long rSum = 0;
			long bSum = nums[0];
			while(true) {
				rSum += (long) nums[pr];
				bSum += (long) nums[pb];
				if(rSum > bSum) {
					isValid = true;
					break;
				}
				pr --;
				pb ++;
				if(pr <= pb) {
					break;
				}
			}
			fout.append(isValid? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}

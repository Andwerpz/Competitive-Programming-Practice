//package powersequence;

import java.util.*;
import java.io.*;

public class powersequence {
	public static void main(String[] args) throws IOException {
		
		//1397B
		
		//to solve, we can just try out all values of c starting from 1, until we start seeing the cost go back up. The important part to notice is that as the size of the array goes up, the maximum value of c 
		//that you have to try exponentially goes down. If the size is 1000, and c == 2, then the last number in the array must change to 2^1000, a huge number.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		Long[] nums = new Long[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Long.parseLong(st.nextToken());
		}
		Arrays.sort(nums);
		long min = Long.MAX_VALUE;
		long pointer = 1;
		long curPower = 1;
		outer:
		while(true) {
			long curAns = 0;
			for(int i = 0; i < n; i++) {
				curAns += Math.abs(curPower - nums[i]);
				curPower *= pointer;
				if(curPower < 0) {
					break outer;
				}
			}
			//System.out.println(curAns);
			if(curAns < min) {
				min = curAns;
				pointer ++;
				curPower = 1;
			}
			else {
				break;
			}
		}
		System.out.println(min);
	}
}

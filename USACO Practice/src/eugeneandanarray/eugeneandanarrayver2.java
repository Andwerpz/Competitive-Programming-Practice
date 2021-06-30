package eugeneandanarray;

import java.util.*;
import java.io.*;

public class eugeneandanarrayver2 {
	public static void main(String[] args) throws IOException {
		
		//1333C
		
				//first, given a good subarray, any subarray within that array is good. Given this, you can do a two pointer approach. For each i, find the maximum rightmost j that forms a good subarray
				//and iterate i through 0 - n.
				//use prefix sums
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		long[] nums = new long[n];
		long[] pfx = new long[n + 1];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
			pfx[i + 1] = nums[i] + pfx[i];
		}
		long ans = 0;
		int pointer = 0;
		HashSet<Long> dict = new HashSet<Long>();
		for(int i = 0; i < pfx.length; i++) {
			//System.out.println(pfx[i]);
			if(i != 0) {
				dict.remove(pfx[i - 1]);
			}
			while(pointer != pfx.length && !dict.contains(pfx[pointer])) {
				//System.out.println("ADD: " + pfx[pointer] + " AT: " + pointer);
				dict.add(pfx[pointer]);
				pointer ++;
			}
			ans += pointer - i - 1;
			//System.out.println("ANS: " + (pointer - i - 1));
		}
		System.out.println(ans);
	}
}

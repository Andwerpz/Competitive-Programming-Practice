//package coprimesegment;

import java.util.*;
import java.io.*;

public class coprimesegment {
	public static void main(String[] args) throws IOException {
		
		//finding the factors of each number
		//if the group of numbers are coprime, then the factor "1" will be part of every number, while any other factor will be not part of every number.
	
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		HashMap<Long, Integer> factors = new HashMap<Long, Integer>();
		long[] nums = new long[n];
		int low = 0;
		int min = Integer.MAX_VALUE;
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			//System.out.println(i);
			boolean isValid = true;
			nums[i] = Long.parseLong(st.nextToken());
			long next = nums[i];
			//System.out.println("num: " + next + " factors:");
			for(long j = 1; j <= next; j++) {
				if(next % j == 0) {
					//System.out.println(j);
					factors.put((long) j, factors.getOrDefault(j, 0) + 1);
					if(factors.get(j) == factors.get((long) 1) && j != 1) {
						//System.out.println("factor " + j + " is not valid");
						isValid = false;
					}
					while(next % j == 0 && j != 1) {
						next /= j;
					}
				}
			}
			//System.out.println(isValid? ("is valid: " + low + " " + i) : "");
			if(isValid) {
				while(true) {
					HashSet<Long> curFactors = new HashSet<Long>();
					long cur = nums[low];
					for(long j = 1; j < cur; j++) {
						if(cur % j == 0) {
							curFactors.add(j);
						}
						while(cur % j == 0 && j != 1) {
							cur /= j;
						}
					}
					boolean success = true;
					Set<Long> keys = factors.keySet();
					for(long k : keys) {
						if(!curFactors.contains(k) && factors.get(k) == i - low) {
							success = false;
							break;
						}
					}
					if(success) {
						low++;
					}
					else {
						break;
					}
				}
				if(min > i - low + 1) {
					min = i - low + 1;
				}
			}
		}
		System.out.println(min == Integer.MAX_VALUE? "-1" : (min));
	}
}

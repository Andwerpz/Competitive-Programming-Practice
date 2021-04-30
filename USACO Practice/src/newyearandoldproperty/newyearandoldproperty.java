//package newyearandoldproperty;

import java.util.*;
import java.io.*;

public class newyearandoldproperty {
	
	static ArrayList<Long> nums;
	
	public static long search(long l, long r) {	//high and low inclusive
		int low = 0;
		int high = nums.size();
		int mid = low + (high - low) / 2;
		int ansLow = -1;
		int ansHigh = -1;
		while(low <= high) {
			if(nums.get(mid) >= l) {
				if(ansLow == -1 || ansLow > mid) {
					ansLow = mid;
				}
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
			mid = low + (high - low) / 2;
		}
		low = 0;
		high = nums.size();
		mid = low + (high - low) / 2;
		while(low <= high) {
			if(nums.get(mid) <= r) {
				if(ansHigh == -1 || ansHigh < mid) {
					ansHigh = mid;
				}
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
			mid = low + (high - low) / 2;
		}
		if(ansHigh == -1 || ansLow == -1) {
			return 0;
		}
		return ansHigh - ansLow + 1;
	}
	
	public static void main(String[] args) throws IOException {
		
		//precalculate all possible answers, and just binary search for the range of answers
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		long base = 1;
		long add = 2;
		long pointer = 1;
		nums = new ArrayList<Long>();
		for(int i = 1; i < 60; i++) {	//log2(10^18)
			base += add;
			add *= 2;
			//System.out.println("BASE: " + base);
			for(int j = 0; j < i; j++) {
				//System.out.println("POINTER: " + pointer);
				nums.add(base - pointer);
				if(base - pointer == 7) {
					//System.out.println("ALERT ALERT");
				}
				pointer *= 2;
			}
			pointer = 1;
		}
		nums.sort((a, b) -> Long.compare(a, b));
		
		StringTokenizer st = new StringTokenizer(fin.readLine());
		long low = Long.parseLong(st.nextToken());
		long high = Long.parseLong(st.nextToken());
		System.out.println(search(low, high));
	}
}

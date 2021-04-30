package geometricprogression;

import java.util.*;
import java.io.*;

public class geometricprogressionver1 {
	
	static long[] nums;
	
	public static long search(long l, long r) {	//low and high inclusive
		long low = 0;
		long high = nums.length - 1;
		long mid = low + (high - low) / 2;
		long ansHigh = -1;
		long ansLow = -1;
		while(low <= high) {
			if(nums[(int)mid] <= r) {
				low = mid + 1;
				if(mid > ansHigh) {
					ansHigh = mid;
				}
			}
			else {
				high = mid - 1;
			}
			mid = low + (high - low) / 2;
		}
		low = 0;
		high = nums.length - 1;
		mid = low + (high - low) / 2;
		while(low <= high) {
			if(nums[(int)mid] >= l) {
				high = mid - 1;
				if(mid < ansLow || ansLow == -1) {
					ansLow = mid;
				}
			}
			else {
				low = mid + 1;
			}
			mid = low + (high - low) / 2;
		}
		//System.out.prlongln("bin search " + ansLow + " " + ansHigh + " " + l);
		if(ansHigh == -1 || ansLow == -1) {
			return 0;
		}
//		else if(ansLow == -1) {
//			return ansHigh + 1;
//		}
//		else if(ansHigh == -1) {
//			return nums.length - ansLow;
//		}
		return ansHigh - ansLow + 1;
	}
	
	public static void main(String[] args) throws IOException {
		
		//for every distinct number, how many ways can we make a geometric progression starting on that number
		
		//misinterpreted the question. We need to keep the original ordering of the array. We can keep bin search, just need to keep track of how many numbers we have already passed. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		long n = Integer.parseInt(st.nextToken());
		long k = Integer.parseInt(st.nextToken());
		nums = new long[(int)n];
		long[] unsorted = new long[(int) n];
		st = new StringTokenizer(fin.readLine());
		for(long i = 0; i < n; i++) {
			nums[(int)i] = Integer.parseInt(st.nextToken());
			unsorted[(int) i] = nums[(int)i];
		}
		HashMap<Long, Long> dict = new HashMap<Long, Long>();	//saves how many numbers of each value we passed. 
		Arrays.sort(nums);
		long prev = -1;
		long ans = 0;
		for(long i = 0; i < n; i++) {
			long next = nums[(int)i];
			if(prev != next) {
				//System.out.prlongln(next);
				long a = search(next, next);
				long b = search(next * k, next * k);
				long c = search(next * k * k, next * k * k);
				//System.out.prlongln(a + " " + b + " " + c);
				//System.out.prlongln(search(next, next));
				ans += a * b * c;
				prev = next;
			}
		}
		System.out.println(ans);
	}
}

//package banditinacity;

import java.util.*;
import java.io.*;

public class banditinacity {
	
	static int[] c;
	static HashSet<Integer> leaves;
	
	public static boolean isValid(long val, long[] people) {
		//System.out.println(val);
		for(int k : leaves) {
			long sum = 0;
			int index = k;
			while(true) {
				long diff = val - sum;
				diff = Math.min(diff, people[index]);
				sum += diff;
				people[index] -= diff;
				if(sum != val) {
					if(c[index] == -1) {
						break;
					}
					else {
						index = c[index];
					}
				}
				else {
					break;
				}
			}
		}
		for(long i : people) {
			if(i != 0) {
				//System.out.println(i);
				return false;
			}
		}
		return true;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1436D
		
		//too slow, need a faster answer.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		StringTokenizer st = new StringTokenizer(fin.readLine());
		c = new int[n];
		leaves = new HashSet<Integer>();
		HashSet<Integer> twoConnection = new HashSet<Integer>();
		Arrays.fill(c, -1);
		for(int i = 0; i < n; i++) {
			leaves.add(i);
		}
		for(int i = 1; i < n; i++) {
			c[i] = Integer.parseInt(st.nextToken()) - 1;
			if(leaves.contains(c[i])) {
				leaves.remove(c[i]);
			}
			else {
				twoConnection.add(c[i]);
			}
		}
		long[] nums = new long[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		//System.out.println(twoConnection);
//		ArrayList<Integer> remove = new ArrayList<Integer>();
//		ArrayList<Integer> add = new ArrayList<Integer>();
//		for(int k : leaves) {
//			int index = k;
//			long sum = 0;
//			while(!twoConnection.contains(c[index]) && index != 0) {
//				//System.out.println(index);
//				sum += nums[index];
//				nums[index] = 0;
//				index = c[k];
//				if(index == 0) {
//					break;
//				}
//			}
//			nums[index] += sum;
//			if(k != index) {
//				remove.add(k);
//				add.add(index);
//			}
//		}
//		for(int i : remove) {
//			leaves.remove(i);
//		}
//		for(int i : add) {
//			leaves.add(i);
//		}
		//System.out.println(leaves);
		long high = (long) Math.pow(10, 14);
		long low = 0;
		long mid = low + (high - low) / 2;
		long ans = high;
		while(low <= high) {
			long[] people = Arrays.copyOf(nums, nums.length);
			if(isValid(mid, people)) {
				ans = Math.min(mid, ans);
				high = mid - 1;
			}
			else {
				low = mid + 1;
			}
			mid = low + (high - low) / 2;
		}
		System.out.println(ans);
	}
}

//package divideandsummarize;

import java.util.*;
import java.io.*;

public class divideandsummarize {
	
	static HashSet<Long> dict;
	static long[] nums;
	static long[] pfx;
	
	public static void getSet(int low, int high) {
		//System.out.println(low + " " + high);
		dict.add(pfx[high + 1] - pfx[low]);
		int midVal = (int) Math.floor((double) (nums[high] + nums[low]) / 2);
		int mid = search(low, high, midVal);
		if(mid == high) {	//they're all the same number
			return;
		}
		else if(low == high) {
			return;
		}
		//System.out.println(low + " " + mid + " " + high);
		getSet(low, mid);
		getSet(mid + 1, high);
	}
	
	public static int search(int low, int high, int val) {
		int mid = low + (high - low) / 2;
		int ans = low;
		while(low <= high) {
			if(nums[mid] <= val && mid <= high) {
				if(ans < mid) {
					ans = mid;
				}
				low = mid + 1;
			}
			else {
				high = mid - 1;
			}
			mid = low + (high - low) / 2;
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1461D
		
		//given an array, you can just precalculate all the possible sums that you can get and put them into a hashset. Queries become trivial, as you just have to check
		//whether it exists within the hashset. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t -- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int q = Integer.parseInt(st.nextToken());
			dict = new HashSet<Long>();
			nums = new long[n];
			pfx = new long[n + 1];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			Arrays.sort(nums);
			for(int i = 0; i < n; i++) {
				pfx[i + 1] = pfx[i] + nums[i];
			}
			getSet(0, n - 1);
			for(int i = 0; i < q; i++) {
				fout.append(dict.contains(Long.parseLong(fin.readLine()))? "YES\n" : "NO\n");
			}
			//System.out.println(dict);
		}
		System.out.print(fout);
	}
}

package kamazingnumbers;

import java.util.*;
import java.io.*;

public class kamazingnumbersver1 {
	
	public static int isValid(int[] nums, int val) {
		HashMap<Integer, Integer> dict = new HashMap<Integer, Integer>();
		for(int i = 0; i < val; i++) {
			int next = nums[i];
			dict.put(next, dict.getOrDefault(next, 0) + 1);
		}
		for(int i = val; i < nums.length; i++) {
			int next = nums[i];
			if(dict.containsKey(next)) {
				dict.put(next, dict.get(next) + 1);
			}
			int remove = nums[i - val];
			if(dict.containsKey(remove)) {
				dict.put(remove, dict.get(remove) - 1);
				if(dict.get(remove) == 0) {
					dict.remove(remove);
				}
			}
		}
		if(dict.size() != 0) {
			return dict.keySet().iterator().next();
		}
		return -1;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int[] nums = new int[n];
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			int high = n;
			int low = 1;
			int ans = n;
			int ansVal = -1;
			int mid = low + (high - low) / 2;
			while(low <= high) {
				int next = isValid(nums, mid);
				if(next != -1) {
					if(ans > mid) {
						ansVal = next;
					}
					ans = Math.min(mid, ans);
					high = mid - 1;
				}
				else {
					low = mid + 1;
				}
				mid = low + (high - low) / 2;
			}
			for(int i = 1; i <= n; i++) {
				if(i >= ans) {
					fout.append(ansVal).append(" ");
				}
				else {
					fout.append("-1 ");
				}
			}
			fout.append("\n");
		}
		System.out.print(fout);
	}
}

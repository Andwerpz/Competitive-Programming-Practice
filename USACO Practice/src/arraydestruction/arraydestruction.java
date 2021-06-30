//package arraydestruction;

import java.util.*;
import java.io.*;

public class arraydestruction {
	
	static int[] nums;
	static HashMap<Integer, Integer> dict;
	static int[][] ans;
	
	public static boolean isValid(int x) {
		int pointer = 0;
		ans = new int[nums.length / 2][2];
		for(int i = nums.length - 1; i >= 0; i--) {
			if(dict.containsKey(nums[i])) {
				if(pointer >= nums.length / 2) {
					return false;
				}
				int a = nums[i];
				int b = x - a;
				if(dict.containsKey(b)) {
					dict.put(a, dict.get(a) - 1);
					dict.put(b, dict.get(b) - 1);
					x = Math.max(a, b);
					if(dict.get(a) == 0) {
						dict.remove(a);
					}
					if(dict.getOrDefault(b, 0) == 0) {
						dict.remove(b);
					}
					ans[pointer][0] = a;
					ans[pointer][1] = b;
					//System.out.println(pointer);
					pointer ++;
					
				}
				else {
					return false;
				}
			}
			if(dict.size() == 0) {
				break;
			}
		}
		return true;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			nums = new int[n + n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < nums.length; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			Arrays.sort(nums);
			boolean isValid = false;
			for(int i = 0; i < nums.length - 1; i++) {
				dict = new HashMap<Integer, Integer>();
				for(int j : nums) {
					dict.put(j, dict.getOrDefault(j, 0) + 1);
				}
				int x = nums[nums.length - 1] + nums[i];
				if(isValid(x)) {
					isValid = true;
					fout.append("YES\n");
					fout.append(x).append("\n");
					for(int[] j : ans) {
						fout.append(j[0]).append(" ").append(j[1]).append("\n");
					}
					break;
				}
			}
			if(!isValid) {
				fout.append("NO\n");
			}
		}
		System.out.print(fout);
	}
}

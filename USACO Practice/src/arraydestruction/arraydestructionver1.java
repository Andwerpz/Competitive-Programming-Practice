//package arraydestruction;

import java.util.*;
import java.io.*;

public class arraydestructionver1 {
	
	static StringBuilder output;
	
	public static boolean isValid(int x, TreeMap<Integer, Integer> dict) {
//		System.out.println(x);
//		System.out.println(dict);
		while(dict.size() != 0) {
			int a = dict.lastKey();
			if(a >= x) {
				return false;
			}
			if(dict.containsKey(x - a)) {
				int b = x - a;
				//System.out.println(a + " " + b);
				dict.put(a, dict.get(a) - 1);
				dict.put(b, dict.get(b) - 1);
				if(dict.get(a) == 0) {
					dict.remove(a);
				}
				if(dict.getOrDefault(b, 0) == 0) {	//get or default because what if a == b, then b would already have been removed
					dict.remove(b);
				}
				x = Math.max(a, b);
			}
			else {
				return false;
			}
		}
		return true;
	}
	
	public static String getString(int x, TreeMap<Integer, Integer> dict) {
		output = new StringBuilder();
		output.append(x).append("\n");
//		System.out.println(x);
//		System.out.println(dict);
		while(dict.size() != 0) {
			int a = dict.lastKey();
			if(dict.containsKey(x - a)) {
				int b = x - a;
				//System.out.println(a + " " + b);
				output.append(a).append(" ").append(b).append("\n");
				dict.put(a, dict.get(a) - 1);
				dict.put(b, dict.get(b) - 1);
				if(dict.get(a) == 0) {
					dict.remove(a);
				}
				if(dict.getOrDefault(b, 0) == 0) {	//get or default because what if a == b, then b would already have been removed
					dict.remove(b);
				}
				x = Math.max(a, b);
			}
		}
		return output.toString();
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] nums = new int[n * 2];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < nums.length; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			TreeMap<Integer, Integer> dict = new TreeMap<Integer, Integer>();
			for(int j = 0; j < nums.length; j++) {
				dict.put(nums[j], dict.getOrDefault(nums[j], 0) + 1);
			}
			Arrays.sort(nums);
			boolean isValid = false;
			for(int i = 0; i < nums.length - 1; i++) {
				TreeMap<Integer, Integer> temp = new TreeMap<Integer, Integer>();
				for(int j : dict.keySet()) {
					temp.put(j, dict.get(j));
				}
				int x = nums[n * 2 - 1] + nums[i];
				if(isValid(x, temp)) {
					fout.append("YES\n");
					fout.append(getString(x, dict));
					isValid = true;
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

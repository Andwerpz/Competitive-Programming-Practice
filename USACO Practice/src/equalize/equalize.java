//package equalize;

import java.util.*;
import java.io.*;

public class equalize {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		char[] a = fin.readLine().toCharArray();
		char[] b = fin.readLine().toCharArray();
		ArrayList<int[]> nums = new ArrayList<int[]>();
		for(int i = 0; i < n; i++) {
			if(a[i] != b[i]) {
				nums.add(new int[] {i, Integer.parseInt(a[i] + "")});
			}
		}
		int ans = 0;
		for(int i = 0; i < nums.size(); i++) {
			//System.out.println(nums.get(i));
			if(i + 1 != nums.size() && nums.get(i + 1)[0] - nums.get(i)[0] == 1 && nums.get(i + 1)[1] != nums.get(i)[1]) {
				ans += 1;
				i ++;
			}
			else {
				ans += 1;
			}
		}
		System.out.println(ans);
	}
}

//package paintthemiddle;

import java.util.*;
import java.io.*;

public class paintthemiddle {
	public static void main(String[] args) throws IOException {
		
		//1631E
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] nums = new int[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(st.nextToken());
		}
		HashMap<Integer, Integer> dict = new HashMap<Integer, Integer>();
		for(int i = n - 1; i >= 0; i--) {
			if(!dict.keySet().contains(nums[i])) {
				dict.put(nums[i], i);
			}
		}
		int ans = 0;
		int l = -1;
		int r = -1;
		for(int i = 0; i < n; i++) {
			if(l==-1) {
				l = i;
				r = dict.get(nums[i]);
				continue;
			}
			if(i==r) {
				// go kill things ahhhh
				l = -1;
				r = -1;
			}
			else {
				if(dict.get(nums[i]) > r) {
					l = i;
					r = dict.get(nums[i]);
				}
				else {
					ans++;
					//System.out.println(i);
				}
			}
		}
		System.out.println(ans);
	}
}

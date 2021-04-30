//package oracandmodels;

import java.util.*;
import java.io.*;

public class oracandmodels {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			HashSet<Integer> v = new HashSet<Integer>();
			int n = Integer.parseInt(fin.readLine());
			int[] nums = new int[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			//System.out.println();
			for(int i = 0; i < n; i++) {
				int index = i;
				int cur = nums[i];
				while(index < n) {
					//System.out.println("loop");
					if(nums[index] > cur && !v.contains(index)) {
						v.add(index);
						//System.out.println(index);
					}
					index += i + 1;
				}
			}
			int ans = 1;
			if(v.size() != 0) {
				ans ++;
			}
			while(true) {
				//System.out.println("loop");
				HashSet<Integer> nextSet = new HashSet<Integer>();
				for(int i : v) {
					int index = i;
					int cur = nums[i];
					while(index < n) {
						if(nums[index] > cur && !nextSet.contains(index)) {
							nextSet.add(index);
						}
						index += i + 1;
					}
				}
				if(nextSet.size() == 0) {
					break;
				}
				ans ++;
				v = nextSet;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}

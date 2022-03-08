//package integralarray;

import java.util.*;
import java.io.*;

public class integralarray {
	public static void main(String[] args) throws IOException {
		
		//1649D
		
		//tutorial solution: (very clever)
		
		//for a number y, we can check whether there is a number r, that exists where floor(x / y) == r. 
		//if r exists for any y, then the array is invalid. 
		
		//for each y, we can test r from 1 to y / c; y / c since if r > y / c, then r * y > c, and x <= c. 
		//correction: y / c is a simplification, we need to test r until y * r > c. Also, when testing, don't test
		//when r exists within a.
		
		//to test, just check whether there exists x where y * r <= x < y * (r + 1). You can check whether x 
		//exists in the range in O(1) with a prefix sum arr. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int n = Integer.parseInt(st.nextToken());
			int c = Integer.parseInt(st.nextToken());
			Integer[] nums = new Integer[n];
			st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				nums[i] = Integer.parseInt(st.nextToken());
			}
			Arrays.sort(nums);
			int[] cnt = new int[c + 1];
			for(int i : nums) {
				cnt[i] ++;
			}
			for(int i = 1; i <= c; i++) {
				cnt[i] += cnt[i - 1];
			}
			HashSet<Integer> checked = new HashSet<Integer>();
			checked.add(1);
			boolean isValid = true;
			outer:
			for(int i = 0; i < n; i++) {
				if(checked.contains(nums[i])) {
					continue;
				}
				//System.out.println(nums[i] + "-------------");
				for(int j = 1; j <= c; j++) {
					//System.out.println(j);
					if(nums[i] * j > c) {	//no x greater than c
						break;
					}
					if(cnt[j] - cnt[j - 1] >= 1) {	//given r exists within a
						continue;
					}
					if(cnt[Math.min(nums[i] * (j + 1) - 1, c)] - cnt[nums[i] * j - 1] >= 1) {	//x / y == r, and r is not in a
						isValid = false;
						break outer;
					}
				}
				checked.add(nums[i]);
			}
			fout.append(isValid? "Yes\n" : "No\n");
		}
		System.out.print(fout);
	}
}

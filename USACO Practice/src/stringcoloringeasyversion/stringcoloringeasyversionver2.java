package stringcoloringeasyversion;

import java.util.*;
import java.io.*;

public class stringcoloringeasyversionver2 {
	public static void main(String[] args) throws IOException {
		
		//we just need to find out if the numbers can be split into two increasing subsequences. doing dp and finding the largest increasing subsequence won't help since you might miss 
		//some numbers, and not get the entire subsequence. The much easier approach is to do it greedily. Since it can be split into two increasing subsequences, you should
		//be able to just run over it two times, and just take increasing or equal numbers. If there are numbers left over, then this subsequence can't be painted
		//with only two colors.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		char[] s = fin.readLine().toCharArray();
		int[] nums = new int[n];
		for(int i = 0; i < n; i++) {
			nums[i] = s[i];
		}
		int s1 = 0;
		int s2 = 0;
		boolean isValid = true;
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < n; i++) {
			if(s1 <= nums[i]) {
				s1 = nums[i];
				fout.append(0);
			}
			else if(s2 <= nums[i]) {
				s2 = nums[i];
				fout.append(1);
			}
			else {
				isValid = false;
				break;
			}
		}
		if(isValid) {
			System.out.println("YES\n" + fout);
		}
		else {
			System.out.println("NO");
		}
	}
}

//package stringcoloringeasyversion;

import java.util.*;
import java.io.*;

public class stringcoloringeasyversion {
	public static void main(String[] args) throws IOException {
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

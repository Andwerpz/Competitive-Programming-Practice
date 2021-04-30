package divisibilityby8;

import java.util.*;
import java.io.*;

public class divisibilityby8ver2 {
	public static void main(String[] args) throws IOException {
		
		//remove down to 3 digits. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		char[] s = fin.readLine().toCharArray();
		int n = s.length;
		int[] nums = new int[n];
		for(int i = 0; i < n; i++) {
			nums[i] = Integer.parseInt(s[i] + "");
		}
		int[][] digits = new int[3][8];	//ones, tens, and hundreds. The columns are the remainders when divided by 8.
		for(int i = 0; i < 3; i++) {
			Arrays.fill(digits[i], -1);
		}
		System.out.println(n);
		for(int i = 0; i < n; i++) {
			if(i >= 0) {
				int ones = nums[i];
				int mod = ones % 8;
				if(digits[0][mod] == -1) {
					digits[0][mod] = nums[i];
				}
			}
			if(i >= 1) {
				int tens = nums[i - 1] * 10;
				int mod = tens % 8;
				if(digits[1][mod] == -1) {
					digits[1][mod] = nums[i - 1];
				}
			}
			if(i >= 2) {
				int hundo = nums[i - 2] * 100;
				int mod = hundo % 8;
				if(digits[2][mod] == -1) {
					digits[2][mod] = nums[i - 2];
				}
			}
		}
		for(int[] i : digits) {
			for(int j : i) {
				System.out.print(j + " ");
			}
			System.out.println();
		}
		boolean isValid = false;
		int ans = 0;
		for(int i = 0; i < 8; i++) {
			for(int j = 0; j < 8 - i; j++) {
				for(int k = 0; k < 8 - (i + j); k++) {
					if(digits[0][i] != -1 && digits[1][j] != -1 && digits[2][k] != -1) {
						isValid = true;
						ans = digits[2][k] * 100 + digits[1][j] * 10 + digits[0][i];
					}
				}
			}
		}
		if(isValid) {
			System.out.println("YES");
			System.out.println(ans);
		}
		else {
			System.out.println("NO");
		}
	}
}

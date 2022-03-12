//package factorialsandpowersoftwo;

import java.util.*;
import java.io.*;

public class factorialsandpowersoftwo {
	public static void main(String[] args) throws IOException {
		
		//1646C
		
		//notice that !16 is larger than the maximum value of n, 10^12. 
		
		//also notice that given any n, it is always powerful, since we can look at it's binary representation
		//and fill it in using powers of 2. 
		
		//notice that factorials aren't powers of 2, and we could probably subtract a factorial from n
		//to minimize the amount of powers of 2 we need to use. 
		
		//since we can only fit the first 15 factorials into n, we could probably generate all possible
		//sums of factorials, and subtract them from n, and see which one gets us the least amount 
		//of numbers required.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		long[] f = new long[15];
		long[] fSums = new long[(int) Math.pow(2, 15)];
		int[] cnt = new int[(int) Math.pow(2, 15)];
		f[0] = 1;
		for(int i = 1; i < 15; i++) {
			f[i] = f[i - 1] * (i + 1);
		}
		for(int i = 0; i < fSums.length; i++) {
			char[] c = Integer.toBinaryString(i).toCharArray();
			for(int j = 1; j < 15; j++) {	//j = 1 since we can't have 1 in our factorial
				if(c.length > j && c[j] == '1') {
					cnt[i] ++;
					fSums[i] += f[j];
				}
			}
		}
		while(t-- > 0) {
			long n = Long.parseLong(fin.readLine());
			int ans = Integer.MAX_VALUE;
			for(int i = 0; i < fSums.length; i++) {
				long next = n - fSums[i];
				int curAns = cnt[i];
				char[] c = Long.toBinaryString(next).toCharArray();
				for(char ch : c) {
					if(ch == '1') {
						curAns ++;
					}
				}
//				if(ans > curAns) {
//					System.out.println(i + " " + curAns + " " + fSums[i] + " " + next);
//					System.out.println(String.valueOf(c));
//				}
				ans = Math.min(ans, curAns);
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}

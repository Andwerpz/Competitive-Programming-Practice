//package numericalsequenceeasyversion;

import java.util.*;
import java.io.*;

public class numericalsequenceeasyversion {
	public static void main(String[] args) throws IOException {
		
		//1216E1, 1216E2
		
		//works for both versions.
		
		//define the ith 'block' as the block of numbers from 1 - i. 
		
		//first, bin search for which 'block' k belongs to. You can compute the sum of numbers of blocks from 
		//1 - i in log10(n) time. So to find which block k belongs to, just find the largest i, where the
		//sum of digits in blocks from 1 - i < k.
		
		//Subtract from k, the sum of digits from blocks 1 - i. K is in the block i + 1.
		
		//now, to find the number k is in, you can search the numbers by amounts of digits. there are 9, 1-digit numbers,
		//90 2-digit numbers, 900 3-digit numbers and so on. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			long k = Long.parseLong(fin.readLine());
			//first bin search for which group it belongs to
			long low = 0;	//group num
			long high = (long) 1e9;
			long mid = low + (high - low) / 2;
			long ans = 0;
			while(low <= high) {
				long curAmt = 0;
				long power = 1;
				while(power <= mid) {
					long n = mid - power + 1;
					curAmt += (n * (n + 1)) / 2;
					power *= 10;
				}
				if(curAmt < k) {
					low = mid + 1;
					ans = Math.max(ans, curAmt);
				}
				else {
					high = mid - 1;
				}
				mid = low + (high - low) / 2;
			}
			k -= ans;
			//System.out.println(ans + " "  + k);
			//compute which number k is part of
			long maxAmt = 0;
			long c = 0;
			ans = 0;
			while(true) {
				//System.out.println("YES" + " " + k);
				long rightMaxAmt = maxAmt <= 9? maxAmt : maxAmt - (long) Math.pow(10, c - 1) + 1;
				//System.out.println("R: " + rightMaxAmt);
				if(k > rightMaxAmt * c) {
					k -= rightMaxAmt * c;
					c ++;
					maxAmt *= 10;
					maxAmt += 9;
					continue;
				}
				maxAmt /= 10;
				k--;
				//System.out.println("K: " + k + " " + c);
				long rem = k % c;
				long multiples = k / c;
				k = rem;
				ans = maxAmt + multiples + 1;
				//System.out.println(maxAmt + " " + multiples);
				break;
			}
			
			String s = ans + "";
			//System.out.println(s + " " + k);
			fout.append(s.charAt((int) k)).append("\n");
		}
		System.out.print(fout);
	}
}

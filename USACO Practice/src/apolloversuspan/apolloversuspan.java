//package apolloversuspan;

import java.util.*;
import java.io.*;

public class apolloversuspan {
	public static void main(String[] args) throws IOException {
		
		//1466E
		
		//goddamn, the time limit on this one is tight. had to use bit shifting to get the bits. It's a good technique, should use it later whenever possible. Also, precalculate powers of 2 when necessary.
		
		//If you fix the value of xj, then you need to calculate the value sum(xj & xi) * sum(xj | xk). You can get the sums in O(log(max(xi))) time, which turns out to be around 60. If a bit is contained
		//within xj, then take a look at the bits that occur within xi and xk. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		long mod = 1000000007;
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			int[] bits = new int[61];
			long[] pow = new long[61];
			for (int i = 0; i < 61; i++) {
	            pow[i] = (1l << i) % mod;
	        }
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long[] nums = new long[n];
			for(int i = 0; i < n; i++) {
				nums[i] = Long.parseLong(st.nextToken());
			}
			for(long x : nums){
	            for (int i = 0; i < 61; i++) {
	                if (((1l << i) | x) == x){
	                    bits[i]++;
	                }
	            }
	        }
			//System.out.println(bits);
			long ans = 0;
			for(long x : nums) {
				long andSum = 0;
				long orSum = 0;
				for(int i = 0; i < 61; i++) {
					if(((1l << i) | x) == x) {
						andSum += pow[i] * bits[i];
						andSum %= mod;
					}
					else {
						orSum += pow[i] * bits[i];
						orSum %= mod;
					}
				}
				orSum += (x % mod * n);
				orSum %= mod;
				ans = (ans + (orSum * andSum) % mod) % mod;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}

package santasbot;

import java.util.*;
import java.io.*;

public class santasbot {
	
	public static long gcd(long a, long b) {
		long gcd = 1;
		for(int i = 2; i <= Math.min(a, b); i++) {
			while(a % i == 0 && b % i == 0) {
				gcd *= i;
				a /= i;
				b /= i;
			}
		}
		return gcd;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1279D
		
		//formatting the numbers is way too hard
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		int[] gifts = new int[1000000];	//for each gift, save how many kids want it.
		long[][] pGift = new long[1000000][2];	//probability for choosing any given gift in fraction form
		int numGifts = 0;
		long mod = 998244353;
		for(int i = 0; i < n; i++) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			int k = Integer.parseInt(st.nextToken());
			numGifts += k;
			for(int j = 0; j < k; j++) {
				int next = Integer.parseInt(st.nextToken()) - 1;
				gifts[next] ++;
				if(pGift[next][1] == 0) {
					pGift[next][1] = (n * k) % mod;
					pGift[next][0] = 1;
				}
				else {
					long numerator = pGift[next][0];
					long denominator = (pGift[next][1] * ((n * k) % mod)) % mod;
				}
			}
		}
		
	}
}

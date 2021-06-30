package quiz;

import java.util.*;
import java.io.*;

public class quiz {
	public static void main(String[] args) throws IOException {
		
		//337C
		
		//we have to find a way to calculate the doublings without doing a loop.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		long m = Integer.parseInt(st.nextToken());
		long k = Integer.parseInt(st.nextToken());
		long numIncorrect = n - m;
		long numDouble = m / k;
		long ans = 0;
		long mod = 1000000009;
		if(numIncorrect >= 1) {
			long remainder = k - 1;
			remainder += (k - 1) * numIncorrect;
//			for(int i = 0; i < numIncorrect; i++) {
//				remainder += k - 1;
//			}
			if(remainder >= m) {
				ans = m;
				m = 0;
			}
			else {
				m -= remainder;
				while(m >= k) {
					ans += k;
					ans *= 2;
					ans %= mod;
					m -= k;
				}
				ans += remainder;
				ans %= mod;
			}
		}
		else {
			while(m >= k) {
				ans += k;
				ans *= 2;
				ans %= mod;
				m -= k;
			}
			ans += m;
			ans %= mod;
		}
		System.out.println(ans);
//		if(numIncorrect >= numDouble) {
//			ans = m;
//		}
//		else {
//			long remainder = m % k;
//			System.out.println("NUM DOUBLE: " + numDouble + " " + numIncorrect);
//			numDouble -= numIncorrect;
//			System.out.println(numDouble);
//			while(numDouble > 0) {
//				numDouble --;
//				ans += k;
//				ans *= 2;
//				m -= k;
//				ans %= mod;
//				System.out.println(ans);
//			}
//			System.out.println("REMAINING: " + m);
//			System.out.println(ans);
//			ans += m;
//			ans %= mod;
//			System.out.println(remainder);
//			System.out.println(m - numIncorrect);
//		}
//		System.out.println(ans);
	}
}

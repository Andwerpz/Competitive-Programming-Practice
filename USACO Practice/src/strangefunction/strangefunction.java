//package strangefunction;

import java.util.*;
import java.io.*;

public class strangefunction {
	
	public static long gcd(long a, long b) {
		if(b == 0) {
			return a;
		}
		return gcd(b, a % b);
	}
	
	public static void main(String[] args) throws IOException {
		
		//1542C
		
		//notice that we only care about the least value divisors in any number.
		//first, we can find the amount of numbers less than n that are divisible by 1. That's easy, the answer is n numbers. Next, find the number that are divisible by 2.
		//that's going to be floor(n / 2). Next, find the amount divisible by 1, 2, and 3. To do this, find the lcm of 1, 2, and 3, and the amount will be floor(n / lcm). 
		//you can see that this works since every lcm interval, there will be another number that is divisible by lcm. Continue this until lcm is greater than n. Add every 
		//floor(n / lcm) to the ans, and return.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		long mod = 1000000007;
		while(t-- > 0) {
			long n = Long.parseLong(fin.readLine());
			long ans = n;
			long lcm = 1;
			long pointer = 1;
			while(lcm <= n) {
				long gcd = gcd(pointer, lcm);
				lcm = (lcm * pointer) / gcd;
				ans += n / lcm;
				ans %= mod;
				pointer ++;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}

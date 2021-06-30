package countthearrays;

import java.util.*;
import java.io.*;
import java.math.BigInteger;

public class countthearraysver1 {
	
	static long mod = 998244353;
	
	public static BigInteger getCombinations(long n, long r) {
		if(r < 0) {
			return new BigInteger("0");
		}
		if(r == 0) {
			return new BigInteger("1");
		}
		if(n == 0) {
			return new BigInteger("1");
		}
		BigInteger ans = new BigInteger("1");
		for(long i = r + 1; i <= n; i++) {
			if(i % 100 == 0) {
				System.out.println(i);
			}
			ans = ans.multiply(new BigInteger(i + ""));
		}
		//System.out.println(ans);
		for(long i = 2; i <= (n - r); i++) {
			if(i % 100 == 0) {
				System.out.println(i);
			}
			ans = ans.divide(new BigInteger(i + ""));
		}
		return ans;
	}
	
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		BigInteger first = new BigInteger(((m * (m - 1)) / 2) + "");
		BigInteger second = getCombinations(m - 2, n - 3);
		//System.out.println(first);
		//System.out.println(second);
		first.mod(new BigInteger(mod + ""));
		second.mod(new BigInteger(mod + ""));
		System.out.println((first.multiply(second).mod(new BigInteger(mod + ""))));
	}
}

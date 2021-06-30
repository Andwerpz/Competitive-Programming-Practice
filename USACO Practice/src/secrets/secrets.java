//package secrets;

import java.util.*;
import java.io.*;

public class secrets {
	public static void main(String[] args) throws IOException {
		
		//333A
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		long n = Long.parseLong(fin.readLine());
		long base = 1;
		while(n % base == 0) {
			base *= 3;
		}
		//System.out.println(base);
		long ans = 1;
		n -= n % base;
		ans += n / base;
		System.out.println(ans);
	}
}

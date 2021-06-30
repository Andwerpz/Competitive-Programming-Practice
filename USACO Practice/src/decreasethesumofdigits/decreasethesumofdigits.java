//package decreasethesumofdigits;

import java.util.*;
import java.io.*;

public class decreasethesumofdigits {
	public static void main(String[] args) throws IOException {
		
		//1409D
		
		//my approach is a very hacky one.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			StringTokenizer st = new StringTokenizer(fin.readLine());
			long n = Long.parseLong(st.nextToken());
			int k = Integer.parseInt(st.nextToken());
			char[] s = (n + "").toCharArray();
			long pow = (long) Math.ceil(Math.log10(n));
			int pointer = 0;
			int sum = 0;
			while(pointer != s.length && sum + Integer.parseInt(s[pointer] + "") < k || (pointer == s.length - 1 && (sum + Integer.parseInt(s[pointer] + "") <= k))) {
				sum += Integer.parseInt(s[pointer] + "");
				pointer ++;
			}
			pow = (long) Math.pow(10, s.length - pointer);
			long ans = pow - (n % pow);
			boolean isValid = true;
			sum = 0;
			for(int i = 0; i < s.length; i++) {
				sum += Integer.parseInt(s[i] + "");
			}
			if(!(sum <= k)) {
				isValid = false;
			}
			if(isValid) {
				ans = 0;
			}
			fout.append(ans).append("\n");
		}
		System.out.print(fout);
	}
}

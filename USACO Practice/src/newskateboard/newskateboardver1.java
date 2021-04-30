package newskateboard;

import java.util.*;
import java.io.*;

public class newskateboardver1 {
	public static void main(String[] args) throws IOException {
		
		//instead of pfx sum, go from the sfx. This way, we can get the actual value represented by the string.
		//then going from sfx, mod each number, and find reciprocal in a dict.
		//if the current % 4 is equal to 1, for example, then if a substring of the current value is also %= 1, then we can subtract that subarray to get a value that is %= 0
		
		//can't do this since 4 isn't coprime with 10. not like 2019
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		PrintWriter fout = new PrintWriter(System.out);
		char[] sTemp = fin.readLine().toCharArray();
		int[] s = new int[sTemp.length];
		int n = s.length;
		for(int i = 0; i < n; i++) {
			s[i] = Integer.parseInt(sTemp[i] + "");
		}
		HashMap<Integer, Integer> dict = new HashMap<Integer, Integer>();
		dict.put(0, 1);
		int power = 1;
		int val = 0;
		long ans = 0;
		for(int i = n - 1; i >= 0; i--) {
			val += (s[i] * power) % 4;
			val %= 4;
			System.out.println(val);
			ans += dict.getOrDefault(val, 0);
			dict.put(val, dict.getOrDefault(val, 0) + 1);
			power = (power * 10) % 4;
		}
		System.out.println(ans);
	}
}

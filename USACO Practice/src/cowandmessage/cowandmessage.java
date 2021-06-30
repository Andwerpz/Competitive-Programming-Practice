//package cowandmessage;

import java.util.*;
import java.io.*;

public class cowandmessage {
	public static void main(String[] args) throws IOException {
		
		//1307C
		
		//the observation is that the most frequent arithmetic sequence of characters is going to be a 1 character sequence or 2 character sequence. This is because for any 
		//sequence longer than 2, they can be made up of multiple 2 character sequences, thus making them strictly less or equal to two letter sequences that make them
		//up. With this knowledge, all we have to do is brute force all 26 possible 1 letter sequences and 26 ^ 2 two letter sequences.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		char[] s = fin.readLine().toCharArray();
		int n = s.length;
		HashMap<Character, Integer> dict = new HashMap<Character, Integer>();
		long[] single = new long[26];
		long[][] dbl = new long[26][26];
		for(int i = 0; i < n; i++) {
			char next = s[i];
			single[next - 'a'] ++;
			for(char k : dict.keySet()) {
				dbl[k - 'a'][next - 'a'] += dict.get(k);
			}
			dict.put(next, dict.getOrDefault(next, 0) + 1);
		}
		long ans = 0;
		for(int i = 0; i < dbl.length; i++) {
			for(int j = 0; j < dbl.length; j++) {
				ans = Math.max(dbl[i][j], ans);
			}
			ans = Math.max(single[i], ans);
		}
		System.out.println(ans);
	}
}

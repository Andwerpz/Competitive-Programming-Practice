package lionage2;

import java.util.*;
import java.io.*;

public class lionage2 {
	public static void main(String[] args) throws IOException {
		
		//CF beta round #66
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		char[] s = st.nextToken().toCharArray();
		int k = Integer.parseInt(st.nextToken());
		int n = Integer.parseInt(fin.readLine());
		HashMap<Character, HashMap<Character, Integer>> bonus = new HashMap<Character, HashMap<Character, Integer>>();
		for(char i = 'a'; i <= 'z'; i++) {
			bonus.put(i, new HashMap<Character, Integer>());
		}
		for(int i = 0; i < n; i++) {
			st = new StringTokenizer(fin.readLine());
			char a = st.nextToken().charAt(0);
			char b = st.nextToken().charAt(0);
			int val = Integer.parseInt(st.nextToken());
			bonus.get(a).put(b, val);
		}
		long curBonus = 0;
		for(int i = 0; i < s.length - 1; i++) {
			char a = s[i];
			char b = s[i + 1];
			if(bonus.get(a).containsKey(b)) {
				curBonus += bonus.get(a).get(b);
			}
		}
		long[][][] dp = new long[k][s.length];	//dp[i][j], i letters that are swapped, max value of letter given that we swapped at jth position.
	}
}

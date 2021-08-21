//package vovaandtrophies;

import java.util.*;
import java.io.*;

public class vovaandtrophies {
	public static void main(String[] args) throws IOException {
		
		//1082B
		
		//standard implementation problem. If you can combine two groups, then do it. Else, just try to make 1 group as big as possible
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		char[] s = fin.readLine().toCharArray();
		ArrayList<Integer> groups = new ArrayList<Integer>();
		char prev = 'G';
		int counter = 0;
		for(int i = 0; i < s.length; i++) {
			char next = s[i];
			if(next != prev) {
				prev = next;
				groups.add(counter);
				counter = 0;
			}
			counter ++;
		}
		groups.add(counter);
		boolean twoGold = false;
		boolean threeGold = false;
		if(groups.size() >= 3 && groups.get(0) != 0 || groups.size() >= 5) {
			twoGold = true;
		}
		//System.out.println((groups.size() >= 5) + " " + groups.size());
		if((groups.size() >= 5 && groups.get(0) != 0) || groups.size() >= 7) {
			threeGold = true;
		}
		int ans = 0;
		for(int i = 0; i < groups.size(); i++) {
			if(i % 2 == 0) {
				ans = Math.max(ans, groups.get(i) + (twoGold? 1 : 0));
			}
			else if(groups.get(i) == 1 && i + 1 < groups.size()) {
				ans = Math.max(ans, groups.get(i - 1) + groups.get(i + 1) + (threeGold? 1 : 0));
			}
		}
		//System.out.println(groups + " " + threeGold);
		System.out.println(ans);
	}
}

package marcinandtrainingcamp;

import java.util.*;
import java.io.*;

public class marcinandtrainingcampver2 {
	
	public static boolean isBetterThan(boolean[] a, boolean[] b) {
		for(int i = 0; i < a.length; i++) {
			if(a[i] && !b[i]) {
				return true;
			}
		}
		return false;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1229A
		
				//first, you can safely send the people with a skill value equal to someone else to the camp; if two peoples skill values are equal, then they won't think that they
				//are better than eachother. Then, go through the rest of the people, and see if they don't think that they are better than at least 1 person in the camp. If they don't
				//then you can safely send them to the camp.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		boolean[][] skills = new boolean[n][60];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			long pow = (long) Math.pow(2, 59);
			int pointer = 59;
			long next = Long.parseLong(st.nextToken());
			while(next != 0) {
				if(next >= pow) {
					next -= pow;
					skills[i][pointer] = true;
				}
				pow /= 2;
				pointer --;
			}
		}
		long[] values = new long[n];
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			values[i] = Integer.parseInt(st.nextToken());
		}
		HashSet<Integer> dict = new HashSet<Integer>();
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) {
				if(i != j && !isBetterThan(skills[i], skills[j]) && !isBetterThan(skills[j], skills[i])) {
					dict.add(i);
					dict.add(j);
				}
			}
		}
		for(int i = 0; i < n; i++) {
			boolean isValid = false;
			if(!dict.contains(i)) {
				for(int j : dict) {
					if(!isBetterThan(skills[i], skills[j])) {
						isValid = true;
						break;
					}
				}
			}
			if(isValid) {
				dict.add(i);
			}
		}
		long ans = 0;
		for(int j : dict) {
			ans += values[j];
		}
		System.out.println(ans);
	}
}

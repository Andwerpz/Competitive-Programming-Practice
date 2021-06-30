package marcinandtrainingcamp;

import java.util.*;
import java.io.*;

public class marcinandtrainingcampver1 {
	
	public static boolean isBetterThan(boolean[] a, boolean[] b) {
		for(int i = 0; i < a.length; i++) {
			if(a[i] && !b[i]) {
				return true;
			}
		}
		return false;
	}
	
	public static long search() {
		
	}
	
	public static void main(String[] args) throws IOException {
		
		//1210B
		
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
		ArrayList<HashSet<Integer>> c = new ArrayList<HashSet<Integer>>();
		for(int i = 0; i < n; i++) {
			c.add(new HashSet<Integer>());
			for(int j = 0; j < n; j++) {
				if(i != j && !isBetterThan(skills[i], skills[j])) {
					c.get(i).add(j);
				}
			}
		}
		ArrayList<HashSet<Integer>> secondC = new ArrayList<HashSet<Integer>>();
		long ans = 0;
		for(int i = 0; i < n; i++) {
			boolean isValid = false;
			HashSet<Integer> dict = new HashSet<Integer>();
			
				
			for(int j = 0; j < n; j++) {
				if(j != i && (c.get(j).contains(i))) {
					dict.add(j);
					if(!isValid && c.get(i).contains(j)) {
						isValid = true;
					}
				}
			}
			
			long cur = 0;
			if(isValid) {
				secondC.add(dict);
				cur += values[i];
				for(int j : dict) {
					cur += values[j];
				}
				ans = Math.max(cur, ans);
			}
			else {
				secondC.add(new HashSet<Integer>());
			}
		}
		
		System.out.println(c);
		
		for(int i = 0; i < n; i++) {
			HashSet<Integer> toProcess = new HashSet<Integer>();
			HashSet<Integer> dict = new HashSet<Integer>();
			dict.add(i);
			for(int j : secondC.get(i)) {
				toProcess.add(j);
			}
			while(toProcess.size() != 0) {
				int cur = toProcess.iterator().next();
				for(int j : secondC.get(cur)) {
					if(!toProcess.contains(j) && !dict.contains(j)) {
						toProcess.add(j);
					}
				}
				toProcess.remove(cur);
				dict.add(cur);
			}
			long curSum = 0;
			for(int j : dict) {
				curSum += values[j];
			}
			ans = Math.max(curSum, ans);
		}
		System.out.print(ans);
	}
}

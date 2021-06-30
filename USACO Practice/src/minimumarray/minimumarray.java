//package minimumarray;

import java.util.*;
import java.io.*;

public class minimumarray {
	
	static TreeMap<Integer, Integer> dict;
	
	public static void main(String[] args) throws IOException {
		
		//in order to make something as lexographically minimum as you can, you must prioritize the numbers in order, from first to last. 
		//so we can just focus on minimizing one number at a time. To minimize a number, we either add to it the minimum number from array b, 
		//or we try to push it so that when modded by n, it is less than the original value. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		dict = new TreeMap<Integer, Integer>();
		int n = Integer.parseInt(fin.readLine());
		int[] a = new int[n];
		int[] b = new int[n];
		StringTokenizer st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			a[i] = Integer.parseInt(st.nextToken());
		}
		st = new StringTokenizer(fin.readLine());
		for(int i = 0; i < n; i++) {
			b[i] = Integer.parseInt(st.nextToken());
			dict.put(b[i], dict.getOrDefault(b[i], 0) + 1);
		}
		StringBuilder fout = new StringBuilder();
		for(int i = 0; i < n; i++) {
			int next = a[i];
			int t = n - next;
			int minimum = (dict.firstKey() + next) % n;
			int targetNum = n + 1;
			if(dict.ceilingKey(t) != null) {
				targetNum = (dict.ceilingKey(t) + next) % n;
			}
			if(minimum <= targetNum) {
				if(dict.get(dict.firstKey()) == 1) {
					dict.remove(dict.firstKey());
				}
				else {
					dict.put(dict.firstKey(), dict.get(dict.firstKey()) - 1);
				}
			}
			else {
				if(dict.get(dict.ceilingKey(t)) == 1) {
					dict.remove(dict.ceilingKey(t));
				}
				else {
					dict.put(dict.ceilingKey(t), dict.get(dict.ceilingKey(t)) - 1);
				}
			}
			fout.append(Math.min(minimum, targetNum)).append(" ");
		}
		System.out.println(fout);
	}
}

//package aquamoonandstrangesort;

import java.util.*;
import java.io.*;

public class aquamoonandstrangesort {
	public static void main(String[] args) throws IOException {
		
		//1546C
		
		//notice that a friend goes back to being right after two swaps. This means that the distance between a friends original and sorted location must be even. To test this, we can 
		//first sort the array, and construct a hashmap of even and odd positioned friends. For each number in the sorted array, we check if the index is even or odd, and based on this
		//go into the even or odd hashmap and find whether that number is contained within it. If it is not, then the input is invalid.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			HashMap<Integer, Integer> odds = new HashMap<Integer, Integer>();
			HashMap<Integer, Integer> evens = new HashMap<Integer, Integer>();
			Integer[] sorted = new Integer[n];
			StringTokenizer st = new StringTokenizer(fin.readLine());
			for(int i = 0; i < n; i++) {
				sorted[i] = Integer.parseInt(st.nextToken());
				if(i % 2 == 0) {
					evens.put(sorted[i], evens.getOrDefault(sorted[i], 0) + 1);
				}
				else {
					odds.put(sorted[i], odds.getOrDefault(sorted[i], 0) + 1);
				}
			}
			boolean isValid = true;
			//System.out.println(odds + " " + evens);
			Arrays.sort(sorted);
			for(int i = 0; i < n; i++) {
				int next = sorted[i];
				if(i % 2 == 0) {
					if(evens.containsKey(next)) {
						evens.put(next, evens.get(next) - 1);
						if(evens.get(next) == 0) {
							evens.remove(next);
						}
					}
					else {
						isValid = false;
						break;
					}
				}
				else {
					if(odds.containsKey(next)) {
						odds.put(next, odds.get(next) - 1);
						if(odds.get(next) == 0) {
							odds.remove(next);
						}
					}
					else {
						isValid = false;
						break;
					}
				}
			}
			fout.append(isValid? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}

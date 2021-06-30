//package beautifullyrics;

import java.util.*;
import java.io.*;

public class beautifullyrics {
	
	static String[] words;
	
	public static String[] getNext(HashMap<Integer, HashSet<Integer>> dict) {
		for(int j : dict.keySet()) {
			if(dict.get(j).size() % 2 == 0 && dict.get(j).size() != 0) {
				int a = dict.get(j).iterator().next();
				dict.get(j).remove(a);
				int b = dict.get(j).iterator().next();
				dict.get(j).remove(b);
				return new String[] {words[a], words[b]};
			}
		}
		return null;
	}
	
	public static String[] wrapper(ArrayList<HashMap<Integer, HashSet<Integer>>> dict) {
		for(int i = 0; i < dict.size(); i++) {
			String[] next = getNext(dict.get(i));
			if(next != null) {
				return next;
			}
		}
		return null;
	}
	
	public static void main(String[] args) throws IOException {
		
		//1182C
		
		//very messy implementation, but yknow, it did have the datastructures tag, so hash set spam is acceptable.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int n = Integer.parseInt(fin.readLine());
		HashMap<Character, Integer> chars = new HashMap<Character, Integer>();
		chars.put('a', 0);
		chars.put('e', 1);
		chars.put('i', 2);
		chars.put('o', 3);
		chars.put('u', 4);
		ArrayList<HashMap<Integer, HashSet<Integer>>> dict = new ArrayList<HashMap<Integer, HashSet<Integer>>>();
		words = new String[n];
		for(int i = 0; i < 5; i++) {
			dict.add(new HashMap<Integer, HashSet<Integer>>());
		}
		for(int i = 0; i < n; i++) {
			char[] s = fin.readLine().toCharArray();
			words[i] = String.valueOf(s);
			int counter = 0;
			int prevVowel = -1;
			for(int j = 0; j < s.length; j++) {
				if(chars.containsKey(s[j])) {
					prevVowel = chars.get(s[j]);
					counter ++;
				}
			}
			if(dict.get(prevVowel).get(counter) == null) {
				dict.get(prevVowel).put(counter, new HashSet<Integer>());
			}
			dict.get(prevVowel).get(counter).add(i);
		}
		HashMap<Integer, HashSet<Integer>> singles = new HashMap<Integer, HashSet<Integer>>();
		for(int i = 0; i < dict.size(); i++) {
			for(int j : dict.get(i).keySet()) {
				if(dict.get(i).get(j).size() % 2 == 1) {
					int next = dict.get(i).get(j).iterator().next();
					dict.get(i).get(j).remove(next);
					if(singles.get(j) == null) {
						singles.put(j, new HashSet<Integer>());
					}
					singles.get(j).add(next);
				}
			}
		}
		int singlesPairs = 0;
		HashSet<Integer> toRemove = new HashSet<Integer>();
		for(int i : singles.keySet()) {
			singlesPairs += singles.get(i).size() / 2;
			if(singles.get(i).size() % 2 == 1) {
				toRemove.add(i);
			}
		}
		for(int i : toRemove) {
			int next = singles.get(i).iterator().next();
			singles.get(i).remove(next);
			if(singles.get(i).size() == 0) {
				singles.remove(i);
			}
		}
		int pairs = 0;
		for(int i = 0; i < dict.size(); i++) {
			for(int j : dict.get(i).keySet()) {
				pairs += dict.get(i).get(j).size() / 2;
			}
		}
		int ans = 0;
		StringBuilder fout = new StringBuilder();
		if(singlesPairs >= pairs) {
			ans += pairs;
			for(int i = 0; i < pairs; i++) {
				String[] a = getNext(singles);
				String[] b = wrapper(dict);
				fout.append(a[0]).append(" ").append(b[0]).append("\n");
				fout.append(a[1]).append(" ").append(b[1]).append("\n");
			}
		}
		else {
			ans += singlesPairs;
			pairs -= singlesPairs;
			pairs /= 2;
			ans += pairs;
			for(int i = 0; i < singlesPairs; i++) {
				String[] a = getNext(singles);
				String[] b = wrapper(dict);
				fout.append(a[0]).append(" ").append(b[0]).append("\n");
				fout.append(a[1]).append(" ").append(b[1]).append("\n");
			}
			for(int i = 0; i < pairs; i++) {
				String[] a = wrapper(dict);
				String[] b = wrapper(dict);
				fout.append(a[0]).append(" ").append(b[0]).append("\n");
				fout.append(a[1]).append(" ").append(b[1]).append("\n");
			}
		}
		System.out.println(ans);
		System.out.print(fout);
	}
}

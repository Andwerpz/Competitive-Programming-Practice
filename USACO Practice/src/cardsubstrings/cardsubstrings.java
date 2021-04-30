//package cardsubstrings;

import java.util.*;
import java.io.*;

public class cardsubstrings {
	public static void main(String[] args) throws IOException {
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(fin.readLine());
		int n = Integer.parseInt(st.nextToken());
		int m = Integer.parseInt(st.nextToken());
		HashMap<Character, Integer> cards = new HashMap<Character, Integer>();
		HashMap<Character, Integer> curChars = new HashMap<Character, Integer>();
		char[] s = fin.readLine().toCharArray();
		char[] cardsInput = fin.readLine().toCharArray();
		for(int i = 0; i < m; i++) {
			cards.put(cardsInput[i], cards.getOrDefault(cardsInput[i], 0) + 1);
		}
		int low = 0;
		long ans = 0;
		for(int i = 0; i < n; i++) {
			//System.out.println(s[i]);
			curChars.put(s[i], curChars.getOrDefault(s[i], 0) + 1);
			boolean needRemoval = true;
			while(needRemoval) {
				Set<Character> keys = curChars.keySet();
				//System.out.println("removal size: " + keys.size());
				needRemoval = false;
				for(char k : keys) {
					//System.out.println("checking " + k);
					if((!cards.containsKey(k) || curChars.get(k) > cards.getOrDefault(k, 0)) && curChars.get(k) != 0) {	//gotta check if the dict entry is 0
						needRemoval = true;
						break;
					}
				}
				if(low < n && needRemoval) {
					//System.out.println("removing " + s[low]);
					char next = s[low];
					curChars.put(next, curChars.get(next) - 1);
					if(curChars.get(next) == 0) {
						curChars.remove(next);
					}
					low++;
				}
			}
			ans += i - low + 1;
		}
		System.out.println(ans);
	}
}

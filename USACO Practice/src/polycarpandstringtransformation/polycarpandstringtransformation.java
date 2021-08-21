//package polycarpandstringtransformation;

import java.util.*;
import java.io.*;

public class polycarpandstringtransformation {
	public static void main(String[] args) throws IOException {
		
		//1560E
		
		//notice that if there is a valid string s, then there is only 1 valid string, s. We just have to find whether there is a valid string.
		
		//to do this, you can first count how many times each letter occurs. Notice that given a valid string s, if there are n different characters, and you divide the total count by the amount
		//that appear in s, then you'll get a sequence looking like 1, 2, 3, ... n. You can try out every prefix, since there are only 26 possible characters.
		
		//when you found a possible valid string, then you need to test it against the rest of the string to make sure that the order in which the rest of the characters appear is correct.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			char[] s = fin.readLine().toCharArray();
			int[] numChars = new int[26];
			int numDifferentChars = 0;
			HashMap<Character, Integer> dict = new HashMap<Character, Integer>();
			for(int i = 0; i < s.length; i++) {
				char next = s[i];
				numChars[s[i] - 'a'] ++;
				if(!dict.containsKey(next)) {
					numDifferentChars ++;
					dict.put(next, 0);
				}
			}
			boolean isValid = false;
			char[] sub = new char[0];
			char[] order = new char[0];
			outer :
			for(int i = 0; i < s.length; i++) {
				char next = s[i];
				boolean curValid = true;
				dict.put(next, dict.get(next) + 1);
				order = new char[numDifferentChars];
				//System.out.println("i: " + i);
				for(char j : dict.keySet()) {
					int index = j - 'a';
					int curChars = dict.get(j);
					if(curChars == 0 || numChars[index] % curChars != 0) {
						curValid = false;
						break;
					}
					int multiple = numChars[index] / curChars;
					//System.out.print(multiple + " ");
					if(multiple - 1 >= order.length || order[multiple - 1] != 0) {
						curValid = false;
						break;
					}
					order[multiple - 1] = j;
				}
				if(curValid) {
					sub = (String.valueOf(s).substring(0, i + 1)).toCharArray();
					isValid = true;
					break outer;
				}
			}
			if(isValid) {
				HashSet<Character> removed = new HashSet<Character>();
				int pointer = 0;
				outer:
				for(int i = 0; i <= order.length; i++) {
					//System.out.println(i + " " + removed);
					for(int j = 0; j < sub.length; j++) {
						//System.out.println(s[pointer]);
						if(removed.contains(sub[j])) {
							continue;
						}
						if(pointer == s.length || s[pointer] != sub[j]) {
							isValid = false;
							//System.out.println("NOT VALID");
							break outer;
						}
						pointer ++;
					}
					if(i != order.length) {
						removed.add(order[i]);
					}
				}
			}
			if(isValid) {
				fout.append(String.valueOf(sub)).append(" ").append(String.valueOf(order)).append("\n");
			}
			else {
				fout.append("-1\n");
			}
		}
		System.out.print(fout);
	}
}

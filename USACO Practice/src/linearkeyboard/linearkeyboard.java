//package linearkeyboard;

import java.util.*;
import java.io.*;

public class linearkeyboard {
	public static void main(String[] args) throws IOException {
		
		//1607A
		
		//simple implementation problem, just use a hashmap to save the location of characters on keyboard.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		StringBuilder fout = new StringBuilder();
		int t = Integer.parseInt(fin.readLine());
		while(t-- > 0) {
			char[] keyboard = fin.readLine().toCharArray();
			char[] s = fin.readLine().toCharArray();
			HashMap<Character, Integer> keys = new HashMap<Character, Integer>();
			for(int i = 0; i < keyboard.length; i++) {
				keys.put(keyboard[i], i);
			}
			int sum = 0;
			for(int i = 0; i < s.length - 1; i++) {
				sum += Math.abs(keys.get(s[i]) - keys.get(s[i + 1]));
			}
			fout.append(sum).append("\n");
		}
		System.out.print(fout);
	}
}

//package perfectkeyboard;

import java.util.*;
import java.io.*;

public class perfectkeyboard {
	public static void main(String[] args) throws IOException {
		
		//1303C
		
		//you can start with the first letter, and just add letters from the password one by one. If you ever run into a position where you need to add a letter
		//and you can't add it, or if you have already added a letter but you can't reach it, then the input is invalid.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			char[] s = fin.readLine().toCharArray();
			char[] keyboard = new char[70];
			Arrays.fill(keyboard, '.');
			
			int pointer = 35;
			HashSet<Character> chars = new HashSet<Character>();
			for(char i = 'a'; i <= 'z'; i++) {
				chars.add(i);
			}
			keyboard[35] = s[0];
			chars.remove(s[0]);
			boolean isValid = true;
			for(int i = 1; i < s.length; i++) {
				if(!chars.contains(s[i])) {
					if(keyboard[pointer + 1] == s[i]) {
						pointer ++;
					}
					else if(keyboard[pointer - 1] == s[i]) {
						pointer --;
					}
					else {
						isValid = false;
						break;
					}
				}
				else {
					if(keyboard[pointer + 1] == '.') {
						pointer ++;
						keyboard[pointer] = s[i];
						chars.remove(s[i]);
					}
					else if(keyboard[pointer - 1] == '.') {
						pointer --;
						keyboard[pointer] = s[i];
						chars.remove(s[i]);
					}
					else {
						isValid = false;
						break;
					}
				}
			}
			if(isValid) {
				fout.append("YES\n");
				for(int i = 0; i < keyboard.length; i++) {
					if(keyboard[i] != '.') {
						fout.append(keyboard[i]);
					}
				}
				for(char i : chars) {
					fout.append(i);
				}
				fout.append("\n");
			}
			else {
				fout.append("NO\n");
			}
		}
		System.out.print(fout);
	}
}

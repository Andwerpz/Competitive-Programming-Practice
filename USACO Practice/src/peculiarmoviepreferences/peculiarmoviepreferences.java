//package peculiarmoviepreferences;

import java.util.*;
import java.io.*;

public class peculiarmoviepreferences {
	public static void main(String[] args) throws IOException {
		
		//1629D
		
		//first, filter out any test cases that include strings that themselves are palindromic. Those test cases automatically pass.
		//this means that there are no strings left of length 1. 
		
		//now we only have non-palindromic strings of length 2 and 3. Assuming that we can make a palindrome using these strings,
		//consider it's center. It will take the form, 1122, 11122, 11222, or 111222. Notice that since the values within the strings
		//are limited to within 26 letters, we could probably record all possible combos of 3 letter strings, and check for palindromes
		
		//since we have to keep the strings in order, we can't first put all the strings into the dictionary, and then check all the
		//strings against it. Instead, as we check the string, we place them into the dictionary, effectively checking every string
		//with every string that comes before it.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			boolean isValid = false;
			char[][] s = new char[n][];
			for(int i = 0; i < n; i++) {
				s[i] = fin.readLine().toCharArray();
				if(s[i][0] == s[i][s[i].length - 1]) {
					isValid = true;
				}
			}
			if(isValid) {
				fout.append("YES\n");
				continue;
			}
			//we know that there are no 1 letter strings
			boolean[][][] v = new boolean[26][26][26]; 	//first letter, second letter, third letter if have
			outer:
			for(int i = 0; i < n; i++) {
				//check if there is a possible pair
				int first = s[i].length == 3? s[i][2] - 'a' : s[i][1] - 'a';
				int second = s[i].length == 3? s[i][1] - 'a' : s[i][0] - 'a';
				int third = s[i].length == 3? s[i][0] - 'a' : -1;
				if(third == -1) {
					for(int j = 0; j < 26; j++) {
						if(v[first][second][j]) {
							isValid = true;
							break outer;
						}
					}
				}
				else if(v[first][second][third]){
					isValid = true;
					break;
				}
				
				//enter current string into dict
				first = s[i][0] - 'a';
				second = s[i][1] - 'a';
				third = s[i].length == 3? s[i][2] - 'a' : -1;
				if(third == -1) {
					for(int j = 0; j < 26; j++) {
						v[first][second][j] = true;
					}
				}
				else {
					v[first][second][third] = true;
				}
			}
			fout.append(isValid? "YES\n" : "NO\n");
		}
		System.out.print(fout);
	}
}

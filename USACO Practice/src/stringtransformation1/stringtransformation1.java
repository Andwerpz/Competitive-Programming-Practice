//package stringtransformation1;

import java.util.*;
import java.io.*;

public class stringtransformation1 {
	public static void main(String[] args) throws IOException {
		
		//1383A
		
		//"nowhere to go now but up"
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int t = Integer.parseInt(fin.readLine());
		StringBuilder fout = new StringBuilder();
		while(t-- > 0) {
			int n = Integer.parseInt(fin.readLine());
			char[] a = fin.readLine().toCharArray();
			char[] b = fin.readLine().toCharArray();
			boolean isValid = true;
			for(int i = 0; i < n; i++) {
				if(a[i] > b[i]) {
					isValid = false;
					break;
				}
			}
			if(isValid) {
				ArrayList<TreeSet<Character>> dict = new ArrayList<TreeSet<Character>>();	//for each letter, which letters the set needs to go to
				for(char i = 'a'; i <= 't'; i++) {
					dict.add(new TreeSet<Character>());
					for(int j = 0; j < n; j++) {
						if(a[j] == i && a[j] < b[j]) {
							dict.get(i - 'a').add(b[j]);
						}
					}
				}
				int ans = 0;
				for(char i = 'a'; i <= 't'; i++) {
					boolean replace = false;
					TreeSet<Character> curSet = new TreeSet<Character>();
					for(int j = 0; j < n; j++) {
						if(a[j] == i && a[j] < b[j]) {
							curSet.add(b[j]);
							replace = true;
						}
					}
					if(replace) {
						boolean matched = false;
						char which = curSet.first();
//						for(int j = i - 'a' + 1; j < 20; j++) {
//							if(curSet.first() == dict.get(j).first()) {
//								matched = true;
//								
//							}
//						}
						for(int j = 0; j < n; j++) {
							if(a[j] == i && a[j] < b[j]) {
								a[j] = which;
							}
						}
//						System.out.println(String.valueOf(a));
//						System.out.println(String.valueOf(b) + "\n");
						ans ++;
					}
				}
				fout.append(ans).append("\n");
			}
			else {
				fout.append("-1\n");
			}
		}
		System.out.print(fout);
	}
}

//package periodicintegernumber;

import java.util.*;
import java.io.*;

public class periodicintegernumber {
	public static void main(String[] args) throws IOException {
		
		//1219C
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		int l = Integer.parseInt(fin.readLine());
		char[] s = fin.readLine().toCharArray();
		StringBuilder fout = new StringBuilder();
		boolean needBig = true;
		for(int i = 0; i < s.length; i++) {
			if(s[i] != '9') {
				needBig = false;
				break;
			}
		}
		if(s.length % l == 0 && !needBig) {
			char[] repeat = String.valueOf(s).substring(0, l).toCharArray();
			boolean add = false;
			for(int i = 0; i < s.length; i++) {
				if(s[i] < repeat[i % l]) {
					break;
				}
				else if(s[i] > repeat[i % l]) {
					add = true;
					break;
				}
				else if(i == s.length - 1) {
					add = true;
				}
			}
			if(add) {
				repeat[l - 1] ++;
				for(int i = l - 1; i >= 0; i--) {
					if(repeat[i] == ':') {
						repeat[i] = '0';
						repeat[i - 1] ++;
					}
					else {
						break;
					}
				}
			}
			for(int i = 0; i < s.length; i++) {
				fout.append(repeat[i % l]);
			}
		}
		else {
			int howMany = (s.length / l) + 1;
			for(int i = 0; i < howMany; i++) {
				for(int j = 0; j < l; j++) {
					if(j == 0) {
						fout.append("1");
					}
					else {
						fout.append("0");
					}
				}
			}
		}
		System.out.println(fout);
	}
}

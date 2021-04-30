//package nikitaandstring;

import java.util.*;
import java.io.*;

public class nikitaandstringver1 {
	public static void main(String[] args) throws IOException {
		
		//didn't interpret the question correctly. 
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		ArrayList<Integer> sections = new ArrayList<Integer>();	//force start with an 'a' section
		char[] s = fin.readLine().toCharArray();
		char prev = 'c';
		for(int i = 0; i < s.length; i++) {
			if(s[i] == prev) {
				sections.set(sections.size() - 1, sections.get(sections.size() - 1) + 1);
			}
			else {
				sections.add(1);
				prev = s[i];
			}
		}
		int max = 0;
		if(sections.size() <= 3) {
			for(int i = 0; i < sections.size(); i++) {
				max += sections.get(i);
			}
		}
		else {
			for(int i = 0; i < sections.size() - 2; i += 2) {
				int cur = sections.get(i) + sections.get(i + 1) + sections.get(i + 2);
				if(cur > max) {
					max = cur;
				}
			}
		}
		System.out.println(max);
	}
}

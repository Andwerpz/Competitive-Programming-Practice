//package nikitaandstring;

import java.util.*;
import java.io.*;

public class nikitaandstring {
	public static void main(String[] args) throws IOException {
		
		//this time, we try all possible partitions.
		
		BufferedReader fin = new BufferedReader(new InputStreamReader(System.in));
		char[] s = fin.readLine().toCharArray();
		int n = s.length;
		ArrayList<Integer> sections = new ArrayList<Integer>();
		char prev = 'a';
		sections.add(0);
		for(int i = 0; i < n; i++) {
			if(s[i] == prev) {
				sections.set(sections.size() - 1, sections.get(sections.size() - 1) + 1);
			}
			else {
				sections.add(1);
				prev = s[i];
			}
		}
		int max = 0;
		int aTotal = 0;
		for(int i = 0; i < sections.size(); i++) {
			if(i % 2 == 0) {
				aTotal += sections.get(i);
			}
		}
		int aCur = 0;
		int bCur = 0;
		int cCur = aTotal;
		max = aTotal;
		//System.out.println(aTotal);
		for(int i = 0; i < sections.size(); i++) {	//looping through all possible partitions.
			if(i % 2 == 0) {
				aCur += sections.get(i);
			}
			else {
				bCur -= sections.get(i);
			}
			cCur = aTotal - aCur;
			bCur = 0;
			if(aCur + bCur + cCur > max) {
				max = aCur + bCur + cCur;
			}
			for(int j = i; j < sections.size(); j++) {
				
				if(j % 2 == 1) {
					bCur += sections.get(j);
				}
				else {
					cCur -= sections.get(j);
				}
				if(aCur + bCur + cCur > max) {
					max = aCur + bCur + cCur;
				}
				//System.out.println(aCur + " " + bCur + " " + cCur);
			}
		}
		System.out.println(max);
	}
}
